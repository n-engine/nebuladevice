/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef __BULLET_RIGIDBODY_H__
#define __BULLET_RIGIDBODY_H__


class btCollisionObject;
#include "CommonRigidBody.h"
#include "BulletMultiThreaded/Vectormath2Bullet.h"
#include "btBulletDynamicsCommon.h"


///////////////////////////////////////////////////////////////////////////////
// BulletRigidBody

class BulletRigidBody : public CommonRigidBody
{
private:

	btCollisionObject* m_rigidBody;

public:
	BulletRigidBody(btCollisionObject* body)
	: CommonRigidBody(0),
		m_rigidBody(body)
	{
	}
	
	Vector3 getPosition() 
	{
		const btVector3& pos = m_rigidBody->getWorldTransform().getOrigin();
		return Vector3(pos.getX(),pos.getY(),pos.getZ());
	}
		
	Matrix3	getRotation() 
	{
		const btMatrix3x3& mat = m_rigidBody->getWorldTransform().getBasis();
		btVector3 col0 = mat.getColumn(0);
		btVector3 col1 = mat.getColumn(1);
		btVector3 col2 = mat.getColumn(2);
		return Matrix3(Vector3(col0.getX(),col0.getY(),col0.getZ()),Vector3(col1.getX(),col1.getY(),col1.getZ()),Vector3(col2.getX(),col2.getY(),col2.getZ()));
	}
};

#endif //__BULLET_RIGIDBODY_H__
