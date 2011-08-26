/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICS_ACTOR_H__
#define __PHYSICS_ACTOR_H__

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "ActorBase.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

class CommonRigidBody;

///////////////////////////////////////////////////////////////////////////////
// Actor

class PhysicsActor : public ActorBase
{
private:
	float turnAngle;
	int jumpCount;
	bool jumping;
	bool catching;

	CustomPad *pad;

public:
	btVector3 m_raySource[5];
	btVector3 m_rayDest[5];
	btScalar m_rayHitFraction[5];
	btVector3 m_rayDirection[5];
	btVector3 m_rayHitPoint[5];
	btVector3 m_rayHitNormal[5];
	int numRays;

	static void initPhysicsActor()
	{
		bodyExists = false;
	}

	void setCustomPad(CustomPad &customPad)
	{
		pad = &customPad;
	}

	void reset()
	{
		jumping = false;
		catching = false;
		turnBody = false;
		angleX = angleY = targetAngleX = targetAngleY = 0.0f;
		turnAngle = 0.0f;
		numRays = 5;
#if 0
		for(int i=0;i<numRays;i++)
			rays[i].startPos = rays[i].endPos = Vector3(0);
#endif
	}

	bool canCatch()
	{
		return false;
#if 0
		return rays[4].contactFlag &&  
			!jointCatcher->isActive() &&
			mRigidBodies->getMoveType(rays[4].contactInstance) != MoveTypeFixed;
#endif
	}

	bool canRelease()
	{
		return false;
#if 0
		return jointCatcher->isActive();
#endif
	}

	void setRays();

	void preUpdate();
	void update();
	void postUpdate();

	static bool bodyExists;

	CommonRigidBody *actorBody;
	CommonRigidBody *catcher;

	//Joint *jointBodyAndCatcher;
	//Joint *jointBodyAndGruound;
	//Joint *jointCatcher;

	Matrix3 defaultRot;

	Vector3 targetCenter,targetVecL,targetVecR;
	float angleX,angleY,targetAngleX,targetAngleY;

	// ターン
	bool turnBody;
	int turnBodyWait;
};

#endif
