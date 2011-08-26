#ifndef __PFX_DOUBLE_BUFFER_H__
#define __PFX_DOUBLE_BUFFER_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PfxStackAllocator.h"

class PfxDoubleBuffer
{
private:
	PfxStackAllocator *mPool;
	
	CellDmaListElement *mDmaList[3];
	uint32_t mNumList[2];

	void  *mBuffer[2];
	uint32_t *mLsAddrs[2];

	uint32_t mBatch;
	uint32_t mSizeOfData;
	uint32_t mTag;
	uint32_t mSwap;
	uint32_t mStartLsAddr;
	
public:
	PfxDoubleBuffer(PfxStackAllocator *pool,uint32_t sizeOfData,uint32_t batch,uint32_t tag)
	{
		mPool = pool;
		mTag = tag;
		mSwap = 0;
		mBatch = batch;
		mSizeOfData = sizeOfData;
		
		mDmaList[0] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mBatch);
		mDmaList[1] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mBatch);
		mDmaList[2] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mBatch);
		mBuffer[0] = mPool->allocate(mSizeOfData*mBatch,PfxStackAllocator::ALIGN128);
		mBuffer[1] = mPool->allocate(mSizeOfData*mBatch,PfxStackAllocator::ALIGN128);
		mLsAddrs[0] = (uint32_t*)mPool->allocate(sizeof(uint32_t)*mBatch);
		mLsAddrs[1] = (uint32_t*)mPool->allocate(sizeof(uint32_t)*mBatch);
	}

	~PfxDoubleBuffer()
	{
		if(mNumList[mSwap] > 0) {
			//uint32_t startAddr = (uint32_t)mBuffer[mSwap];
			//for(int i=0;i<mNumList[mSwap];i++) {
			//	PRINTF("put ls:%x ea:%x sz:%d\n",startAddr,(uint32_t)mDmaList[mSwap][i].eal,(uint32_t)mDmaList[mSwap][i].size);
			//	startAddr += mDmaList[mSwap][i].size;
			//}
			cellDmaListPut(mBuffer[mSwap],0,mDmaList[mSwap],sizeof(CellDmaListElement)*mNumList[mSwap],mTag,0,0);
		}
		wait();
		
		mPool->deallocate(mLsAddrs[1]);
		mPool->deallocate(mLsAddrs[0]);
		mPool->deallocate(mBuffer[1]);
		mPool->deallocate(mBuffer[0]);
		mPool->deallocate(mDmaList[2]);
		mPool->deallocate(mDmaList[1]);
		mPool->deallocate(mDmaList[0]);
	}
	
	void appendBegin()
	{
		mNumList[mSwap] = 0;
		mStartLsAddr = (uint32_t)mBuffer[mSwap];
	}
	
	void appendEnd()
	{
		if(mNumList[mSwap] > 0) {
			cellDmaListGetf(mBuffer[mSwap],0,mDmaList[mSwap],sizeof(CellDmaListElement)*mNumList[mSwap],mTag,0,0);
		}
		mSwap = 1 - mSwap;
	}
	
	void append(uint32_t ea,uint32_t sz)
	{
		PFX_ASSERT(mNumList[mSwap] < mBatch);
		CellDmaListElement dmaList;
		dmaList.notify = 0;
		dmaList.eal = ea;
		dmaList.size = sz;
		mDmaList[mSwap][mNumList[mSwap]] = dmaList;
		mLsAddrs[mSwap][mNumList[mSwap]] = mStartLsAddr;
		//PRINTF("append ls:%x ea:%x sz:%d\n",mStartLsAddr,ea,sz);
		mStartLsAddr += sz;
		mNumList[mSwap]++;
	}

	void wait()
	{
		cellDmaWaitTagStatusAll(1<<mTag);
	}

	void put()
	{
		if(mNumList[mSwap] > 0) {
			//uint32_t startAddr = (uint32_t)mBuffer[mSwap];
			//for(int i=0;i<mNumList[mSwap];i++) {
			//	PRINTF("put ls:%x ea:%x sz:%d\n",startAddr,(uint32_t)mDmaList[mSwap][i].eal,(uint32_t)mDmaList[mSwap][i].size);
			//	startAddr += mDmaList[mSwap][i].size;
			//}
			memcpy(mDmaList[2],mDmaList[mSwap],sizeof(CellDmaListElement)*mNumList[mSwap]);
			cellDmaListPut(mBuffer[mSwap],0,mDmaList[2],sizeof(CellDmaListElement)*mNumList[mSwap],mTag,0,0);
		}
	}

	void *get(int i)
	{
		return (void*)mLsAddrs[mSwap][i];
	}
};

#endif /* __PFX_DOUBLE_BUFFER_H__ */
