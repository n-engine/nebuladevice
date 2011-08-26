#ifndef __PFX_CONSTRAINT_SOLVER_H__
#define __PFX_CONSTRAINT_SOLVER_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PerfCounter.h"
#include "Physics/Base/SortCommon.h"
#include "Physics/Base/PfxAllocator.h"
#include "Physics/Base/PfxStackAllocator.h"
#include "Physics/Base/PfxPtrArray.h"
#include "Physics/RigidBody/common/PfxConstraint.h"

#ifdef __PPU__
	#include "Util/PELowLevelTask.h"
#endif

struct ConstraintSolverConfig {
	float timeStep;
	int iteration;

	PfxAllocator *allocator;
	PfxStackAllocator *stackAllocator;

	uint32_t numTasks;
	uint32_t maxUniqueId;
	uint32_t bytesOfUserObject;
	uint32_t bytesOfUserConstraint;

#ifdef __PPU__
	PELowLevelTask *task;
#endif
};

#ifdef __cplusplus
extern "C" { 
#endif

void solveConstraints(PfxPtrArray<PfxSolverBody> &solverBodies,PfxGenericConstraintRow *constraintRows,
	PfxConstraintPtr *constraints,uint32_t numConstraints,ConstraintSolverConfig &config);

#ifdef __PPU__

void solveConstraintsSPU(PfxPtrArray<PfxSolverBody> &solverBodies,PfxGenericConstraintRow *constraintRows,
	PfxConstraintPtr *constraints,uint32_t numConstraints,ConstraintSolverConfig &config);

#endif

struct PfxConstraintSolver {
	ConstraintSolverConfig config;

	PfxPtrArray<PfxSolverBody> solverBodies;

	PfxConstraintPtr *constraints;
	uint32_t numConstraints;
	uint32_t maxCachedConstraints;
	
	// temporal buffer
	PfxGenericConstraintRow *constraintRows;
	uint32_t numConstraintRows;

	bool useSPU;
};


#ifdef __cplusplus
}
#endif

#endif /* __PFX_CONSTRAINT_SOLVER_H__ */
