/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_CONTACT_CACHE_H__
#define __PFX_CONTACT_CACHE_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"
#include "SubData.h"

#define PFX_CONTACT_CACHE_SIZE 4
#define PFX_CONTACT_THRESHOLD  0.002f

class PfxContactCache {
private:
	uint32_t numContacts;
	uint32_t info[PFX_CONTACT_CACHE_SIZE];
	float   distance[PFX_CONTACT_CACHE_SIZE];
	Vector3 normal[PFX_CONTACT_CACHE_SIZE];
	Vector3 pointA[PFX_CONTACT_CACHE_SIZE];
	Vector3 pointB[PFX_CONTACT_CACHE_SIZE];
	
	int findNearestContactPoint(const Vector3 &newPoint);
	int sort4ContactPoints(const Vector3 &newPoint,float newDistance);

public:
	PfxContactCache() : numContacts(0)
	{
	}

	void add(float newDistance,Vector3 &newNormal,Vector3 &newPointA,Vector3 &newPointB,uint32_t newInfo)
	{
		int replaceId = findNearestContactPoint(newPointA);
		if(replaceId < 0) {
			if(numContacts < 4) {
				replaceId = numContacts++;
			}
			else {
				replaceId = sort4ContactPoints(newPointA,newDistance);
			}
		}
		distance[replaceId] = newDistance;
		normal[replaceId] = newNormal;
		pointA[replaceId] = newPointA;
		pointB[replaceId] = newPointB;
		info[replaceId] = newInfo;
	}
	
	uint32_t getNumContacts() {return numContacts;}

	uint32_t getInfo(int i) {return info[i];}
	float    getDistance(int i) const {return distance[i];}
	Vector3  getNormal(int i) const {return normal[i];}
	Vector3  getPointA(int i) const {return pointA[i];}
	Vector3  getPointB(int i) const {return pointB[i];}
};

#endif /* __PFX_CONTACT_CACHE_H__ */
