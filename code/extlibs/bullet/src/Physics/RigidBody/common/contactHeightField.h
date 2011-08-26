/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __HEIGHTFIELD_CONTACT_H__
#define __HEIGHTFIELD_CONTACT_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/RigidBody/common/HeightField.h"

bool contactHeightField(
					const HeightField *heightfield,
					const Point3 &checkPoint,
					Point3 &fieldPoint,
					Vector3 &fieldNormal,
					float &dist);

#endif
