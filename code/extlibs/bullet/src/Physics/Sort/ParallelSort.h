/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PARALLELSORT_H__
#define __PARALLELSORT_H__

#define SORT_PREFETCH_NUM		2048
#define MERGE_PREFETCH_NUM		32

class PfxStackAllocator;

struct ParallelSortConfig {
	uint32_t taskId;
	uint32_t numSpu;
	uint32_t barrier;
	PfxStackAllocator *pool;
};

void parallelSort(uint32_t sortsAddr,uint32_t buffAddr,uint32_t numSorts,const ParallelSortConfig &config);

#endif /* __PARALLELSORT_H__ */
