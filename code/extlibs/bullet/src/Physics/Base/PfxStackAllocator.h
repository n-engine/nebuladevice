/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_STACK_ALLOCATOR_H__
#define __PFX_STACK_ALLOCATOR_H__

#ifdef __SPU__
	#define HEAP_STACK_SIZE 32
#else
	#define HEAP_STACK_SIZE 64
#endif

#define MIN_ALLOC_SIZE 16

///////////////////////////////////////////////////////////////////////////////
// PfxStackAllocator

// ＜補足＞
// メモリはスタックで管理されています。取得した順と逆に開放する必要があります。
// メモリを一気に開放したい場合はclear()を呼び出してください。
// 
// HEAP_MANAGER_DEBUGを定義することでメモリの取得や開放を常にチェックします。
// このとき、チェックが失敗した場合はアサートします。
// 
// 最小割り当てサイズはMIN_ALLOC_SIZEで定義されます。

class PfxStackAllocator
{
private:
	unsigned char *mHeap		__attribute__((aligned(16)));
	unsigned int mHeapBytes		__attribute__((aligned(16)));
	unsigned char *mPoolStack[HEAP_STACK_SIZE]		__attribute__((aligned(16)));
	unsigned int mCurStack		__attribute__((aligned(16)));

public:
	enum {ALIGN16,ALIGN128};

	PfxStackAllocator(unsigned char *buf,int bytes)
	{
		mHeap = buf;
		mHeapBytes = bytes;
		clear();
	}
	
	~PfxStackAllocator()
	{
	}
	
	int getAllocated()
	{
		return (int)(mPoolStack[mCurStack]-mHeap);
	}
	
	int getRest()
	{
		return mHeapBytes-getAllocated();
	}

	int getTotal()
	{
		return (int)mHeapBytes;
	}

#ifdef HEAP_MANAGER_DEBUG

	void *allocate(size_t bytes,int alignment = ALIGN16)
	{
		if(bytes <= 0) bytes = MIN_ALLOC_SIZE;
		if(mCurStack == HEAP_STACK_SIZE-1) {
			PRINTF("PfxStackAllocator : heap stack overflow\n");
			abort();
		}

		unsigned int p = (unsigned int)mPoolStack[mCurStack];

		if(alignment == ALIGN128) {
			p = ((p+127) & 0xffffff80);
			bytes = (bytes+127) & 0xffffff80;
		}
		else {
			bytes = (bytes+15) & 0xfffffff0;
		}

		if( bytes > (mHeapBytes-(p-(unsigned int)mHeap)) ) {
			PRINTF("PfxStackAllocator : heap overflow %d bytes\n",bytes);
			abort();
		}

		mPoolStack[++mCurStack] = (unsigned char *)(p + bytes);
		PRINTF("PfxStackAllocator : allocate addr:0x%x size:%d (rest %d bytes)\n",(uint32_t)p,bytes,getRest());
		return (void*)p;
	}
	
	void deallocate(void *p)
	{
		if(mCurStack == 0) {
			PRINTF("PfxStackAllocator : deallocate error! stack is empty\n");
			abort();
		}
		unsigned int top = (unsigned int)mPoolStack[mCurStack];
		mCurStack--;
		unsigned int addr = (unsigned int)mPoolStack[mCurStack];
		if(addr != (unsigned int)p && ((addr+127) & 0xffffff80) != (unsigned int)p) {
			PRINTF("PfxStackAllocator : deallocate error! invalid address:0x%x (stack 0x%x)\n",(uint32_t)p,(uint32_t)mPoolStack[mCurStack]);
			abort();
		}
		else {
			memset((void*)addr,0,top-addr);
			PRINTF("PfxStackAllocator : deallocate addr:0x%x (rest %d bytes)\n",(uint32_t)p,getRest());
		}
	}
	
	void clear()
	{
		PRINTF("PfxStackAllocator : clear\n");
		memset(mHeap,0,sizeof(mHeap));
		mPoolStack[0] = mHeap;
		mCurStack = 0;
	}

#else

	void *allocate(size_t bytes,int alignment = ALIGN16)
	{
		if(bytes <= 0) bytes = MIN_ALLOC_SIZE;
		if(mCurStack == HEAP_STACK_SIZE-1) {
			PRINTF("HMERR1\n");
			abort();
		}

		unsigned int p = (unsigned int)mPoolStack[mCurStack];

		if(alignment == ALIGN128) {
			p = ((p+127) & 0xffffff80);
			bytes = (bytes+127) & 0xffffff80;
		}
		else {
			bytes = (bytes+15) & 0xfffffff0;
		}

		if( bytes > (mHeapBytes-(p-(unsigned int)mHeap)) ) {
			PRINTF("HMERR2\n");
			abort();
		}

		mPoolStack[++mCurStack] = (unsigned char *)(p + bytes);
		return (void*)p;
	}

	void deallocate(void *p)
	{
		(void) p;
		mCurStack--;
	}
	
	void clear()
	{
		mPoolStack[0] = mHeap;
		mCurStack = 0;
	}

#endif

	void printStack()
	{
		for(unsigned int i=0;i<=mCurStack;i++) {
			PRINTF("memStack %2d 0x%x\n",i,(uint32_t)mPoolStack[i]);
		}
	}
};

#endif
