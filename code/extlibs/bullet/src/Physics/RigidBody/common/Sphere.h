/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Box.h"

//---------------------------------------------------------------------------
// Sphere
//---------------------------------------------------------------------------

class Sphere
{
public:
	float radius;

	Sphere()
	{}
	Sphere( float _radius );

	void  Set( float _radius );
	Vector3   GetAABB();
};

inline
Sphere::Sphere( float _radius )
{
	radius = _radius;
}

inline
void
Sphere::Set( float _radius )
{
	radius = _radius;
}

inline
Vector3
Sphere::GetAABB()
{
	return Vector3( radius );
}

//-------------------------------------------------------------------------------------------------
// SpherePoint
//-------------------------------------------------------------------------------------------------

class SpherePoint
{
public:
	SpherePoint() : localPoint(0.0f) {}

	Point3      localPoint;    // point in sphere's coordinate system
	FeatureType featureType;
	int         featureIdx;

	inline void setVertexFeature();
};

inline
void
SpherePoint::setVertexFeature()
{
	featureType = V;
	featureIdx = 0;
}

#endif /* __SPHERE_H__ */

