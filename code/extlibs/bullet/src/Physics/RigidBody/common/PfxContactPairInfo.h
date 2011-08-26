/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_CONTACT_H__
#define __PFX_CONTACT_H__

#include "Physics/LowLevelPhysics.h"

struct PfxContactPairInfo {
	CollObject *shapeA;
	CollObject *shapeB;

	Vector3 positionA;
	Vector3 positionB;
	Quat orientationA;
	Quat orientationB;

	void *userContact;
	void *userObjectA;
	void *userObjectB;
} __attribute__ ((aligned(128)));

static inline
void internalCollideCallback(
	void* userObjectA,
	void* userObjectB,
	void* userContact,
	ContactPoint *cp,
	int numContacts)
{
	plContactInfo info;
	
	info.m_strideInBytes = sizeof(ContactPoint);
	info.m_numContacts = numContacts;
	info.m_localPointA = (plReal*)cp[0].localPointA;
	info.m_localPointB = (plReal*)cp[0].localPointB;
	info.m_normal = (plReal*)cp[0].normal;
	info.m_distance = (plReal*)&cp[0].distance;

	//PRINTF("internalCollideCallback in\n");
	//PRINTF("  userObjectA %x userObjectB %x userContact %x\n",userObjectA,userObjectB,userContact);
	//PRINTF("  strideInBytes %d\n",info.m_strideInBytes);
	//PRINTF("  numContacts %d\n",info.m_numContacts);
	//PRINTF("  localPointA %f %f %f\n",info.m_localPointA[0],info.m_localPointA[1],info.m_localPointA[2]);
	//PRINTF("  localPointB %f %f %f\n",info.m_localPointB[0],info.m_localPointB[1],info.m_localPointB[2]);
	//PRINTF("  normal %f %f %f\n",info.m_normal[0],info.m_normal[1],info.m_normal[2]);
	//PRINTF("  distance %f\n",*info.m_distance);
	//PRINTF("internalCollideCallback out\n");

	plCollide(userObjectA,userObjectB,userContact,&info);
}

#endif /* __PFX_CONTACT_H__ */
