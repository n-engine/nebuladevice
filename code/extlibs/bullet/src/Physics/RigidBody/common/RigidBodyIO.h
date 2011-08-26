/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __RIGIDBODYIO_H__
#define __RIGIDBODYIO_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#ifndef WIN32

///////////////////////////////////////////////////////////////////////////////
// Event

enum {
	// Broadphase Event
	BROADPHASE_CALCVARIANCE = 0,
	BROADPHASE_CREATEPROXIES,
	BROADPHASE_FINDPAIRS_ACTIVE_ACTIVE,
	BROADPHASE_FINDPAIRS_STATIC_ACTIVE,
	BROADPHASE_MERGEPAIRS,
	BROADPHASE_SORT,

	// Narrowphase Event
	NARROWPHASE_FINDCONTACTS,
	
	// Solver Event
	SOLVER_SPLIT_CONSTRAINTS,
	SOLVER_SETUPCONSTRAINTS,
	SOLVER_SOLVECONSTRAINTROWS,
	SOLVER_UPDATEVELOCITY,
	SOLVER_POSTCONSTRAINTS,
};

///////////////////////////////////////////////////////////////////////////////
// Broadphase IO Parameter

struct IOCalcVariance {
	uint32_t statesPtrAddr;
	uint32_t numStates;
	Vector3 s;
	Vector3 s2;
} __attribute__ ((aligned(16)));

struct IOCreateProxies {
	uint32_t statesPtrAddr;
	uint32_t numStates;
	uint32_t activeProxiesAddr;
	uint32_t staticProxiesAddr;
	uint32_t numActiveProxies;
	uint32_t numStaticProxies;
	uint32_t worldVolumeAddr;
	uint32_t chkAxis;
} __attribute__ ((aligned(16)));

struct IOFindPairs {
	uint32_t activeProxyAddr;
	uint32_t staticProxyAddr;
	uint32_t numActiveProxies;
	uint32_t numStaticProxies;
	uint32_t outPairsAddr;
	uint32_t numOutPairs;
	uint32_t maxPairs;
	uint32_t chkAxis;
	uint32_t nonContactPairAddr;
} __attribute__ ((aligned(16)));

struct IOFindContacts {
	uint32_t numContactPairs;
	uint32_t contactPairsAddr;
	uint32_t bytesOfUserObject;
	uint32_t bytesOfUserContact;
} __attribute__ ((aligned(16)));

struct IOSplitConstraints {
	uint32_t numSpu;
	uint32_t maxUniqueId;
	uint32_t numPairs;
	uint32_t pairsAddr;
	uint32_t solverInfoAddr;
	uint32_t solverGroupsAddr;
} __attribute__ ((aligned(16)));

struct IOParallelSort {
	uint32_t numSpu;
	uint32_t buffAddr;
	uint32_t sortsAddr;
	uint32_t numSorts;
} __attribute__ ((aligned(16)));

struct IOMergePairs {
	uint32_t newPairsAddr;
	uint32_t numNewPairs;
	uint32_t oldPairsAddr;
	uint32_t numOldPairs;
	IOParallelSort sortio;
} __attribute__ ((aligned(16)));

///////////////////////////////////////////////////////////////////////////////
// Constraint Solver IO Parameter

struct IOSetupConstraints {
	uint32_t solverInfoAddr;
	uint32_t solverGroupsAddr;
	uint32_t constraintRowsAddr;
	uint32_t constraintsAddr;
	uint32_t bytesOfUserConstraint;
	uint32_t bytesOfUserObject;
	uint32_t numSPU;
	uint32_t maxUniqueId;
} __attribute__ ((aligned(16)));

struct IOSolveConstraintRows {
	uint32_t solverInfoAddr;
	uint32_t solverGroupsAddr;
	uint32_t constraintRowsAddr;
	uint32_t constraintsAddr;
	uint32_t iteration;
	uint32_t numSPU;
	uint32_t maxUniqueId;
} __attribute__ ((aligned(16)));

struct IOUpdateVelocity {
	uint32_t bodiesPtrAddr;
	uint32_t numBodies;
	uint32_t bytesOfUserObject;
} __attribute__ ((aligned(16)));

struct IOPostConstraints {
	uint32_t solverInfoAddr;
	uint32_t solverGroupsAddr;
	uint32_t constraintRowsAddr;
	uint32_t constraintsAddr;
	uint32_t bytesOfUserConstraint;
} __attribute__ ((aligned(16)));

#endif

#endif /* __RIGIDBODYCOLLIO_H__ */

