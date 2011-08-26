/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PREFETCH_ITERATOR_H__
#define __PREFETCH_ITERATOR_H__

#include <stdint.h>
#include <cell/dma.h>

#include "PhysicsCommon.h"
#include "PfxStackAllocator.h"

///////////////////////////////////////////////////////////////////////////////
// ReadOnlyPrefetchForwardIterator

template <class T>
class ReadOnlyPrefetchForwardIterator
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
	T *mPtrBuf				__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));
	
	void dmaGetBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGet(ls,ea,sz_tmp,tag,0,0);
	}

	void dmaGetBufferf(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGetf(ls,ea,sz_tmp,tag,0,0);
	}

public:
	ReadOnlyPrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag=0);
	~ReadOnlyPrefetchForwardIterator();

	ReadOnlyPrefetchForwardIterator& operator++();
	T& operator*()const{return *mPtrBuf;}
	uint32_t getEA()const{return mEA;}
};

template <class T>
inline
ReadOnlyPrefetchForwardIterator<T>::ReadOnlyPrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mEndEA(endEA),mIndex(0),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(T)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	
	dmaGetBuffer(mBuffer[0],mEA,mPrefetchSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);
	dmaGetBuffer(mBuffer[1],mEA+mPrefetchSize,mPrefetchSize,mDmaTag);
}

template <class T>
inline
ReadOnlyPrefetchForwardIterator<T>::~ReadOnlyPrefetchForwardIterator()
{
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
ReadOnlyPrefetchForwardIterator<T>& ReadOnlyPrefetchForwardIterator<T>::operator++()
{
	mEA+=sizeof(T);
	mIndex++;
	mPtrBuf++;
	if(PFX_UNLIKELY(mIndex>=mPrefetchNum)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);
		dmaGetBuffer(mBuffer[mCurrentBuffer],mEA+mPrefetchSize,mPrefetchSize,mDmaTag);
		mCurrentBuffer=1-mCurrentBuffer;mIndex=0;
		mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// WriteOnlyPrefetchForwardIterator

template <class T>
class WriteOnlyPrefetchForwardIterator
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
	T *mPtrBuf				__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));
	
	void dmaPutBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaPut(ls,ea,sz_tmp,tag,0,0);
	}
	
public:
	WriteOnlyPrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag=0);
	~WriteOnlyPrefetchForwardIterator();

	WriteOnlyPrefetchForwardIterator& operator++();
	T& operator*()const{return *mPtrBuf;}
	uint32_t getEA()const{return mEA;}
};

template <class T>
inline
WriteOnlyPrefetchForwardIterator<T>::WriteOnlyPrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mEndEA(endEA),mIndex(0),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(T)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	
}

template <class T>
inline
WriteOnlyPrefetchForwardIterator<T>::~WriteOnlyPrefetchForwardIterator()
{
	dmaPutBuffer(mBuffer[mCurrentBuffer],mEA-(mIndex*sizeof(T)),(mIndex*sizeof(T)),mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
WriteOnlyPrefetchForwardIterator<T>& WriteOnlyPrefetchForwardIterator<T>::operator++()
{
	mEA+=sizeof(T);
	mIndex++;
	mPtrBuf++;
	if(PFX_UNLIKELY(mIndex>=mPrefetchNum)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);
		dmaPutBuffer(mBuffer[mCurrentBuffer],mEA-mPrefetchSize,mPrefetchSize,mDmaTag);
		mCurrentBuffer=1-mCurrentBuffer;mIndex=0;
		mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// PrefetchForwardIterator

template <class T>
class PrefetchForwardIterator
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
	T *mPtrBuf				__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));
	
	void dmaGetBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGet(ls,ea,sz_tmp,tag,0,0);
	}

	void dmaGetBufferf(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaGetf(ls,ea,sz_tmp,tag,0,0);
	}

	void dmaPutBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		int32_t sz_tmp = (ea+sz <= mEndEA)?sz:mEndEA-ea;
		if(sz_tmp < 0) sz_tmp = 0;
		cellDmaPut(ls,ea,sz_tmp,tag,0,0);
	}
	
