/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRIANGLESBOX_CONTACTS_H__
#define __TRIANGLESBOX_CONTACTS_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"
#include "Box.h"
#include "Physics/RigidBody/common/SubData.h"

// sepAxisÇÕ-->triangleÇÃï˚å¸
// Boxç¿ïWån
bool triangleBoxContact(Vector3 &axis,Vector3 &pointsOnTriangle,Vector3 &pointsOnBox,
							const Vector3 &normal,const Vector3 &p0,const Vector3 &p1,const Vector3 &p2,const float thickness,
							const Vector3 &halfExtent);

int trianglesBoxContacts( Vector3 *normal, SubData *subData, Point3 *pointA, Point3 *pointB, float *distance,
								   const TriMesh *meshA, const Transform3 & transformA,
								   Box boxB, const Transform3 & transformB,float distanceThreshold = FLT_MAX );
#endif
