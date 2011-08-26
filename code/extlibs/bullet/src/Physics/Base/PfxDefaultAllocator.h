/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_DEFAULT_ALLOCATOR_H__
#define __PFX_DEFAULT_ALLOCATOR_H__

#ifdef WIN32
	#include <psapi.h>
	#pragma comment(lib,"psapi.lib")
#else
	#include <sys/memory.h>
	//#define USE_MSPACE
#endif

#include "PfxAllocator.h"

///////////////////////////////////////////////////////////////////////////////
// PfxAllocator (mspace)

#ifdef USE_MSPACE

#include <mspace.h>

class PfxDefaultAllocator : public PfxAllocator {
private:
	std::mspace mMemSpace;
	void *mPool;
	
public:
	PfxDefaultAllocator(size_t preAllocatedBytes=0)
	{
		if(CELL_OK != sys_memory_allocate(preAllocatedBytes,SYS_MEMORY_PAGE_SIZE_64K,(sys_addr_t*)&mPool)) {
			PRINTF("can't allocate heap.");
			abort();
		}
		
		mMemSpace = std::mspace_create(mPool,preAllocatedBytes);
	}

	virtual ~PfxDefaultAllocator()
	{
		if(mspace_is_heap_empty(mMemSpace)) {
			std::mspace_destroy(mMemSpace);
		}
		else {
			PRINTF("Heap is not empty.");
			abort();
		}
		
		sys_memory_free((sys_addr_t)mPool);
	}

	virtual void *allocate(size_t size)
	{
		return std::mspace_malloc(mMemSpace,size);
	}

	virtual void *reallocate(void* ptr,size_t size)
	{
		return std::mspace_realloc(mMemSpace,ptr,size);
	}

	virtual void *allocateAlign(size_t boundary,size_t size)
	{
		return std::mspace_memalign(mMemSpace,boundary,size);
	}

	virtual void deallocate(void *ptr)
	{
		return std::mspace_free(mMemSpace,ptr);
	}
	
	virtual size_t allocatedBytes()
	{
		std::malloc_managed_size msize;
		std::mspace_malloc_stats(mMemSpace,&msize);
		return msize.current_inuse_size;
	}
};

#else // USE_MSPACE

///////////////////////////////////////////////////////////////////////////////
// PfxAllocator

class PfxDefaultAllocator : public PfxAllocator {
public:
	PfxDefaultAllocator(size_t preAllocatedBytes=0)
	{
	}

	virtual ~PfxDefaultAllocator()
	{
	}

	virtual void *allocate(size_t size)
	{
		void *p = ::malloc(size);
		return p;
	}

	virtual void *reallocate(void* ptr,size_t size)
	{
		void *p = ::realloc(ptr,size);
		return p;
	}

	virtual void *allocateAlign(size_t boundary,size_t size)
	{
#ifdef WIN32
		void *p = allocate(size);
#else
		void *p = ::memalign(boundary,size);
#endif
		return p;
	}

	virtual void deallocate(void *ptr)
	{
		return ::free(ptr);
	}
	
	virtual size_t allocatedBytes()
	{
#ifdef WIN32
		PROCESS_MEMORY_COUNTERS msize;
		GetProcessMemoryInfo(GetCurrentProcess(),&msize,sizeof(msize));
		return msize.PagefileUsage;
#else
		std::malloc_managed_size msize;
		std::malloc_stats(&msize);
		return msize.current_inuse_size;
#endif
	}
};

#endif // USE_MSPACE

#endif /* __PFX_DEFAULT_ALLOCATOR_H__ */
