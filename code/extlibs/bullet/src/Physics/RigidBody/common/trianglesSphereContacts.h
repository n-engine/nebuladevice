/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRIANGLESSPHERE_CONTACTS_H__
#define __TRIANGLESSPHERE_CONTACTS_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"
#include "Sphere.h"
#include "Physics/RigidBody/common/SubData.h"

// sepAxis‚Í-->triangle‚Ì•ûŒü
bool triangleSphereContact(
	Vector3 &axis,Vector3 &pointsOnTriangle,Vector3 &pointsOnSphere,
	const Vector3 &normal,const Vector3 &p0,const Vector3 &p1,const Vector3 &p2,const float thickness,
	float sphereRadius,const Vector3 &spherePos);

int trianglesSphereContacts( Vector3 *normal, SubData *subData, Point3 *pointA, Point3 *pointB, float *distance,
								   const TriMesh *meshA, const Transform3 & transformA,
								   Sphere sphereB, const Transform3 & transformB,float distanceThreshold = FLT_MAX );
#endif