public:
	PrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag=0);
	~PrefetchForwardIterator();

	PrefetchForwardIterator& operator++();
	T& operator*()const{return *mPtrBuf;}
	uint32_t getEA()const{return mEA;}
};

template <class T>
inline
PrefetchForwardIterator<T>::PrefetchForwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t endEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mEndEA(endEA),mIndex(0),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(T)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	
	dmaGetBuffer(mBuffer[0],mEA,mPrefetchSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);
	dmaGetBuffer(mBuffer[1],mEA+mPrefetchSize,mPrefetchSize,mDmaTag);
}

template <class T>
inline
PrefetchForwardIterator<T>::~PrefetchForwardIterator()
{
	dmaPutBuffer(mBuffer[mCurrentBuffer],mEA-(mIndex*sizeof(T)),(mIndex*sizeof(T)),mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
PrefetchForwardIterator<T>& PrefetchForwardIterator<T>::operator++()
{
	mEA+=sizeof(T);
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
// ReadOnlyPrefetchBackwardIterator

template <class T>
class ReadOnlyPrefetchBackwardIterator
{
private:
	PfxStackAllocator *mPool;

	const int mDmaTag		__attribute__((aligned(16)));
	int mPrefetchNum		__attribute__((aligned(16)));
	int mPrefetchSize		__attribute__((aligned(16)));
	uint32_t mEA 			__attribute__((aligned(16)));
	uint32_t mStartEA		__attribute__((aligned(16)));
	int mIndex 				__attribute__((aligned(16)));
	int mCurrentBuffer		__attribute__((aligned(16)));
	T *mPtrBuf				__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));

	void dmaGetBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		if(PFX_LIKELY(ea >= mStartEA)) {
			cellDmaGet(ls,ea,sz,tag,0,0);
		}
		else {
			sz = ea+sz-mStartEA;
			ls += (mStartEA - ea)/sizeof(T);
			if(sz > 0) {
				cellDmaGet(ls,mStartEA,sz,tag,0,0);
			}
		}
	}

	void dmaGetBufferf(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		if(PFX_LIKELY(ea >= mStartEA)) {
			cellDmaGetf(ls,ea,sz,tag,0,0);
		}
		else {
			sz = ea+sz-mStartEA;
			ls += (mStartEA - ea)/sizeof(T);
			if(sz > 0) {
				cellDmaGetf(ls,mStartEA,sz,tag,0,0);
			}
		}
	}

public:
	ReadOnlyPrefetchBackwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t startEA,int prefetchNum,int tag=0);
	~ReadOnlyPrefetchBackwardIterator();

	ReadOnlyPrefetchBackwardIterator& operator--();
	T& operator*()const{return *mPtrBuf;}
	unsigned int getEA()const{return mEA;}
};

template <class T>
inline
ReadOnlyPrefetchBackwardIterator<T>::ReadOnlyPrefetchBackwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t startEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mStartEA(startEA),mIndex(prefetchNum),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(T)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;

	dmaGetBuffer(mBuffer[0],mEA-mPrefetchSize,mPrefetchSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);
	dmaGetBuffer(mBuffer[1],mEA-mPrefetchSize*2,mPrefetchSize,mDmaTag);
}

