/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __WORLD_VOLUME_H__
#define __WORLD_VOLUME_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/VecInt3.h"
//#include "Physics/RigidBody/common/RigidBodyConfig.h"

class WorldVolume {
public:
	Vector3 origin;
	Vector3 extent;
	
	inline void	setWorldSize(Vector3 origin_,Vector3 extent_);
	inline Vector3 localToWorldPosition(const VecInt3 &localPosition);
	inline VecInt3 worldToLocalPosition(const Vector3 &worldPosition);
} __attribute__ ((aligned(16)));

inline
void WorldVolume::setWorldSize(Vector3 origin_,Vector3 extent_)
{
	origin = origin_;
	extent = extent_;
}

inline
Vector3 WorldVolume::localToWorldPosition(const VecInt3 &localPosition)
{
	Vector3 sz(65535.0f);
	Vector3 q = divPerElem((Vector3)localPosition,sz);
	return mulPerElem(q,2.0f*extent) + origin - extent;
}

inline
VecInt3 WorldVolume::worldToLocalPosition(const Vector3 &worldPosition)
{
	Vector3 sz(65535.0f);
	Vector3 q = divPerElem(worldPosition - origin + extent,2.0f*extent);
	q = minPerElem(maxPerElem(q,Vector3(0.0f)),Vector3(1.0f)); // clamp 0.0 - 1.0
	q = mulPerElem(q,sz);
	return VecInt3(q);
}

#endif /* __WORLD_VOLUME_H__ */
