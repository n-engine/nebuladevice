/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __RIGIDBODY_CONFIG_H__
#define __RIGIDBODY_CONFIG_H__

//---------------------------------------------------------------------------
// Rigid Body Dynamics
//---------------------------------------------------------------------------

// Rigid Body
#define NUMPRIMS					5		// １剛体に含まれる形状数

// Simulation Settings
#define JOINT_IMPULSE_EPSILON		0.0001f	// インパルス閾値
#define NUMCONTACTS_PER_BODIES		4		// 剛体ペアの最大衝突点数
#define CONTACT_THRESHOLD_NORMAL	0.01f	// 衝突点の閾値（法線方向）
#define CONTACT_THRESHOLD_TANGENT	0.002f	// 衝突点の閾値（平面上）
#define CONTACT_BATCH				64		// 衝突ペア処理数の最大値
#define CCD_THRESHOLD_MIN			0.01f	// CCD判定の範囲
#define CCD_THRESHOLD_MAX			0.25f	// CCD判定の範囲
#define CCD_ENABLE_DISTANCE			0.5f	// CCD判定に移行するための間隔

// 積分計算の切り替え（どちらかを選択）
//#define ODE_EULER
#define ODE_RUNGEKUTTA

// Height Field
#define BLOCK_SIZE				16
#define HEIGHTFIELD_CACHE_COUNT 4
#define BLOCK_SIZE_B (BLOCK_SIZE+1)	// 実際に確保されるサイズ（エッジを含む）

// SPU-SIMD最適化
#ifdef __SPU__
	//#define TRY_SIMD
#endif

// Split Impulse
//#define USE_SPLIT_IMPULSE

#endif /* __RIGIDBODY_CONFIG_H__ */
