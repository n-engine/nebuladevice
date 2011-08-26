/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CAPSULESPHEREDISTANCE_H__
#define __CAPSULESPHEREDISTANCE_H__

#include "Capsule.h"
#include "Sphere.h"

//---------------------------------------------------------------------------
// capsuleSphereDistance:
//
// returns:
//    positive or negative distance between capsule and sphere.
//
// args:
//    Vector3& normal: set to a unit contact normal pointing from capsule (A) to sphere (B).
//
//    CapsulePoint& capsulePointA, SpherePoint& spherePointB:
//       set to a closest point or point of penetration on each object
//
//    const Capsule& capsuleA, const Sphere& sphereB: object sizes.
//
//    const Transform3 & transformA: column 0 gives the direction of the capsule;
//                                    the translation gives the center position
//    const Transform3 & transformB: the translation gives the center position
//
//    float distanceThreshold:
//       the algorithm will exit early if it finds that the objects are more distant than this
//       threshold, and not compute a contact normal or points.  if this distance returned
//       exceeds the threshold, all the other output data may not have been computed.  by
//       default, this is set to MAX_FLOAT so it will have no effect.
//
//---------------------------------------------------------------------------

float
capsuleSphereDistance(
	Vector3 & normal,
	CapsulePoint & capsulePointA,
	SpherePoint & spherePointB,
	const Capsule & capsuleA, const Transform3 & transformA,
	Sphere sphereB, const Transform3 & transformB,
	float distanceThreshold = FLT_MAX );

#endif /* __CAPSULESPHEREDISTANCE_H__ */
