/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __COLLOBJECT_H__
#define __COLLOBJECT_H__

#include "CollPrim.h"
#include "Physics/RigidBody/common/RigidBodyConfig.h"

class CollObject
{
	CollPrim prims[NUMPRIMS];
	uint8_t numPrims;
	float ccdRadius;
	float center[3];	// AABB center (Local)
	float half[3];		// AABB half (Local)

public:

	CollObject();
	~CollObject();

	void addBox(Box box, const Transform3 & objectRelTransform);
	void addCapsule(Capsule capsule, const Transform3 & objectRelTransform);
	void addSphere(Sphere sphere, const Transform3 & objectRelTransform);
	void addConvex(const ConvexMesh *convexMesh, const Transform3 & objectRelTransform);
	void addTriangle(const TriMesh *triangleMesh, const Transform3 & objectRelTransform);

	void finish();
	void clear(); // clear all the prims

	// Height Field
	void setHeightField(const HeightField *heightfield);

	// LargeMesh
	void setLargeMesh(const LargeTriMesh *largeMesh);
	void setPreLargeMesh(const LargeTriMesh *largeMesh);

	inline uint8_t getNumPrims() const;

	inline const CollPrim &  getPrim(int i) const;
	inline CollPrim &  getPrim(int i) { return prims[i];}

	inline float getRadius() const;
	inline Vector3 getHalf() const;
	inline Vector3 getCenter() const;
	
	inline void setCcdRadius(float r) {ccdRadius=r;}
	inline float getCcdRadius() const {return ccdRadius;}
	
} __attribute__ ((aligned(16)));

inline
uint8_t
CollObject::getNumPrims() const
{
	return numPrims;
}

inline
const CollPrim &
CollObject::getPrim(int i) const
{
	return prims[i];
}

inline
float
CollObject::getRadius() const
{
	return length(getHalf());
}

inline
Vector3
CollObject::getHalf() const
{
	return read_Vector3(half);
}

inline
Vector3
CollObject::getCenter() const
{
	return read_Vector3(center);
}

inline
void CollObject::setPreLargeMesh(const LargeTriMesh *largeMesh)
{
	if(prims[0].getType() == LARGEMESH)
		prims[0].setPreLargeMesh(largeMesh);
}

#endif /* __COLLOBJECT_H__ */

