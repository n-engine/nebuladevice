/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CAPSULECAPSULEDISTANCE_H__
#define __CAPSULECAPSULEDISTANCE_H__

#include "Capsule.h"

//---------------------------------------------------------------------------
// capsuleCapsuleDistance:
//
// returns:
//    positive or negative distance between two capsules.
//
// args:
//    Vector3& normal: set to a unit contact normal pointing from capsule A to capsule B.
//
//    CapsulePoint& capsulePointA, CapsulePoint& capsulePointB:
//       set to a closest point or point of penetration on each object
//
//    const Capsule& capsuleA, const Capsule& capsuleB: capsule sizes.
//
//    const Transform3 & transformA,B: column 0 gives the direction of the capsule;
//                                      the translation gives the center position
//
//    float distanceThreshold:
//       the algorithm will exit early if it finds that the objects are more distant than this
//       threshold, and not compute a contact normal or points.  if this distance returned
//       exceeds the threshold, all the other output data may not have been computed.  by
//       default, this is set to MAX_FLOAT so it will have no effect.
//
//---------------------------------------------------------------------------

float
capsuleCapsuleDistance(
	Vector3 & normal,
	CapsulePoint & capsulePointA,
	CapsulePoint & capsulePointB,
	const Capsule & capsuleA, const Transform3 & transformA,
	const Capsule & capsuleB, const Transform3 & transformB,
	float distanceThreshold = FLT_MAX );

#endif /* __CAPSULECAPSULEDISTANCE_H__ */
