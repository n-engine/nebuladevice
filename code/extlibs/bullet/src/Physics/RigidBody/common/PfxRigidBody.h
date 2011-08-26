/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_RIGIDBODY_H__
#define __PFX_RIGIDBODY_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

struct PfxRigidBody {
	uint32_t uniqueId;
	float   restitution;
	float   friction;
	float   invMass;
	Matrix3 invInertia;
	Vector3 position;
	Quat    orientation;
	Vector3 linearVelocity;
	Vector3 angularVelocity;
} __attribute__ ((aligned(16)));

#endif /* __PFX_RIGIDBODY_H__ */
