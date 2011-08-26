/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __BOXBOXDISTANCE_H__
#define __BOXBOXDISTANCE_H__

#include <vectormath_aos.h>

#include "Box.h"

using namespace Vectormath::Aos;

//---------------------------------------------------------------------------
// boxBoxDistance:
//
// description:
//    this computes info that can be used for the collision response of two boxes.  when the boxes
//    do not overlap, the points are set to the closest points of the boxes, and a positive
//    distance between them is returned.  if the boxes do overlap, a negative distance is returned
//    and the points are set to two points that would touch after the boxes are translated apart.
//    the contact normal gives the direction to repel or separate the boxes when they touch or
//    overlap (it's being approximated here as one of the 15 "separating axis" directions).
//
// returns:
//    positive or negative distance between two boxes.
//
// args:
//    Vector3& normal: set to a unit contact normal pointing from box A to box B.
//
//    BoxPoint& boxPointA, BoxPoint& boxPointB:
//       set to a closest point or point of penetration on each box.
//
//    Box boxA, Box boxB:
//       boxes, represented as 3 half-widths
//
//    const Transform3& transformA, const Transform3& transformB:
//       box transformations, in world coordinates
//
//    float distanceThreshold:
//       the algorithm will exit early if it finds that the boxes are more distant than this
//       threshold, and not compute a contact normal or points.  if this distance returned
//       exceeds the threshold, all the other output data may not have been computed.  by
//       default, this is set to MAX_FLOAT so it will have no effect.
//
//---------------------------------------------------------------------------

float
boxBoxDistance(Vector3& normal, BoxPoint& boxPointA, BoxPoint& boxPointB,
			   Box boxA, const Transform3 & transformA, Box boxB,
			   const Transform3 & transformB,
			   float distanceThreshold = FLT_MAX );

#endif /* __BOXBOXDISTANCE_H__ */
