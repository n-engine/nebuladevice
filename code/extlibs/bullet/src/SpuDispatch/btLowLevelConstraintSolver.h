
#ifndef BT_LOW_LEVEL_SOLVER_BINDING_H
#define BT_LOW_LEVEL_SOLVER_BINDING_H

#include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#include "btLowLevelConstraintSolver.h"
#include "Physics/LowLevelPhysics.h"

#ifdef __PPU__
#define USE_PE_GATHER_SCATTER_SPURS_TASK 1
#define PARALLEL_BATCH_SIZE 64
#endif //__PPU__


class btLowLevelConstraintSolver : public btConstraintSolver
{

	plConstraintSolverHandle	m_ConstraintSolver;
	
public:

	int m_recentNumConstraints;

	btLowLevelConstraintSolver(class PfxDefaultAllocator* allocator,class PfxStackAllocator* stackPool,class CellSpurs* spursInstance,int maxNumSpu);

	plConstraintSolverHandle	getLLSolver() 
	{
		return m_ConstraintSolver;
	}

	virtual ~btLowLevelConstraintSolver();

	///solve a group of constraints
	virtual btScalar solveGroup(btCollisionObject** bodies,int numBodies,btPersistentManifold** manifold,int numManifolds,btTypedConstraint** constraints,int numConstraints, const btContactSolverInfo& info,class btIDebugDraw* debugDrawer, btStackAlloc* stackAlloc,btDispatcher* dispatcher);

	///clear internal cached data and reset random seed
	virtual	void	reset();

	virtual void	setNumTasks(int numTasks);
	
	virtual void	setUseSpu(bool useSpu);
};


#endif //BT_LOW_LEVEL_SOLVER_BINDING_H