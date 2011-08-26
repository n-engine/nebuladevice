/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PARALLEL_GROUP_H__
#define __PARALLEL_GROUP_H__

///////////////////////////////////////////////////////////////////////////////
// Parallel Pair Group

#define MAX_SOLVER_PHASES 64	// 最大フェーズ数
#define MAX_SOLVER_GROUPS 16	// １フェーズに含まれる最大並列処理グループ
#define MAX_SOLVER_PAIRS  128	// １グループに含まれる最大ペア数
#define MIN_SOLVER_PAIRS  16

struct SolverGroup {
	uint16_t pairIndices[MAX_SOLVER_PAIRS];
} __attribute__ ((aligned(128)));

struct SolverInfo {
	uint16_t numPhases;
	uint16_t numGroups[MAX_SOLVER_PHASES];
	uint16_t numPairs[MAX_SOLVER_PHASES*MAX_SOLVER_GROUPS];
} __attribute__ ((aligned(16)));

#endif /* __PARALLEL_GROUP_H__ */
