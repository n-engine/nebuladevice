/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __BOXCAPSULEDISTANCE_H__
#define __BOXCAPSULEDISTANCE_H__

#include "Box.h"
#include "Capsule.h"

//---------------------------------------------------------------------------
// boxCapsuleDistance:
//
// returns:
//    positive or negative distance between a box and capsule.
//
// args:
//    Vector3& normal: set to a unit contact normal pointing from box (A) to capsule (B).
//
//    BoxPoint& boxPointA, CapsulePoint& capsulePointB:
//       set to a closest point or point of penetration on each object.
//
//    Box boxA, const Capsule& capsuleB: object sizes
//
//    const Transform3 & transformA: box transformation
//
//    const Transform3 & transformB: column 0 gives the direction of the capsule;
//                                    the translation gives the center position
//
//    float distanceThreshold:
//       the algorithm will exit early if it finds that the objects are more distant than this
//       threshold, and not compute a contact normal or points.  if this distance returned
//       exceeds the threshold, all the other output data may not have been computed.  by
//       default, this is set to MAX_FLOAT so it will have no effect.
//
//---------------------------------------------------------------------------

float
boxCapsuleDistance(Vector3& normal,	BoxPoint& boxPointA,
				   CapsulePoint& capsulePointB,	Box boxA,
				   const Transform3& transformA, const Capsule& capsuleB,
				   const Transform3& transformB,
				   float distanceThreshold = FLT_MAX );

#endif /*  __BOXCAPSULEDISTANCE_H__ */
