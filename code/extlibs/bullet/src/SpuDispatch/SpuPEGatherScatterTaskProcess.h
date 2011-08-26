/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef SPU_PE_GATHER_SCATTER_TASK_PROCESS_H
#define SPU_PE_GATHER_SCATTER_TASK_PROCESS_H

#include <assert.h>


#include "BulletMultiThreaded/PlatformDefinitions.h"

#include <stdlib.h>

#include "LinearMath/btAlignedObjectArray.h"


#include "SPURS_PEGatherScatterTask/SpuPEGatherScatterTask.h"




/// SpuPEGatherScatterTaskProcess handles SPU processing of collision pairs.
/// When PPU issues a task, it will look for completed task buffers
/// PPU will do postprocessing, dependent on workunit output (not likely)
class SpuPEGatherScatterTaskProcess
{
	// track task buffers that are being used, and total busy tasks
	btAlignedObjectArray<bool>	m_taskBusy;
	btAlignedObjectArray<SpuPEGatherScatterTaskDesc>m_spuPEGatherScatterTaskDesc;
	
	int   m_numBusyTasks;

	// the current task and the current entry to insert a new work unit
	int   m_currentTask;

	bool m_initialized;

	void postProcess(int taskId, int outputSize);
	
	class	btThreadSupportInterface*	m_threadInterface;

	int	m_maxNumOutstandingTasks;



public:
	SpuPEGatherScatterTaskProcess(btThreadSupportInterface*	threadInterface, unsigned int maxNumOutstandingTasks);
	
	~SpuPEGatherScatterTaskProcess();
	
	///call initialize in the beginning of the frame, before addCollisionPairToTask
	void initialize();

	void issueTask(int sampleCommand, void* m_bulletArrayAddress,void* m_peArrayAddress,void* m_peArray2Address,int startIndex,int numElements);

	///call flush to submit potential outstanding work to SPUs and wait for all involved SPUs to be finished
	void flush();
};


#if defined(USE_LIBSPE2) && defined(__SPU__)
////////////////////MAIN/////////////////////////////
#include "../SpuLibspe2Support.h"
#include <spu_intrinsics.h>
#include <spu_mfcio.h>
#include <SpuFakeDma.h>

void * PEGatherScatterlsMemoryFunc();
void PEGatherScatterThreadFunc(void* userPtr,void* lsMemory);

//#define DEBUG_LIBSPE2_MAINLOOP

int main(unsigned long long speid, addr64 argp, addr64 envp)
{
	printf("SPU is up \n");
	
	ATTRIBUTE_ALIGNED128(btSpuStatus status);
	ATTRIBUTE_ALIGNED16( SpuPEGatherScatterTaskDesc taskDesc ) ;
	unsigned int received_message = Spu_Mailbox_Event_Nothing;
        bool shutdown = false;

	cellDmaGet(&status, argp.ull, sizeof(btSpuStatus), DMA_TAG(3), 0, 0);
	cellDmaWaitTagStatusAll(DMA_MASK(3));

	status.m_status = Spu_Status_Free;
	status.m_lsMemory.p = PEGatherScatterlsMemoryFunc();

	cellDmaLargePut(&status, argp.ull, sizeof(btSpuStatus), DMA_TAG(3), 0, 0);
	cellDmaWaitTagStatusAll(DMA_MASK(3));
	
	
	while (!shutdown)
	{
		received_message = spu_read_in_mbox();
		

		
		switch(received_message)
		{
		case Spu_Mailbox_Event_Shutdown:
			shutdown = true;
			break; 
		case Spu_Mailbox_Event_Task:
			// refresh the status
#ifdef DEBUG_LIBSPE2_MAINLOOP
			printf("SPU recieved Task \n");
#endif //DEBUG_LIBSPE2_MAINLOOP
			cellDmaGet(&status, argp.ull, sizeof(btSpuStatus), DMA_TAG(3), 0, 0);
			cellDmaWaitTagStatusAll(DMA_MASK(3));
		
			btAssert(status.m_status==Spu_Status_Occupied);
			
			cellDmaGet(&taskDesc, status.m_taskDesc.p, sizeof(SpuPEGatherScatterTaskDesc), DMA_TAG(3), 0, 0);
			cellDmaWaitTagStatusAll(DMA_MASK(3));
			
			PEGatherScatterThreadFunc((void*)&taskDesc, reinterpret_cast<void*> (taskDesc.m_mainMemoryPtr) );
			break;
		case Spu_Mailbox_Event_Nothing:
		default:
			break;
		}

		// set to status free and wait for next task
		status.m_status = Spu_Status_Free;
		cellDmaLargePut(&status, argp.ull, sizeof(btSpuStatus), DMA_TAG(3), 0, 0);
		cellDmaWaitTagStatusAll(DMA_MASK(3));		
				
		
  	}
  	return 0;
}
//////////////////////////////////////////////////////
#endif



#endif // SPU_PE_GATHER_SCATTER_TASK_PROCESS_H

