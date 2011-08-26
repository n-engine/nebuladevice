/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __INSTANCE_MESH_CONTAINER_H__
#define __INSTANCE_MESH_CONTAINER_H__

#include "PhysicsFramework/RenderShape.h"
#include "PhysicsFramework/RenderContainer/RenderContainer.h"

#define INSTANCE_BLOCK	500

///////////////////////////////////////////////////////////////////////////////
// InstanceMeshContainer class

class InstanceMeshContainer : public RenderContainer
{
private:
	ShaderProgramInstanceMesh *mShader;

	enum {
		VBO_VERTEX=0,
		VBO_NORMAL,
		VBO_TEXCOORD,
		VBO_COLOR,
		VBO_ELEMENT,
		VBO_TRANS,
		VBO_ITTRANS,
		VBO_PROPERTY,
		VBO_COUNT
	};

	RenderShape *mShape;	// 形状
	int mInstanceCount;		// インスタンス数
	int mInstanceBlockCount;// インスタンスブロック数
	
	// 頂点バッファオブジェクト
	GLuint mVbo[VBO_COUNT];
	
	void setupBuffer(int blockIdx,int blockSize);
	
public:
	InstanceMeshContainer(RenderShape *shape);
	virtual ~InstanceMeshContainer();
	
	ContainerType getContainerType() {return ContainerTypeInstanceMesh;}
	
	void setShader(const ShaderProgramBase *shader);
	ShaderProgramBase *getShader() {return mShader;}

	void printShape() {if(mShape) mShape->print();}

	// ※ 以下のメソッドはすべてmObjListを設定してから呼ぶこと
	
	void init();	// 初期化
	void release();	// 開放
	void reset();	// パラメータをセット

	// 描画
	void drawContainer(const Matrix4 &wvpMatrix,const Vector3 &lightPos,const Vector3 &eyePos);
};

#endif
