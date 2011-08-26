/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CONVEXCONVEX_DISTANCE_H___
#define __CONVEXCONVEX_DISTANCE_H___

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"

float closestConvexConvex( Vector3& normal, Point3 &pointA, Point3 &pointB,
						const ConvexMesh *meshA, const Transform3 & transformA,
						const ConvexMesh *meshB, const Transform3 & transformB,
						float distanceThreshold = FLT_MAX );

#endif // __CONVEXCONVEX_DISTANCE_H___

