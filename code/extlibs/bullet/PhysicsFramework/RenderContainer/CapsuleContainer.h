/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CAPSULE_CONTAINER_H__
#define __CAPSULE_CONTAINER_H__

#include "PhysicsFramework/RenderShape.h"
#include "PhysicsFramework/RenderContainer/RenderContainer.h"

///////////////////////////////////////////////////////////////////////////////
// CapsuleContainer class

class CapsuleContainer : public RenderContainer
{
private:
	ShaderProgramMesh *mShader;

	enum {
		VBO_VERTEX=0,
		VBO_NORMAL,
		VBO_TEXCOORD,
		VBO_ELEMENT,
		VBO_COUNT
	};

	RenderShape *mSphereShape;		// 球形状
	RenderShape *mCylinderShape;	// シリンダ形状
	
	// 頂点バッファオブジェクト
	GLuint mVbo[2][VBO_COUNT];// 頂点属性
	
	void drawSphere();
	void drawCylinder();
	
public:
	// ※ mScale = { halfLength, radius, None, None }
	
	CapsuleContainer(int div);
	virtual ~CapsuleContainer();
	
	ContainerType getContainerType() {return ContainerTypeCapsule;}
	
	void setShader(const ShaderProgramBase *shader);
	ShaderProgramBase *getShader() {return mShader;}

	void printShape()
	{
		if(mSphereShape) mSphereShape->printAll();
		if(mCylinderShape) mCylinderShape->printAll();
	}

	// ※ 以下のメソッドはすべてmObjListを設定してから呼ぶこと
	
	void init();	// 初期化
	void release();	// 開放
	void reset();	// パラメータをセット

	// 描画
	void drawContainer(const Matrix4 &wvpMatrix,const Vector3 &lightPos,const Vector3 &eyePos);
};

#endif
