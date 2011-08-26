#ifndef __PREFETCH_POINTER_ITERATOR_H__
#define __PREFETCH_POINTER_ITERATOR_H__

#include "Physics/Base/PfxHandle.h"

///////////////////////////////////////////////////////////////////////////////
// PtrIterator

class PtrIterator
{
private:
	PfxStackAllocator *mPool		__attribute__((aligned(16)));

	const int mDmaTag		__attribute__((aligned(16)));
	int mPrefetchNum		__attribute__((aligned(16)));
	int mPrefetchSize		__attribute__((aligned(16)));
	uint32_t mEA 			__attribute__((aligned(16)));
	uint32_t mEndEA			__attribute__((aligned(16)));
	int mIndex 				__attribute__((aligned(16)));
	int mCurrentBuffer		__attribute__((aligned(16)));
	PfxHandle16 *mPtrBuf				__attribute__((aligned(16)));
	PfxHandle16 *mBuffer[2]			__attribute__((aligned(128)));
	
	void dmaGetBuffer(PfxHandle16* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGet(ls,ea,sz_tmp,tag,0,0);
	}

	void dmaGetBufferf(PfxHandle16* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGetf(ls,ea,sz_tmp,tag,0,0);
	}

	void dmaPutBuffer(PfxHandle16* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaPut(ls,ea,sz_tmp,tag,0,0);
	}
	
public:
	PtrIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag=0);
	~PtrIterator();

	PtrIterator& operator++();
	PfxHandle16& operator*()const{return *mPtrBuf;}
	uint32_t getEA()const{return mEA;}
};

inline
PtrIterator::PtrIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mEndEA(endEA),mIndex(0),mCurrentBuffer(0)
{
	mBuffer[0] = (PfxHandle16*)mPool->allocate(sizeof(PfxHandle16)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (PfxHandle16*)mPool->allocate(sizeof(PfxHandle16)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(PfxHandle16)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	
	dmaGetBuffer(mBuffer[0],mEA,mPrefetchSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);
	dmaGetBuffer(mBuffer[1],mEA+mPrefetchSize,mPrefetchSize,mDmaTag);
}

inline
PtrIterator::~PtrIterator()
{
	uint32_t buffSize = mIndex*sizeof(PfxHandle16);
	dmaPutBuffer(mBuffer[mCurrentBuffer],mEA-buffSize,buffSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

inline
PtrIterator& PtrIterator::operator++()
{
	mEA+=sizeof(PfxHandle16);
	mIndex++;
	mPtrBuf++;
	if(PFX_UNLIKELY(mIndex>=mPrefetchNum)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);
		dmaPutBuffer(mBuffer[mCurrentBuffer],mEA-mPrefetchSize,mPrefetchSize,mDmaTag);
		dmaGetBufferf(mBuffer[mCurrentBuffer],mEA+mPrefetchSize,mPrefetchSize,mDmaTag);
		mCurrentBuffer=1-mCurrentBuffer;mIndex=0;
		mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// PrefetchForwardPtrIterator

template <class T>
class PrefetchForwardPtrIterator
{
private:
	PtrIterator itrPtr;

	PfxStackAllocator *mPool		__attribute__((aligned(16)));

	const int mDmaTag		__attribute__((aligned(16)));
	int mPrefetchNum		__attribute__((aligned(16)));
	int mTotalNum			__attribute__((aligned(16)));
	int mIndex 				__attribute__((aligned(16)));
	int mCurrentBuffer		__attribute__((aligned(16)));
	int mNumPtrs[2];
	T *mPtr					__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));
	CellDmaListElement *mDmaList[3] __attribute__((aligned(16)));
	
	int p,q;
	
public:
	PrefetchForwardPtrIterator(PfxStackAllocator *pool,uint32_t ptrAddr,int totalNum,int prefetchNum,int tag0,int tag1);
	~PrefetchForwardPtrIterator();

	void* getAddr() {return (void*)mDmaList[mCurrentBuffer][mIndex].eal;}

	PrefetchForwardPtrIterator& operator++();
	T& operator*()const{return *mPtr;}
};

template <class T>
inline
PrefetchForwardPtrIterator<T>::PrefetchForwardPtrIterator(PfxStackAllocator *pool,uint32_t ptrAddr,int totalNum,int prefetchNum,int tag0,int tag1)
	:itrPtr(pool,ptrAddr,ptrAddr+sizeof(PfxHandle16)*totalNum,prefetchNum*4,tag0),mPool(pool),mDmaTag(tag1),mPrefetchNum(prefetchNum),mTotalNum(totalNum),mIndex(0),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mDmaList[0] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mPrefetchNum);
	mDmaList[1] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mPrefetchNum);
	mDmaList[2] = (CellDmaListElement*)mPool->allocate(sizeof(CellDmaListElement)*mPrefetchNum);
	
	mPtr=mBuffer[mCurrentBuffer]+mIndex;
	
	p = q = 0;

	for(p=0;p<mPrefetchNum;p++) {
		mDmaList[0][p].notify = 0;
		mDmaList[0][p].size = sizeof(T);
		mDmaList[1][p].notify = 0;
		mDmaList[1][p].size = sizeof(T);
	}

	for(p=0;p<mPrefetchNum&&q<(int)mTotalNum;p++,q++,++itrPtr) {
		mDmaList[0][p].eal = (uint32_t)getHdl(*itrPtr);
	}
	mNumPtrs[0] = p;

	cellDmaListGet(mBuffer[0],0,mDmaList[0],sizeof(CellDmaListElement)*mNumPtrs[0],mDmaTag,0,0);

	for(p=0;p<mPrefetchNum&&q<(int)mTotalNum;p++,q++,++itrPtr) {
		mDmaList[1][p].eal = (uint32_t)getHdl(*itrPtr);
	}
	mNumPtrs[1] = p;

	cellDmaWaitTagStatusAll(1<<mDmaTag);
	cellDmaListGet(mBuffer[1],0,mDmaList[1],sizeof(CellDmaListElement)*mNumPtrs[1],mDmaTag,0,0);
}

