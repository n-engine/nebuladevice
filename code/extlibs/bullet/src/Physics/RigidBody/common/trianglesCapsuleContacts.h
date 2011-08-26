/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRIANGLESCAPSULE_CONTACTS_H__
#define __TRIANGLESCAPSULE_CONTACTS_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TriMesh.h"
#include "Capsule.h"
#include "Physics/RigidBody/common/SubData.h"

// sepAxis‚Í-->triangle‚Ì•ûŒü
bool triangleCapsuleContact(Vector3 &axis,Vector3 &pointsOnTriangle,Vector3 &pointsOnCapsule,
							const Vector3 &normal,const Vector3 &p0,const Vector3 &p1,const Vector3 &p2,const float thickness,
							float capsuleRadius,const Vector3 &capA,const Vector3 &capB);

int trianglesCapsuleContacts( Vector3 *normal, SubData *subData, Point3 *pointA, Point3 *pointB, float *distance,
							const TriMesh *meshA, const Transform3 & transformA,
							Capsule capB, const Transform3 & transformB,float distanceThreshold = FLT_MAX );

#endif /* __TRIANGLESCAPSULE_CONTACTS_H__ */
