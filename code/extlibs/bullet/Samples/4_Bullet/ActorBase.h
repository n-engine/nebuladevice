/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __ACTORBASE_H__
#define __ACTORBASE_H__

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "CustomPad.h"

class ActorBase
{
protected:
	btRigidBody *mRigidBody;

public:
	ActorBase() {}
	virtual ~ActorBase() {}
	
	virtual void setRigidBody(btRigidBody *rigidBody)
	{
		mRigidBody = rigidBody;
	}

	btRigidBody* getRigidBody ()
	{
		return mRigidBody;
	}
	
	virtual void reset() = 0;

	virtual void preUpdate() {}
	virtual void update() {}
	virtual void postUpdate() {}
};

#endif /* __ACTORBASE_H__ */
