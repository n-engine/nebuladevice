/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CLOSESTCONTACT_H__
#define __CLOSESTCONTACT_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Contact.h"
#include "CollObject.h"

struct CCDDebugSphere {
	float r;
	bool collide;
	Vector3 pos;
};

inline Transform3 interpTransform(float t,const Transform3 &tr0,const Transform3 &tr1)
{
	return Transform3(
		slerp(t,Quat(tr0.getUpper3x3()),Quat(tr1.getUpper3x3())),
		lerp(t,tr0.getTranslation(),tr1.getTranslation()));
}

inline Transform3 integrateTransform(float timeStep,const Transform3 &tr,const Vector3 &linVel,const Vector3 &angVel)
{
	Quat orientation(tr.getUpper3x3());
	Quat dq =  Quat(angVel,0) * orientation * 0.5f;
	return Transform3(
		normalize(orientation + dq * timeStep),
		tr.getTranslation() + linVel * timeStep);
}

bool
closestContact(ContactPair &contactPair,
				const CollObject & objA, const Transform3 & transformA,
				const CollObject & objB, const Transform3 & transformB,
				float objsInContactDist = FLT_MAX);

uint32_t findContactCCD(ContactPair &contactPair,
				const CollObject &objA,const Transform3 &tA0,const Transform3 &tA1,bool useCcdA,
				const CollObject &objB,const Transform3 &tB0,const Transform3 &tB1,bool useCcdB,
				float objsInContactDist = FLT_MAX);

#endif /* __CLOSESTCONTACT_H__ */

