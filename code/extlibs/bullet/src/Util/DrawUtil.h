/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __DRAWUTIL_H__
#define __DRAWUTIL_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

void drawStar(const Vector3 &p,float radius);
void drawLine(const Vector3 &p1,const Vector3 &p2);
void drawBox(const Vector3 &pos,const Vector3 &w);
void drawArrow(const Vector3 &pos,const Vector3 &dir,const Vector3 &upVec,float scale=1.0f);
void drawJointFrame(const Vector3 &pos,const Matrix3 &frame,float scale=1.0f);
void drawCircle(const Vector3 &p,const Vector3 &n,float radius);

#endif
