/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PARTICLE_UTILITY_H__
#define __PARTICLE_UTILITY_H__

#include "Physics/Particle/Particles.h"

namespace ParticleUtil {

///////////////////////////////////////////////////////////////////////////////
// パーティクルユーティリティ関数

///////////////////////////////////////////////////////////////////////////////
// パーティクルグループの作成・破棄

void createParticleGroup(ParticleGroup &particleGroup,ParticleGroupProperty &property);
void releaseParticleGroup(ParticleGroup &particleGroup);

///////////////////////////////////////////////////////////////////////////////
// クロスの作成・破棄
// 必要なバッファは自動的に確保されます。

struct ClothProperty {
	// Mesh Property
	uint32_t	numVertices;			// 頂点数
	uint32_t	numIndices;				// 面インデックス
	uint32_t	vertexStrideBytes;		// 頂点ストライド
	float		*verts;					// 頂点バッファ
	float		*texCoords;				// テクスチャバッファ
	uint16_t	*indices;				// インデックスバッファ
	uint32_t	numReserveJoints;		// 予備用の追加ジョイント数

	// Particle Property
	float		mass;					// パーティクルの質量
	float		radius;					// パーティクルの半径
	
	// Simulation Property
	uint8_t		contactIteration;		// コンタクト演算の反復回数
	uint8_t		jointIteration;			// ジョイント演算の反復回数
	uint16_t	contactFilterSelf;		// コンタクトフィルター
	uint16_t	contactFilterTarget;	// コンタクトフィルター
	float		maxLinearVelocity;		// 速度の最大値
	float		linearDamping;			// 並進速度のダンピング
	float		separateBias;			// 接触しているパーティクルを引き離すためのバイアス値
	float		jointDamping;			// ジョイントダンピング
	float		jointBias;				// ジョイントバイアス
	Vector3		extraForce;				// 外力
	Vector3		gravity;				// 重力
	bool		particleCollisionEnable;// パーティクル間衝突

	ClothProperty()
	{
		contactIteration = 1;
		jointIteration = 3;
		contactFilterSelf = 0xffff;
		contactFilterTarget = 0xffff;
		maxLinearVelocity = 500.0f;
		linearDamping = 1.0f;
		separateBias = 0.2f;
		jointDamping = 0.2f;
		jointBias = 0.2f;
		extraForce = Vector3(0.0f);
		gravity = Vector3(0.0f,-9.8f,0.0f);
		particleCollisionEnable = false;

		mass = 0.01f;
		radius = 0.2f;

		numVertices = 0;
		numIndices = 0;
		vertexStrideBytes = sizeof(float)*3;
		verts = NULL;
		texCoords = NULL;
		indices = NULL;
		numReserveJoints = 0;
	}
};

void createCloth(ParticleGroup &particleGroup,ClothProperty &property);

} // namespace ParticleUtil

#endif /* __PARTICLE_UTILITY_H__ */
