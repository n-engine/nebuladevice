#ifndef _BT_LOW_LEVEL_DYNAMICS_WORLD_H
#define _BT_LOW_LEVEL_DYNAMICS_WORLD_H

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"

class btLowLevelConstraintSolver;
class btThreadSupportInterface;
class SpuPEGatherScatterTaskProcess;
class CellSpurs;
class SpuBatchRaycaster;

#ifdef __PPU__
#define USE_PE_GATHER_SCATTER_SPURS_TASK 1
#define PARALLEL_BATCH_SIZE 64
#endif //__PPU__

//#define USE_BATCH_RAYCASTER 1

///btLowLevelDynamicsWorld benefits from several SPU optimizations
class btLowLevelDynamicsWorld : public btDiscreteDynamicsWorld
{
	btLowLevelConstraintSolver*	m_lowLevelConstraintSolver;

	class btThreadSupportInterface*			m_PEGatherScatterSpursSupport;

	class SpuPEGatherScatterTaskProcess*	m_PEGatherScatterProcess;

#ifdef USE_BATCH_RAYCASTER
	class btThreadSupportInterface* m_batchRaycasterThreadSupport;

	SpuBatchRaycaster*	m_batchRayCaster;
#endif //USE_BATCH_RAYCASTER

	bool	m_useIslands;

	public:

	btLowLevelDynamicsWorld(btDispatcher* dispatcher,btBroadphaseInterface* pairCache,btLowLevelConstraintSolver* constraintSolver,btCollisionConfiguration* collisionConfiguration,CellSpurs* spursInstance);
		
	virtual ~btLowLevelDynamicsWorld();
	
	virtual void	addCollisionObject(btCollisionObject* collisionObject,short int collisionFilterGroup=btBroadphaseProxy::StaticFilter,short int collisionFilterMask=btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

	virtual void	removeCollisionObject(btCollisionObject* collisionObject);

	virtual void	addRigidBody(btRigidBody* body);

	virtual void	addRigidBody(btRigidBody* body, short group, short mask);

	virtual void	removeRigidBody(btRigidBody* body);

	virtual void	addConstraint(btTypedConstraint* constraint, bool disableCollisionsBetweenLinkedBodies=false);

	virtual void	removeConstraint(btTypedConstraint* constraint);
	
	virtual void	internalSingleStepSimulation(btScalar timeStep);

	virtual	void	solveConstraints(btContactSolverInfo& solverInfo);

	virtual void	performDiscreteCollisionDetection();
	
	virtual void	predictUnconstraintMotion(btScalar timeStep);
		
	virtual void integrateTransforms(btScalar timeStep);

	void	setUseIslands(bool useIslands)
	{
		m_useIslands = useIslands;
	}

	void	rayTestBatch(int numRays,const btVector3* rayFromArray,const btVector3* rayToArray,btScalar* rayHitFractionArray,btVector3* rayHitPointArray,btVector3* rayHitNormalArray,RayResultCallback& resultCallback);

#ifdef USE_BATCH_RAYCASTER
	SpuBatchRaycaster*	getBatchRayCaster()
	{
		return m_batchRayCaster;
	}
#endif //USE_BATCH_RAYCASTER


};
#endif //_BT_LOW_LEVEL_DYNAMICS_WORLD_H