template <class T>
inline
PrefetchForwardPtrIterator<T>::~PrefetchForwardPtrIterator()
{
	cellDmaListPut(mBuffer[mCurrentBuffer],0,mDmaList[mCurrentBuffer],sizeof(CellDmaListElement)*mNumPtrs[mCurrentBuffer],mDmaTag,0,0);
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mDmaList[2]);
	mPool->deallocate(mDmaList[1]);
	mPool->deallocate(mDmaList[0]);
	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
PrefetchForwardPtrIterator<T>& PrefetchForwardPtrIterator<T>::operator++()
{
	mIndex++;
	mPtr++;
	if(PFX_UNLIKELY(mIndex>=mPrefetchNum)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);

		memcpy(mDmaList[2],mDmaList[mCurrentBuffer],sizeof(CellDmaListElement)*mNumPtrs[mCurrentBuffer]);
		cellDmaListPut(mBuffer[mCurrentBuffer],0,mDmaList[2],sizeof(CellDmaListElement)*mNumPtrs[mCurrentBuffer],mDmaTag,0,0);
		for(p=0;p<mPrefetchNum&&q<mTotalNum;p++,q++,++itrPtr) {
			mDmaList[mCurrentBuffer][p].eal = (uint32_t)getHdl(*itrPtr);
		}
		mNumPtrs[mCurrentBuffer] = p;
		cellDmaListGetf(mBuffer[mCurrentBuffer],0,mDmaList[mCurrentBuffer],sizeof(CellDmaListElement)*mNumPtrs[mCurrentBuffer],mDmaTag,0,0);
		
		mIndex=0;
		mCurrentBuffer=1-mCurrentBuffer;
		mPtr=mBuffer[mCurrentBuffer];
	}
	return *this;
}

#endif /* __PREFETCH_POINTER_ITERATOR_H__ */
