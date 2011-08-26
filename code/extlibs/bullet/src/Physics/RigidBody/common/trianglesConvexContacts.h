/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRIANGLESCONVEX_CONTACTS_H__
#define __TRIANGLESCONVEX_CONTACTS_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"
#include "Physics/RigidBody/common/SubData.h"

// sepAxisÇÕ-->triangleÇÃï˚å¸
// Convexç¿ïWån
bool triangleConvexContact(Vector3 &axis,Vector3 &pointsOnTriangle,Vector3 &pointsOnConvex,
							const Vector3 &normal,const Vector3 &p0,const Vector3 &p1,const Vector3 &p2,const float thickness,
							const ConvexMesh *meshB);

int trianglesConvexContacts(Vector3 *normal, SubData *subData, Point3 *pointA, Point3 *pointB, float *distance,
						const TriMesh *meshA, const Transform3 & transformA,
						const ConvexMesh *meshB, const Transform3 & transformB,float distanceThreshold = FLT_MAX );

#endif
