/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __RENDER_CONTAINER_H__
#define __RENDER_CONTAINER_H__

#include "PhysicsFramework/GLInclude.h"
#include "PhysicsFramework/DebugPrint.h"
#include "PhysicsFramework/RenderObject.h"
#include "PhysicsFramework/ShaderProgram.h"

#include <vector>
using namespace std;

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#define PRIMITIVE_RESTART_INDEX 0xffff

class RenderObject;

///////////////////////////////////////////////////////////////////////////////
// RenderContainer class 描画用コンテナのベースクラス

class RenderContainer {
protected:
	bool mDrawEnable;
	
	vector<RenderObject*> mObjList;
public:
	enum ContainerType {
		ContainerTypeMesh,
		ContainerTypeDynMesh,
		ContainerTypeInstanceMesh,
		ContainerTypeSkinMesh,
		ContainerTypeCapsule,
		ContainerTypeWaterSurface,
	};
	
	RenderContainer() : mDrawEnable(true) {}
	virtual ~RenderContainer() {}
	
	virtual ContainerType getContainerType() = 0;
	
	virtual void setShader(const ShaderProgramBase *shader) = 0;
	virtual ShaderProgramBase *getShader() = 0;

	virtual int add(RenderObject *obj)
	{
		mObjList.push_back(obj);
		return mObjList.size()-1;
	}

	int getRenderObjectCount() {return mObjList.size();}

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void reset() = 0;
	virtual void drawContainer(const Matrix4 &wvpMatrix,const Vector3 &lightPos,const Vector3 &eyePos) = 0;
	
	void draw(const Matrix4 &wvpMatrix,const Vector3 &lightPos,const Vector3 &eyePos)
	{
		if(mDrawEnable) drawContainer(wvpMatrix,lightPos,eyePos);
	}
	
	void enableDraw(bool flg) {mDrawEnable = flg;}
	
	void toCgMatrix(const Matrix4& t, GLfloat *mtx)
	{
		for(int ii=0;ii<4;++ii)
			for(int jj=0;jj<3;++jj)
				mtx[ii+jj*4] = t[ii][jj];
	}
};

#endif
