/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SNAPSHOT_UTILITY_H__
#define __SNAPSHOT_UTILITY_H__

#include "PhysicsCommon.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

bool isSame(char *s1,char *s2);
bool isToken(char c);
void readTag(char *line,char *tag);
void readString(const char *line,const char *str);
void readUint32(const char *line,uint32_t &value);
void readBool(const char *line,bool &value);
void readInt32(const char *line,int32_t &value);
void readFloat(const char *line,float &value);
void readVector3(const char *line,Vector3 &value);
void readMatrix3(const char *line,Matrix3 &value);
void readQuat(const char *line,Quat &value);
void readIndex3(const char *line,uint32_t &value0,uint32_t &value1,uint32_t &value2);
void readFloat3(const char *line,float &value0,float &value1,float &value2);

#endif /* __SNAPSHOT_UTILITY_H__ */
