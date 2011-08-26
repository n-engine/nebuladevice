/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_RBSTATE_H__
#define __PFX_RBSTATE_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"

// Move Type
enum {
	MoveTypeFixed    = 0,
	MoveTypeActive   = 1,
	MoveTypeKeyframe = 3,
	MoveTypeOneWay   = 5,
	MoveTypeTrigger  = 7,
	MoveTypeCount
};

struct PfxRbState
{
	PfxHandle	originalRigidbody;
	uint16_t	uniqueId;
	uint8_t		moveType;
	uint8_t		sleeping           : 1;
	uint16_t	contactFilterSelf;
	uint16_t	contactFilterTarget;
	Vector3		center;		// AABB center(World)
	Vector3		extent;		// AABB half(World)
} __attribute__ ((aligned(16)));

#endif /* __PFX_RBSTATE_H__ */

