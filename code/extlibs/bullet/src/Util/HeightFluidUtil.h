/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __HEIGHTFLUID_UTILITY_H__
#define __HEIGHTFLUID_UTILITY_H__

#include "Physics/HeightFluid/HeightFluidSurface.h"

namespace HeightFluidUtil {

///////////////////////////////////////////////////////////////////////////////
// 水面ユーティリティ関数

// 水面サーフェスの作成
void createHeightFluidSurface(HeightFluidSurface &surface,int numWidth,int numDepth);

// 水面サーフェスの破棄
void releaseHeightFluidSurface(HeightFluidSurface &surface);

} // namespace HeightFluidUtil

#endif /* __HEIGHTFLUID_UTILITY_H__ */
