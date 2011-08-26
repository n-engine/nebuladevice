/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __HEIGHTFIELD_FUNCTION_H__
#define __HEIGHTFIELD_FUNCTION_H__

#include "Physics/Base/PhysicsCommon.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/RigidBody/common/HeightField.h"
#include "Physics/RigidBody/common/RigidBodyConfig.h"

///////////////////////////////////////////////////////////////////////////////
// Height Field Function

#ifdef __SPU__

// ハイトフィールドのキャッシュを初期化
void  initializeHeightFieldCache();

// ハイトフィールドのキャッシュを開放
void  releaseHeightFieldCache();

#endif

// 指定したハイトフィールドの高さ（ローカル）を取得する
// ※ x,zはハイトフィールドのローカル座標で指定する
bool getHeight(const HeightField &heightfield,float x,float z,float &h);

// 指定したハイトフィールドの法線（ワールド）を取得する
// ※ x,zはハイトフィールドのローカル座標で指定する
bool getNormal(const HeightField &heightfield,float x,float z,Vector3 &nml);

#endif
