/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CAPSULE_H__
#define __CAPSULE_H__

#include "Box.h"

//---------------------------------------------------------------------------
// Capsule
//---------------------------------------------------------------------------

class Capsule
{
public:
	float hLength;
	float radius;

	Capsule()
	{}
	Capsule(float hLength_, float radius_);

	void Set(float hLength_, float radius_);
	Vector3  GetAABB(Vector3 direction);
};

inline
Capsule::Capsule(float hLength_, float radius_)
{
	hLength = hLength_;
	radius = radius_;
}

inline
void
Capsule::Set(float hLength_, float radius_)
{
	hLength = hLength_;
	radius = radius_;
}

inline
Vector3
Capsule::GetAABB(Vector3 direction)
{
	return absPerElem(direction) * hLength + Vector3(radius);
}

//-------------------------------------------------------------------------------------------------
// CapsulePoint
//-------------------------------------------------------------------------------------------------

class CapsulePoint
{
public:
	CapsulePoint() : localPoint(0.0f) {}

	Point3      localPoint;    // point in capsule's coordinate system
	FeatureType featureType;
	int         featureIdx;
	float       lineParam;     // if line segment inside the capsule is parameterized as
	//    (center + direction * t), this is the t value for the
	//    nearest point on the line segment.

	inline void setVertexFeature(int plus);
	inline void setEdgeFeature();

	inline void getVertexFeature(int & plus) const;
};

inline
void
CapsulePoint::setVertexFeature(int plus)
{
	featureType = V;
	featureIdx = plus;
}

inline
void
CapsulePoint::setEdgeFeature()
{
	featureType = E;
	featureIdx = 0;
}

inline
void
CapsulePoint::getVertexFeature(int & plus) const
{
	plus = featureIdx;
}

#endif /* __CAPSULE_H__ */

