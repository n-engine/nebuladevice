/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SKINMESH_CONTAINER_H__
#define __SKINMESH_CONTAINER_H__

#include <vector>
using namespace std;

#include "PhysicsFramework/RenderShape.h"
#include "PhysicsFramework/RenderContainer/RenderContainer.h"

///////////////////////////////////////////////////////////////////////////////
// SkinMeshContainer class

class SkinMeshContainer : public RenderContainer
{
private:
	ShaderProgramSkinMesh *mShader;

	enum {
		VBO_VERTEX=0,
		VBO_NORMAL,
		VBO_TEXCOORD,
		VBO_BONEINDEX,
		VBO_BONEWEIGHT,
		VBO_ELEMENT,
		VBO_COUNT
	};

	RenderShape *mShape;	// 形状
	
	// 頂点バッファオブジェクト
	GLuint mVbo[VBO_COUNT];// 頂点属性
	
	int mNumBones;
	
public:
	vector< vector<Matrix4> > mBoneWorldInverseMatrices;

	SkinMeshContainer(RenderShape *shape,int numBones);
	virtual ~SkinMeshContainer();

	ContainerType getContainerType() {return ContainerTypeSkinMesh;}

	void setShader(const ShaderProgramBase *shader);
	ShaderProgramBase *getShader() {return mShader;}

	void printShape() {if(mShape) mShape->print();}

	void init();	// 初期化
	void release();	// 開放
	void reset();	// パラメータをセット

	int add(RenderObject *obj)
	{
		// オブジェクト追加と同時に空のボーンマトリクスを用意
		vector<Matrix4> tmpMatrix;
		tmpMatrix.resize(mNumBones,Matrix4::identity());
		mBoneWorldInverseMatrices.push_back(tmpMatrix);
		
		return RenderContainer::add(obj);
	}

	void setBoneWorldInverseMatrix(int renderObjIndex,int boneIndex,const Matrix4 &boneMatrix)
	{
		mBoneWorldInverseMatrices[renderObjIndex][boneIndex] = boneMatrix;
	}

	// 描画
	void drawContainer(const Matrix4 &wvpMatrix,const Vector3 &lightPos,const Vector3 &eyePos);
};

#endif
