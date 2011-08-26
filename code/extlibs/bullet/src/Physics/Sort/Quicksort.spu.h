/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __QUICKSORT_SPU_H__
#define __QUICKSORT_SPU_H__

#include "Physics/Base/SortCommon.h"

//	渡されたバッファは4分割して利用するため、
//	4で割り切れる数をnumPrefetchに指定すること
void quickSortSPU(uint32_t start_ea,uint32_t end_ea,int numPrefetch);

#endif /* __QUICKSORT_SPU_H__ */
