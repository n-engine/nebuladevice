/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

#include "GLInclude.h"
#include "RenderShape.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

///////////////////////////////////////////////////////////////////////////////
// RenderObject class

class RenderObject
{
public:
	RenderObject();
	~RenderObject();

	// オブジェクトの属性
	Vector4     mColor;			// 色
	Vector3     mScale;			// スケール
	Transform3  mTransform;		// 位置
	Transform3  mRelTransform;	// 相対位置

	Matrix4    	mLocalToWorld;	// ワールド変換マトリクス
	GLuint      mTextureIndex;	// テクスチャインデックス
	
	bool		mDrawEnable;
	
	void init();
	void update();
};

//-----------------------------------------------------------------------------

#endif
