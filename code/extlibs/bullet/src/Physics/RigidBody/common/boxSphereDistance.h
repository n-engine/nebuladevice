/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __BOXSPHEREDISTANCE_H__
#define __BOXSPHEREDISTANCE_H__

#include "Box.h"
#include "Sphere.h"

//---------------------------------------------------------------------------
// boxSphereDistance:
//
// returns:
//    positive or negative distance between a box and sphere.
//
// args:
//    Vector3& normal: set to a unit contact normal pointing from box (A) to sphere (B).
//
//    BoxPoint& boxPointA, SpherePoint& spherePointB:
//       set to a closest point or point of penetration on each object
//
//    Box boxA, const Sphere& sphereB: object sizes.
//
//    const Transform3 & transformA: box transformation
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
boxSphereDistance(Vector3& normal, BoxPoint& boxPointA,
				  SpherePoint& spherePointB, Box boxA,
				  const Transform3 & transformA, const Sphere& sphereB,
				  const Transform3 & transformB,
				  float distanceThreshold = FLT_MAX );

#endif /* __BOXSPHEREDISTANCE_H__ */
