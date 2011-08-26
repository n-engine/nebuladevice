/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_PTR_ARRAY_H__
#define __PFX_PTR_ARRAY_H__

#include "PfxDefaultAllocator.h"

///////////////////////////////////////////////////////////////////////////////
// PfxPtrArray

template <class T>
class PfxPtrArray
{
//private:
public:
	PfxAllocator *mAllocator;
	static const int mBlockNum = 1024;
	
	int          mNumData;
	int          mMaxPointer;
	PfxHandle16  *mPointerArray;
	
public:
	PfxPtrArray()
	{
		mAllocator = NULL;
		mPointerArray = NULL;
		mNumData = 0;
		mMaxPointer = 0;
	}
	
	~PfxPtrArray()
	{
		clear();
	}
	
	void setAllocator(PfxAllocator *allocator) {mAllocator = allocator;}
	
	int size() {return mNumData;}
	
	PfxHandle16 *getPointerArray() {return mPointerArray;}
	
	inline PfxHandle16& operator[](uint32_t i);

	inline T& get(uint32_t i);

	inline T& get(PfxHandle id);

	inline bool remove(uint32_t i);

	inline bool remove(PfxHandle id);

	inline PfxHandle create();

	inline void clear();

	inline int  allocatedBytes();
};

template <class T>
inline PfxHandle16& PfxPtrArray<T>::operator[](uint32_t i)
{
	return mPointerArray[i];
}

template <class T>
inline T& PfxPtrArray<T>::get(uint32_t i)
{
	return get(getHdl(mPointerArray[i]));
}

template <class T>
inline T& PfxPtrArray<T>::get(PfxHandle id)
{
	return *((T*)id);
}

template <class T>
inline PfxHandle PfxPtrArray<T>::create()
{
	PfxHandle newHandle = mAllocator->allocateAlign(16,sizeof(T));

	if(mNumData >= mMaxPointer) {
		mMaxPointer += mBlockNum;
		PfxHandle16 *newPool = (PfxHandle16*)mAllocator->allocateAlign(128,sizeof(PfxHandle16)*mMaxPointer);
		if(mPointerArray) {
			memcpy(newPool,mPointerArray,sizeof(PfxHandle16)*(mMaxPointer-mBlockNum));
			mAllocator->deallocate(mPointerArray);
		}
		mPointerArray = newPool;
	}

	setHdl(mPointerArray[mNumData],newHandle);
	mNumData++;

	return newHandle;
}

template <class T>
inline bool PfxPtrArray<T>::remove(uint32_t i)
{
	if(i < (uint32_t)mNumData) {
		mAllocator->deallocate(getHdl(mPointerArray[i]));
		mNumData--;
		setHdl(mPointerArray[i],getHdl(mPointerArray[mNumData]));
		setHdl(mPointerArray[mNumData],NULL);
		return true;
	}
	return false;
}

template <class T>
inline bool PfxPtrArray<T>::remove(PfxHandle id)
{
	for(uint32_t i=0;i<(uint32_t)mNumData;i++) {
		if(id && getHdl(mPointerArray[i]) == id)
			return remove(i);
	}
	return false;
}

template <class T>
inline void PfxPtrArray<T>::clear()
{
	for(uint32_t i=0;i<(uint32_t)mNumData;i++) {
		if(getHdl(mPointerArray[i])) {mAllocator->deallocate(getHdl(mPointerArray[i]));}
	}

	if(mPointerArray) {mAllocator->deallocate(mPointerArray);mPointerArray=NULL;}
	mNumData = 0;
	mMaxPointer = 0;
}

template <class T>
inline int PfxPtrArray<T>::allocatedBytes()
{
	return sizeof(T) * mNumData + sizeof(PfxHandle16) * mMaxPointer;
}

#endif // __PFX_PTR_ARRAY_H__
