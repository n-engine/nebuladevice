/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICS_RIGIDBODY_H__
#define __PHYSICS_RIGIDBODY_H__

///////////////////////////////////////////////////////////////////////////////
// PhysicsRigidBody

#define Instance(rb) ((int)(rb->getRigidBody()))

class PhysicsRigidBody : public CommonRigidBody
{
private:
	RigidBodies *mRigidBodies;
	int mBodyIndex;
	
public:
	PhysicsRigidBody(RigidBodies *rb,int bodyIndex) : CommonRigidBody((void*)bodyIndex)
	{
		mRigidBodies = rb;
		mBodyIndex = bodyIndex;
	}
	
	Vector3 getPosition() {return mRigidBodies->getPosition(mBodyIndex);}
	Matrix3	getRotation() {return Matrix3(mRigidBodies->getOrientation(mBodyIndex));}
};

#endif
