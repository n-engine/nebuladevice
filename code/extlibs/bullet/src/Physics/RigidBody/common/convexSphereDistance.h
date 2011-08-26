/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CONVEXSPHERE_DISTANCE_H__
#define __CONVEXSPHERE_DISTANCE_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"
#include "Sphere.h"

float closestConvexSphere( Vector3 &normal, Point3 &pointA, Point3 &pointB,
						  const ConvexMesh *meshA, const Transform3 & transformA,
						  Sphere sphereB, const Transform3 & transformB,
						  float distanceThreshold = FLT_MAX );

#endif
