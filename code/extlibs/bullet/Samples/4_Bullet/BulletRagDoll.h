/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef __BULLET_RAGDOLL_H
#define __BULLET_RAGDOLL_H

// Enrico: Shouldn't these three variables be real constants and not defines?

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

class BulletRagDoll
{
	enum
	{
		BODYPART_PELVIS = 0,
		BODYPART_SPINE,
		BODYPART_HEAD,

		BODYPART_LEFT_UPPER_LEG,
		BODYPART_LEFT_LOWER_LEG,

		BODYPART_RIGHT_UPPER_LEG,
		BODYPART_RIGHT_LOWER_LEG,

		BODYPART_LEFT_UPPER_ARM,
		BODYPART_LEFT_LOWER_ARM,

		BODYPART_RIGHT_UPPER_ARM,
		BODYPART_RIGHT_LOWER_ARM,

		BODYPART_COUNT
	};

	enum
	{
		JOINT_PELVIS_SPINE = 0,
		JOINT_SPINE_HEAD,

		JOINT_LEFT_HIP,
		JOINT_LEFT_KNEE,

		JOINT_RIGHT_HIP,
		JOINT_RIGHT_KNEE,

		JOINT_LEFT_SHOULDER,
		JOINT_LEFT_ELBOW,

		JOINT_RIGHT_SHOULDER,
		JOINT_RIGHT_ELBOW,

		JOINT_COUNT
	};

	class btDynamicsWorld* m_ownerWorld;
	class PhysicsSample*	m_sample;

	class btCollisionShape* m_shapes[BODYPART_COUNT];
	class btRigidBody* m_bodies[BODYPART_COUNT];
	class btTypedConstraint* m_joints[JOINT_COUNT];

	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);
	
public:
	BulletRagDoll (btDynamicsWorld* ownerWorld, PhysicsSample* sample, const btVector3& positionOffset, btScalar scale = btScalar(1.0f));
	virtual ~BulletRagDoll ();
};

#endif