template <class T>
inline
ReadOnlyPrefetchBackwardIterator<T>::~ReadOnlyPrefetchBackwardIterator()
{
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
ReadOnlyPrefetchBackwardIterator<T>& ReadOnlyPrefetchBackwardIterator<T>::operator--()
{
	mEA-=sizeof(T);
	mIndex--;
	mPtrBuf--;
	if(PFX_UNLIKELY(mIndex<0)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);
		dmaGetBuffer(mBuffer[mCurrentBuffer],mEA-mPrefetchSize*2+sizeof(T),mPrefetchSize,mDmaTag);
		mCurrentBuffer=1-mCurrentBuffer;mIndex=mPrefetchNum-1;
		mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// PrefetchBackwardIterator

template <class T>
class PrefetchBackwardIterator
{
private:
	PfxStackAllocator *mPool;

	const int mDmaTag		__attribute__((aligned(16)));
	int mPrefetchNum		__attribute__((aligned(16)));
	int mPrefetchSize		__attribute__((aligned(16)));
	uint32_t mEA 			__attribute__((aligned(16)));
	uint32_t mStartEA		__attribute__((aligned(16)));
	int mIndex 				__attribute__((aligned(16)));
	int mCurrentBuffer		__attribute__((aligned(16)));
	T *mPtrBuf				__attribute__((aligned(16)));
	T *mBuffer[2]			__attribute__((aligned(128)));

	void dmaGetBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		if(PFX_LIKELY(ea >= mStartEA)) {
			cellDmaGet(ls,ea,sz,tag,0,0);
		}
		else {
			sz = ea+sz-mStartEA;
			ls += (mStartEA - ea)/sizeof(T);
			if(sz > 0) {
				cellDmaGet(ls,mStartEA,sz,tag,0,0);
			}
		}
	}

	void dmaGetBufferf(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		if(PFX_LIKELY(ea >= mStartEA)) {
			cellDmaGetf(ls,ea,sz,tag,0,0);
		}
		else {
			sz = ea+sz-mStartEA;
			ls += (mStartEA - ea)/sizeof(T);
			if(sz > 0) {
				cellDmaGetf(ls,mStartEA,sz,tag,0,0);
			}
		}
	}

	void dmaPutBuffer(T* ls,uint32_t ea,int32_t sz,uint32_t tag)
	{
		if(PFX_LIKELY(ea >= mStartEA)) {
			cellDmaPut(ls,ea,sz,tag,0,0);
		}
		else {
			sz = ea+sz-mStartEA;
			ls += (mStartEA - ea)/sizeof(T);
			if(sz > 0) {
				cellDmaPut(ls,mStartEA,sz,tag,0,0);
			}
		}
	}

public:
	PrefetchBackwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t startEA,int prefetchNum,int tag=0);
	~PrefetchBackwardIterator();

	PrefetchBackwardIterator& operator--();
	T& operator*()const{return *mPtrBuf;}
	unsigned int getEA()const{return mEA;}
};

template <class T>
inline
PrefetchBackwardIterator<T>::PrefetchBackwardIterator(PfxStackAllocator *pool,uint32_t initialEA,uint32_t startEA,int prefetchNum,int tag)
	:mPool(pool),mDmaTag(tag),mPrefetchNum(prefetchNum),mEA(initialEA),mStartEA(startEA),mIndex(prefetchNum),mCurrentBuffer(0)
{
	mBuffer[0] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mBuffer[1] = (T*)mPool->allocate(sizeof(T)*mPrefetchNum,PfxStackAllocator::ALIGN128);
	mPrefetchSize = sizeof(T)*prefetchNum;
	mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;

	dmaGetBuffer(mBuffer[0],mEA-mPrefetchSize,mPrefetchSize,mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);
	dmaGetBuffer(mBuffer[1],mEA-mPrefetchSize*2,mPrefetchSize,mDmaTag);
}

template <class T>
inline
PrefetchBackwardIterator<T>::~PrefetchBackwardIterator()
{
	dmaPutBuffer(mBuffer[mCurrentBuffer]+mIndex,mEA,mPrefetchSize-(mIndex*sizeof(T)),mDmaTag);
	cellDmaWaitTagStatusAll(1<<mDmaTag);

	mPool->deallocate(mBuffer[1]);
	mPool->deallocate(mBuffer[0]);
}

template <class T>
inline
PrefetchBackwardIterator<T>& PrefetchBackwardIterator<T>::operator--()
{
	mEA-=sizeof(T);
	mIndex--;
	mPtrBuf--;
	if(PFX_UNLIKELY(mIndex<0)) {
		cellDmaWaitTagStatusAll(1<<mDmaTag);
		dmaPutBuffer(mBuffer[mCurrentBuffer],mEA+sizeof(T),mPrefetchSize,mDmaTag);
		dmaGetBufferf(mBuffer[mCurrentBuffer],mEA-mPrefetchSize*2+sizeof(T),mPrefetchSize,mDmaTag);
		mCurrentBuffer=1-mCurrentBuffer;mIndex=mPrefetchNum-1;
		mPtrBuf=mBuffer[mCurrentBuffer]+mIndex;
	}
	return *this;
}

#endif /*__PREFETCH_ITERATOR_H__*/

