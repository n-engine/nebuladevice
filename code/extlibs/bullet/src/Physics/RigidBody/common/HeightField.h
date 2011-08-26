/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __HEIGHTFIELD_H__
#define __HEIGHTFIELD_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/RigidBody/common/RigidBodyConfig.h"

///////////////////////////////////////////////////////////////////////////////
// Height Field Data

// ハイトフィールドの１ブロック
struct HeightFieldBlock
{
	float heightBuf[PFX_ALIGN16(BLOCK_SIZE_B*BLOCK_SIZE_B,sizeof(float))] __attribute__ ((aligned(128)));
};

// ハイトフィールド全体
struct HeightFieldData
{
	uint16_t numBlockX,numBlockZ;	// ブロック数
	uint16_t numFieldX,numFieldZ;	// フィールド数
	float maxHeight,minHeight;		// 高さの最大最小値
	float fieldWidth,fieldDepth;	// フィールドの大きさ

	HeightFieldBlock *blocks __attribute__ ((aligned(16)));
	
	HeightFieldData()
	{
		blocks = NULL;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Height Field Class

class HeightField
{
private:
	Vector3 fieldScale;		// フィールドのスケール

public:
	HeightField();
	
	// フィールドの更新
#ifndef __SPU__
	void setHeightFieldData(const HeightFieldData &field);
#endif

	// フィールドデータ
	HeightFieldData fieldData;

	// フィールドのサイズ
	float		getMaxHeight() const {return fieldData.maxHeight;}
	float		getMinHeight() const {return fieldData.minHeight;}
	float		getFieldWidth() const {return fieldData.fieldWidth;}
	float		getFieldDepth() const {return fieldData.fieldDepth;}
	
	// スケール
	const Vector3&	getScale() const {return fieldScale;}
	void			setScale(const Vector3 &scale) {fieldScale = scale;}
	
	// 座標変換
	inline Vector3 localToWorldPosition(const Vector3 &localPosition) const;
	inline Vector3 worldToLocalPosition(const Vector3 &worldPosition) const;
} __attribute__ ((aligned(16)));

inline
Vector3 HeightField::localToWorldPosition(const Vector3 &localPosition) const
{
	return mulPerElem(fieldScale,(localPosition - 0.5f*Vector3(fieldData.fieldWidth,0.0f,fieldData.fieldDepth)));
}

inline
Vector3 HeightField::worldToLocalPosition(const Vector3 &worldPosition) const
{
	return divPerElem(worldPosition,fieldScale) + 0.5f*Vector3(fieldData.fieldWidth,0.0f,fieldData.fieldDepth);
}

///////////////////////////////////////////////////////////////////////////////
//  Inline Function

#ifndef __SPU__
inline
float getFieldData(const HeightFieldData &fieldData,int i,int j)
{
	i = PFX_MIN(fieldData.numFieldX-1,i);
	j = PFX_MIN(fieldData.numFieldZ-1,j);
	int bi = i/BLOCK_SIZE;
	int bj = j/BLOCK_SIZE;
	int ci = i-bi*BLOCK_SIZE;
	int cj = j-bj*BLOCK_SIZE;

	return fieldData.blocks[bj*fieldData.numBlockX+bi].heightBuf[cj*BLOCK_SIZE_B+ci];
}

inline
void setFieldData(HeightFieldData &fieldData,int i,int j,float v)
{
	i = PFX_MIN(fieldData.numFieldX-1,i);
	j = PFX_MIN(fieldData.numFieldZ-1,j);
	int bi = i/BLOCK_SIZE;
	int bj = j/BLOCK_SIZE;
	int ci = i-bi*BLOCK_SIZE;
	int cj = j-bj*BLOCK_SIZE;
	
	fieldData.blocks[bj*fieldData.numBlockX+bi].heightBuf[cj*BLOCK_SIZE_B+ci] = v;

	// エッジに重複データを持たせる
	if(ci == 0 && cj == 0) {
		if(bi > 0) {
			fieldData.blocks[bj*fieldData.numBlockX+(bi-1)].heightBuf[cj*BLOCK_SIZE_B+BLOCK_SIZE] = v;
		}

		if(bj > 0) {
			fieldData.blocks[(bj-1)*fieldData.numBlockX+bi].heightBuf[BLOCK_SIZE*BLOCK_SIZE_B+ci] = v;
		}

		if(bi > 0 && bj > 0) {
			fieldData.blocks[(bj-1)*fieldData.numBlockX+(bi-1)].heightBuf[BLOCK_SIZE*BLOCK_SIZE_B+BLOCK_SIZE] = v;
		}
	}
	else if(ci == 0) {
		if(bi > 0) {
			fieldData.blocks[bj*fieldData.numBlockX+(bi-1)].heightBuf[cj*BLOCK_SIZE_B+BLOCK_SIZE] = v;
		}
	}
	else if(cj == 0) {
		if(bj > 0) {
			fieldData.blocks[(bj-1)*fieldData.numBlockX+bi].heightBuf[BLOCK_SIZE*BLOCK_SIZE_B+ci] = v;
		}
	}
}
#endif

#endif // __HEIGHTFIELD_H__
