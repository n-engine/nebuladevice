#ifndef __PFX_GJK_SUPPORT_FUNC_H__
#define __PFX_GJK_SUPPORT_FUNC_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

void getSupportVertexTriangle(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);
void getSupportVertexTriangleWithThickness(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);
void getSupportVertexConvex(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);
void getSupportVertexBox(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);
void getSupportVertexCapsule(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);
void getSupportVertexSphere(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);

// not supported yet
//void getSupportVertexCylinder(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);

#endif /* __PFX_GJK_SUPPORT_FUNC_H__ */
