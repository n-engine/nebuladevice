/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifdef __CELLOS_LV2__
#include <stdio.h>						/* printf, fprintf */

/* Lv2 OS headers */
#include <sys/event.h>
#include <sys/spu_thread.h>
#include <sys/ppu_thread.h>

/* for spu_printf */
#include <spu_printf.h>

#include <cell/spurs/lv2_event_queue.h>

#define	SPU_PORT_PRINTF	1
#define	TERMINATING_PORT_NAME	0xFEE1DEAD

#define	STACK_SIZE	(1024 * 64)

#include "spurs_util_spu_printf_service.h"

static void
spu_printf_handler_entry(uint64_t arg)
{
	SampleUtilSpursPrintfService *service = (SampleUtilSpursPrintfService *)(uintptr_t)arg;
	int	ret;
	for (;;) {
		sys_spu_thread_t	spu;
		sys_event_t	event;

		ret = sys_event_queue_receive(service->equeue, &event, 0);

		if (event.source == TERMINATING_PORT_NAME) {
			printf ("Finalizing the spu printf handler\n");
			sys_ppu_thread_exit(0);
		}
		spu = event.data1;
		int sret = spu_thread_printf(spu, event.data3);
		ret = sys_spu_thread_write_spu_mb(spu, sret);
		if (ret) {
			printf ("sys_spu_thread_write_spu_mb failed (%d)\n", ret);
			sys_ppu_thread_exit(-1);
		}
	}
	/* never reach here */
	sys_ppu_thread_exit(0);
}

int
sampleSpursUtilSpuPrintfServiceInitialize(SampleUtilSpursPrintfService *service, CellSpurs* spurs, int prio)
{
	int	ret;
	service->spurs = spurs;

	/* create event_queue for printf */
	sys_event_queue_attribute_t	attr;
	sys_event_queue_attribute_initialize (attr);

	/* queue depth must be equal or greater than max_spu_threads */
	ret = sys_event_queue_create (&service->equeue, &attr, SYS_EVENT_QUEUE_LOCAL, 8);
	if (ret) {
		printf ("sys_event_queue_create failed (%d)\n", ret);
		return ret;
	}

	/* 		create ppu_thread for printf handling */
	ret = sys_ppu_thread_create (&service->spu_printf_handler, spu_printf_handler_entry,
								 (uint64_t)(uintptr_t)service, prio, STACK_SIZE, SYS_PPU_THREAD_CREATE_JOINABLE, 
								 "spu_printf_handler");
	if (ret) {
		printf ("sys_ppu_thread_create failed (%d)\n", ret);
		return ret;
	}

	/*
	 * Create the terminating port. This port is used only in 
	 * spu_printf_service_finalize().
	 */
	ret = sys_event_port_create(&service->terminating_port, SYS_EVENT_PORT_LOCAL, TERMINATING_PORT_NAME);
	if (ret) {
		printf ("spu_printf_server_initialize: sys_event_port_create failed %d\n", ret);
		return ret;
	}

	ret = sys_event_port_connect_local(service->terminating_port, service->equeue);
	if (ret) {
		printf ("spu_printf_server_initialize: sys_event_connect failed %d\n", ret);
		return ret;
	}

	/* connect to SPURS */
	uint8_t	port = SPU_PORT_PRINTF;
	ret = cellSpursAttachLv2EventQueue (service->spurs, service->equeue, &port, 0);
	if (ret) {
		printf ("spu_printf_server_initialize: cellSpursAttachLv2EventQueue failed %d\n", ret);
		return ret;
	}
	return CELL_OK;
}

int
sampleSpursUtilSpuPrintfServiceFinalize(SampleUtilSpursPrintfService *service)
{
	int ret;
	uint64_t	exit_code;

	/*
	 *
	 */
	ret = cellSpursDetachLv2EventQueue (service->spurs, SPU_PORT_PRINTF);
	if (ret) {
		printf ("cellSpursDetachLv2EventQueue failed %d\n", ret);
		return ret;
	}

	/*
	 * send event for temination.
	 */
	ret = sys_event_port_send (service->terminating_port, 0, 0, 0);
	if (ret) {
		printf ("sys_event_port_send failed %d\n", ret);
		return ret;
	}
	/*	wait for termination of the handler thread */
	ret = sys_ppu_thread_join (service->spu_printf_handler, &exit_code);
	if (ret) {
		printf("sys_ppu_thread_join failed %d\n", ret);
		return ret;
	}

	/* Disconnect and destroy the terminating port */
	ret = sys_event_port_disconnect(service->terminating_port);
	if (ret) {
		printf("sys_event_disconnect failed %d\n", ret);
		return ret;
	}
	ret = sys_event_port_destroy(service->terminating_port);
	if (ret) {
		printf("sys_event_port_destroy failed %d\n", ret);
		return ret;
	}	

	/*	clean event_queue for spu_printf */
	ret = sys_event_queue_destroy (service->equeue, 0);
	if (ret) {
		printf("sys_event_queue_destroy failed %d\n", ret);
		return ret;
	}

	return CELL_OK;
}

#endif //__CELLOS_LV2__
