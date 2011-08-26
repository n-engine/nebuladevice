/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SAFEDMA_H__
#define __SAFEDMA_H__

///////////////////////////////////////////////////////////////////////////////
// safe dma func

static inline
uint32_t dmaGetBuffer(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaGet(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}

static inline
uint32_t dmaGetBufferf(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaGetf(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}


static inline
uint32_t dmaGetBufferb(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaGetb(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}

static inline
uint32_t dmaPutBuffer(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaPut(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}

static inline
uint32_t dmaPutBufferf(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaPutf(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}

static inline
uint32_t dmaPutBufferb(void* ls,uint32_t start,uint32_t end,int32_t sz,uint32_t tag)
{
	int32_t sz_tmp = (start+sz <= end)?sz:end-start;
	if(sz_tmp < 0) sz_tmp = 0;
	cellDmaPutb(ls,start,sz_tmp,tag,0,0);
	return (uint32_t)sz_tmp;
}

#endif /* __SAFEDMA_H__ */
