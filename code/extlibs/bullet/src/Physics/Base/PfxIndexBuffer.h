#ifndef __PFX_INDEX_BUFFER_H__
#define __PFX_INDEX_BUFFER_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PfxStackAllocator.h"

class PfxIndexBuffer
{
private:
	PfxStackAllocator *mPool;
	
	static const int MAX_BUFF = 256;
	
	CellDmaListElement *mDmaList[2];
	uint32_t mNumList[2];
	uint32_t *mAddrs;
	uint8_t  *mIdTable;
	uint8_t  *mBuffer;
	uint16_t mMaxId;
	uint32_t mSizeOfData;
	uint32_t mTag;
	uint32_t mSwap;
	uint32_t mNumBuff;
	void *mStartBuffPtr;
	
public:
	PfxIndexBuffer(PfxStackAllocator *pool,uint32_t sizeOfData,uint32_t maxId,uint32_t tag)
	{
		mPool = pool;
		mSizeOfData = sizeOfData;
		mMaxId = maxId;
		mTag = tag;
		mSwap = 0;
		mNumBuff = 0;

		mAddrs = (uint32_t*)mPool->allocate(sizeof(CellDmaListElement)*MAX_BUFF);
		mDmaList[0] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*MAX_BUFF);
		mDmaList[1] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*MAX_BUFF);
		mIdTable = (uint8_t*)mPool->allocate(sizeof(uint8_t)*mMaxId);
		mBuffer = (uint8_t*)mPool->allocate(mSizeOfData*MAX_BUFF,PfxStackAllocator::ALIGN128);
		memset(mIdTable,0xff,sizeof(uint8_t)*mMaxId);
		for(int i=0;i<MAX_BUFF;i++) {
			mDmaList[0][i].notify = 0;
			mDmaList[1][i].notify = 0;
			mDmaList[0][i].size = mSizeOfData;
			mDmaList[1][i].size = mSizeOfData;
		}
	}

	~PfxIndexBuffer()
	{
		for(uint32_t i=0;i<mNumBuff;i++) {
			mDmaList[0][i].eal = mAddrs[i];
			//PRINTF("put ls:%x ea:%x\n", &mBuffer[i*mSizeOfData],mAddrs[i]);
		}
		cellDmaListPut(mBuffer,0,mDmaList[0],sizeof(CellDmaListElement)*mNumBuff,mTag,0,0);
		wait();
		
		mPool->deallocate(mBuffer);
		mPool->deallocate(mIdTable);
		mPool->deallocate(mDmaList[1]);
		mPool->deallocate(mDmaList[0]);
		mPool->deallocate(mAddrs);
	}

	void appendBegin()
	{
		mNumList[mSwap] = 0;
		mStartBuffPtr = &mBuffer[mNumBuff*mSizeOfData];
	}
	
	void appendEnd()
	{
		if(mNumList[mSwap] > 0) {
			cellDmaListGet(mStartBuffPtr,0,mDmaList[mSwap],sizeof(CellDmaListElement)*mNumList[mSwap],mTag,0,0);
		}
		mSwap = 1 - mSwap;
	}
	
	void append(uint32_t id,uint32_t ea)
	{
		if(mIdTable[id]==0xff) {
			PFX_ASSERT(mNumBuff<MAX_BUFF);
			mIdTable[id] = mNumBuff;
			mAddrs[mNumBuff] = ea;
			mDmaList[mSwap][mNumList[mSwap]].eal = ea;

			//PRINTF("append id:%d ls:%x ea:%x\n",id,&mBuffer[mNumBuff*mSizeOfData],ea);

			mNumBuff++;
			mNumList[mSwap]++;
		}
	}

	void wait()
	{
		cellDmaWaitTagStatusAll(1<<mTag);
	}

	inline void *get(uint32_t id)
	{
		return &mBuffer[mIdTable[id]*mSizeOfData];
	}
};

#endif /* __PFX_INDEX_BUFFER_H__ */
