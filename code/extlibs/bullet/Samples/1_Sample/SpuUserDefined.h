/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __USER_OBJECT_H__
#define __USER_OBJECT_H__

#include "Physics/LowLevelPhysics.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#define CONTACT_THRESHOLD_NORMAL	0.01f	// 衝突点の閾値（法線方向）
#define CONTACT_THRESHOLD_TANGENT	0.002f	// 衝突点の閾値（平面上）

struct UserBody {
	int uniqueId;
	plBroadphaseProxyHandle proxy;
	plShapeHandle shape;
	plSolverBodyHandle solverBody;
	float restitution;
	float friction;
	float mass;
	float invMass;
	Vector3 center;
	Vector3 extent;
	Matrix3 inertia;
	Matrix3 invInertia;
	Vector3 position;
	Quat orientation;
	Vector3 linearVelocity;
	Vector3 angularVelocity;
	
	UserBody()
	{
		uniqueId = 0;
		proxy = 0;
		shape = 0;
		solverBody = 0;
		restitution = 0.0f;
		friction = 0.6f;
		mass = 1.0f;
		center = Vector3(0.0f);
		extent = Vector3(1.0f);
		inertia = Matrix3::identity();
		position = Vector3(0.0f);
		orientation = Quat::identity();
		linearVelocity = Vector3(0.0f);
		angularVelocity = Vector3(0.0f);
	}
#ifdef WIN32
};
#else
} __attribute__ ((aligned(16)));
#endif

struct UserContactPoint {
	float   distance;
	float   accumlatedImpulse[3];
	Vector3 normal;
	Vector3 localPointA;
	Vector3 localPointB;
};

struct UserContactManifold {
	UserBody *bodyA,*bodyB;
	int numContactPoints;
	UserContactPoint contactPoints[4];
#ifdef WIN32
};
#else
} __attribute__ ((aligned(16)));
#endif

//E Add contact points to the contact manifold.
//E The contact manifold can hold upto 4 contact points. 
void addContactPoint(UserContactManifold *contactManifold,
	Vector3 &normal,float distance,Vector3 &localPointA,Vector3 &localPointB);

//E Check contact points whether they are vaild or not.
//E If a local contact point are separated, then it will be removed.
void refeshContactManifold(UserContactManifold *contactManifold,
	const Vector3 &pA,const Quat &qA,const Vector3 &pB,const Quat &qB);

#endif /* __USER_OBJECT_H__ */