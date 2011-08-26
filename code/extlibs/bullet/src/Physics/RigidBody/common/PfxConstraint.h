/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_CONSTRAINT_H__
#define __PFX_CONSTRAINT_H__

#include "PfxRigidBody.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

enum PfxConstraintType {
	ConstraintTypeLinear,
	ConstraintTypeAngular,
};

struct PfxSolverBody {
	Vector3 deltaLinearVelocity;
	Vector3 deltaAngularVelocity;
	float   massInv;
//	float   friction;
	void    *userObject;
} __attribute__ ((aligned(16)));

struct PfxGenericConstraintRow {
	int   type;
	float jacDiagInv;
	float rhs;
	float cfm;
	float lowerLimit;
	float upperLimit;
	float accumImpulse;
	Vector3 normal;
	Vector3 angularComponentA;
	Vector3 angularComponentB;
	Vector3 relposCrossNormalA;
	Vector3 relposCrossNormalB;
} __attribute__ ((aligned(128)));

#endif /* __PFX_CONSTRAINT_H__ */
