/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __RENDERSHAPE_H__
#define __RENDERSHAPE_H__

#include "GLInclude.h"

#define FMT_VERTEX			0x01
#define FMT_NORMAL			0x02
#define FMT_TEXCOORD		0x04
#define FMT_TANGENT			0x08
#define FMT_BONEINDEX		0x10
#define FMT_BONEWEIGHT		0x20

///////////////////////////////////////////////////////////////////////////////
// RenderShape class

class RenderShape
{
public:
	RenderShape(int _type);
	~RenderShape();

	enum {MESH,MESH_STATIC};			// 形状の種類
	enum {TRIANGLES,TRIANGLE_STRIP};	// インデックスの種類

	int mType;					// 形状の種類
	int mFormat;				// 頂点に含まれる属性値
	int mIdxType;				// インデックスの種類

	unsigned int mVtxcount;	// 頂点数

	const float  *mVtx;		// 頂点座標バッファ
	const float  *mNml;		// 法線ベクトルバッファ
	const float  *mTex;		// テクスチャ座標バッファ
	const float  *mBoneIndex;	// ボーンインデックス	x4
	const float  *mBoneWeight;	// ボーンウェイト		x4

	unsigned int mIdxcount;	// インデックス数
	const unsigned short *mIdx;		// 頂点へのインデックスバッファ

	void setMesh(
		unsigned int vtxcount,
		const float *vtx,
		const float *nml,
		const float *tex,
		const float *boneIndex,
		const float *boneWeight,
		unsigned int idxcount,
		const unsigned short *idx,
		int idxtype = TRIANGLES);

	void print();
	void printAll();
	
	bool checkFormat(int f) {return f&mFormat;}
	
	// 基本形状の作成
	static RenderShape* createBox();
	static RenderShape* createSphere(int div);
	static RenderShape* createCapsule(float hlen,float radius,int div,int dir);
	static RenderShape* createCylinder(float hlen,float radius,int div,int dir);
};

#endif
