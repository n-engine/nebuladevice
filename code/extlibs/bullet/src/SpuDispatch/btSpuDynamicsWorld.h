/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef BT_SPU_DYNAMICS_WORLD
#define BT_SPU_DYNAMICS_WORLD

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

class btSpuDynamicsWorld : public btDiscreteDynamicsWorld
{
protected:
	virtual void predictUnconstraintMotion (btScalar timeStep);
	virtual void internalSingleStepSimulation (btScalar timeStep);
	// can make other methods of btDiscreteDynamicsWorld virtual as needed for optimizations.
public:
	btSpuDynamicsWorld (btDispatcher* dispatcher,btBroadphaseInterface* pairCache,btConstraintSolver* constraintSolver,btCollisionConfiguration* collisionConfiguration);
	virtual ~btSpuDynamicsWorld ();

        virtual btDynamicsWorldType getWorldType() const
	{
		return BT_DISCRETE_DYNAMICS_WORLD;
	}
};

#endif

