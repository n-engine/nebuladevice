/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_COMMON_FORMAT_H__
#define __PFX_COMMON_FORMAT_H__

#include "PfxCommonTypes.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// フォーマット情報

#define PFX_FORMAT_VENDER	"Sony Computer Entertainment"
#define PFX_FORMAT_VERSION	"1.0.0"

///////////////////////////////////////////////////////////////////////////////
// 剛体で使われる要素の種類

// 形状の種類
enum PfxRigShapeType {
	RigShapeTypeSphere = 0,	// 球
	RigShapeTypeBox,		// ボックス
	RigShapeTypeCapsule,	// カプセル
	RigShapeTypeConvexMesh,	// 凸ポリゴン
	RigShapeTypeLargeMesh,	// 大規模メッシュ
};

// 剛体動作の種類
enum PfxRigMoveType {
	RigMoveTypeFixed = 0,	// 固定
	RigMoveTypeActive,		// アクティブ
	RigMoveTypeKeyframe,	// キーフレーム
	RigMoveTypeOneWay,		// 一方向
	RigMoveTypeTrigger,		// トリガ
};

// ジョイントの種類
enum PfxRigJointType {
	RigJointTypeBall = 0,	// ボールジョイント
	RigJointTypeChain,		// チェインジョイント
	RigJointTypeSlider,		// スライダージョイント
	RigJointTypeHinge,		// ヒンジジョイント
	RigJointTypeFix,		// 固定ジョイント
	RigJointTypeUniversal,	// ユニバーサルジョイント
	RigJointTypeAnimation,	// アニメーションジョイント
	RigJointTypeDistance,	// 一定距離に保つジョイント
	RigJointType6DOF,		// 6自由度ジョイント
	RigJointTypeConeTwist,  // コーンツイストジョイント
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigWorldInfo

struct PfxRigWorldInfo {
	// オブジェクトの最大数
	PfxUInt32 maxInstances;			// 剛体インスタンスの最大数
	PfxUInt32 maxDynBodies;			// 剛体の最大数
	PfxUInt32 maxJoints;				// ジョイントの最大数
	PfxUInt32 maxSprings;			// スプリングの最大数
	PfxUInt32 maxContactPairs;		// コンタクトペアの最大数

	// ワールド
	PfxFloat3  worldCenter;			// ワールドの中心
	PfxFloat3  worldExtent;			// ワールドの広さ
	PfxFloat3  gravity;				// 重力

	// シミュレーション
	PfxUInt8 subStepCount;			// サブステップ数
	PfxUInt8 contactIteration;		// コンタクト演算の反復回数
	PfxUInt8 jointIteration;		// ジョイント演算の反復回数
	PfxFloat maxLinearVelocity;		// 速度の最大値
	PfxFloat maxAngularVelocity;	// 角速度の最大値
	PfxFloat separateBias;			// 接触している剛体を引き離すためのバイアス値

	// スリープ
	PfxBool  sleepEnable;			// スリープ機能のON/OFF
	PfxUInt16 sleepCount;			// スリープに入るカウント
	PfxUInt16 sleepInterval;		// スリープチェックインターバル
	PfxFloat sleepLinearVelocity;	// スリープに入るための並進速度
	PfxFloat sleepAngularVelocity;	// スリープに入るための角速度
	PfxFloat wakeLinearVelocity;	// 起きるための並進速度
	PfxFloat wakeAngularVelocity;	// 起きるための角速度
	
	
	PfxBool ccdEnable;				// 連続的衝突判定のON/OFF
	PfxBool deformMeshEnable;		// 変形メッシュのON/OFF
	
	PfxRigWorldInfo()
	{
		maxInstances = 550;
		maxDynBodies = 40;
		maxJoints = 600;
		maxSprings = 0;
		maxContactPairs = 5000;
		worldExtent = PfxFloat3(200.0f);
		worldCenter = PfxFloat3(0.0f,90.0f,0.0f);
		gravity = PfxFloat3(0.0f,-9.8f,0.0f);
		subStepCount = 1;
		contactIteration = 5;
		jointIteration = 8;
		maxLinearVelocity = 500.0f;
		maxAngularVelocity = 100.0f;
		separateBias = 0.2f;
		sleepEnable = true;
		sleepLinearVelocity = 0.1f;
		sleepAngularVelocity = 0.1f;
		sleepCount = 100;
		sleepInterval = 300;
		wakeLinearVelocity = 0.2f;
		wakeAngularVelocity = 0.2f;
		ccdEnable = false;
		deformMeshEnable = false;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigShapeInfo

struct PfxRigShapeInfo {
	PfxRigShapeType shapeType : 8;
	PfxUInt32 contactFilterSelf;
	PfxUInt32 contactFilterTarget;
	PfxFloat4 relativeOrientation;
	PfxFloat3 relativePosition;
	union {
		PfxFloat    vfData[3];
		PfxUInt32   viData[3];
	};
	
	PfxRigShapeInfo()
	{
		shapeType = RigShapeTypeSphere;
		contactFilterSelf = 0xffffffff;
		contactFilterTarget = 0xffffffff;
		relativeOrientation = PfxFloat4(0.0f,0.0f,0.0f,1.0f);
		relativePosition = PfxFloat3(0.0f);
		viData[0] = viData[1] = viData[2] = 0;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigBodyInfo

struct PfxRigBodyInfo {
	string		name;					// 名称
	PfxFloat	mass;					// 質量
	PfxMatrix3	inertia;				// 慣性テンソル
	PfxFloat	friction;				// 摩擦係数
	PfxFloat	restitution;			// 反発係数
	vector<PfxRigShapeInfo> shapes;		// 形状配列
	
	PfxRigBodyInfo()
	{
		name = "";
		mass = 0.0f;
		inertia.identity();
		friction = 0.6f;
		restitution = 0.2f;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigStateInfo

struct PfxRigStateInfo {
	string		name;					// 名称
	PfxRigMoveType	moveType;			// 動作の種類
	PfxUInt32	contactFilterSelf;		// 自分のコンタクトフィルター
	PfxUInt32	contactFilterTarget;	// 衝突先コンタクトフィルター
	PfxFloat3	position;				// 位置
	PfxFloat4	orientation;			// 回転
	PfxFloat3 	linearVelocity;			// 並進速度
	PfxFloat3 	angularVelocity;		// 回転速度
	PfxFloat	linearDamping;			// 並進ダンピング
	PfxFloat	angularDamping;			// 回転ダンピング
	string		bodyName;				// 剛体とのリンク
	PfxBool		sleeping;				// スリープ中かどうか
	PfxBool		useSleep;				// スリープ可否属性
	PfxBool		useCcd;					// CCD属性
	PfxBool		useContactCallback;		// コンタクトコールバック属性
	PfxBool		useSleepCallback;		// スリープコールバック属性
	
	PfxRigStateInfo()
	{
		name = "";
		moveType = RigMoveTypeFixed;
		contactFilterSelf = 0xffffffff;
		contactFilterTarget = 0xffffffff;
		position = PfxFloat3(0.0f);
		orientation = PfxFloat4(0.0f,0.0f,0.0f,1.0f);
		linearVelocity = PfxFloat3(0.0f);
		angularVelocity = PfxFloat3(0.0f);
		linearDamping = 1.0f;
		angularDamping = 0.99f;
		bodyName = "";
		sleeping = false;
		useCcd = false;
		useSleep = true;
		useContactCallback = false;
		useSleepCallback = false;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigJointInfo

struct PfxRigJointInfo {
	string		name;					// 名称
	PfxRigJointType	jointType;			// ジョイントの種類
	string		parentName;				// 親-剛体インスタンス
	string		childName;		 		// 子-剛体インスタンス
	PfxFloat3	anchor;					// 基点
	PfxFloat3	axis;					// 軸

	PfxFloat	lowerLimit1;			// 可動範囲の下限
	PfxFloat	upperLimit1;			// 可動範囲の上限
	PfxFloat	lowerLimit2;			// 可動範囲の下限
	PfxFloat	upperLimit2;			// 可動範囲の上限
	PfxFloat	distance;				// Distanceジョイントの距離
	
	PfxFloat	linearDamping;			// 並進ダンピング
	PfxFloat	angularDamping;			// 回転ダンピング
	PfxFloat	linearImpulseWeight;	// 並進インパルスウェイト
	PfxFloat	angularImpulseWeight;	// 回転インパルスウェイト
	PfxFloat	linearBias;				// 並進バイアス値
	PfxFloat	angularBias;			// 回転バイアス値
	PfxFloat	maxLinearImpulse;		// 最大並進インパルス
	PfxFloat	maxAngularImpulse;		// 最大回転インパルス
	PfxFloat	breakableLimit;			// ジョイントを破壊 0.0f=無効
	
	PfxRigJointInfo()
	{
		name = "";
		jointType = RigJointTypeBall;
		parentName = childName = "";
		anchor = PfxFloat3(0.0f);
		axis = PfxFloat3(1.0f,0.0f,0.0f);
		lowerLimit1 = upperLimit1 = 0.0f;
		lowerLimit2 = upperLimit2 = 0.0f;
		linearDamping = angularDamping = 0.0f;
		linearImpulseWeight = angularImpulseWeight = 1.0f;
		linearBias = angularBias = 0.1f;
		maxLinearImpulse = 100.0f;
		maxAngularImpulse = 100.0f;
		breakableLimit = 0.0f;
		distance = 0.0f;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigConvexMeshInfo

struct PfxRigConvexMeshInfo {
	PfxUInt32 id;
	vector<PfxFloat> verts;		// 頂点配列
	vector<PfxUInt16> indices;	// 面インデックス配列
	
	PfxRigConvexMeshInfo()
	{
		id = 0;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigLargeTriMeshInfo

struct PfxRigLargeMeshInfo {
	PfxUInt32 id;
	vector<PfxFloat> verts;		// 頂点配列
	vector<PfxUInt16> indices;	// 面インデックス配列

	PfxUInt32 numFacetsLimit;	// アイランド面数閾値
	PfxFloat islandsRatio; 		// シーン全体に対するアイランドAABBサイズ比率
	
	PfxRigLargeMeshInfo()
	{
		id = 0;
		numFacetsLimit = 15;
		islandsRatio = 0.2f;
	}
};

///////////////////////////////////////////////////////////////////////////////
// PfxRigNonContactPairInfo

struct PfxRigNonContactPairInfo {
	string rigA,rigB;
};

///////////////////////////////////////////////////////////////////////////////
// PfxCommonFormat

class PfxCommonFormat
{
private:
	map<string,PfxUInt32>				mRigBodyMap;
	map<string,PfxUInt32>				mRigStateMap;
	map<string,PfxUInt32>				mRigJointMap;
	map<PfxUInt32,PfxUInt32>			mRigConvexMeshMap;
	map<PfxUInt32,PfxUInt32>			mRigLargeMeshMap;

protected:
	PfxRigWorldInfo						mRigWorldInfo;

	vector<PfxRigBodyInfo>				mRigBodies;
	vector<PfxRigStateInfo>				mRigStates;
	vector<PfxRigJointInfo>				mRigJoints;
	vector<PfxRigConvexMeshInfo>		mRigConvexMeshes;
	vector<PfxRigLargeMeshInfo>			mRigLargeMeshes;
	vector<PfxRigNonContactPairInfo>	mRigNonContactPairs;

public:
	void clear();
	
	void setRigWorldInfo(PfxRigWorldInfo &info);
	PfxRigWorldInfo getRigWorldInfo();

	void addRigBody(PfxRigBodyInfo &body);
	void addRigState(PfxRigStateInfo &state);
	void addRigJoint(PfxRigJointInfo &joint);
	void addRigConvexMesh(PfxRigConvexMeshInfo &convex);
	void addRigLargeMesh(PfxRigLargeMeshInfo &largemesh);
	void addRigNonContactPair(PfxRigNonContactPairInfo &info);

	int getRigBodyCount();
	int getRigStateCount();
	int getRigJointCount();
	int getConvexMeshCount();
	int getLargeMeshCount();
	int getRigNonContactPairCount();

	const PfxRigBodyInfo       &getRigBodyById(int i);
	const PfxRigStateInfo      &getRigStateById(int i);
	const PfxRigJointInfo      &getRigJointById(int i);
	const PfxRigConvexMeshInfo &getConvexMeshById(int i) const;
	const PfxRigLargeMeshInfo  &getLargeMeshById(int i) const;
	const PfxRigNonContactPairInfo  &getRigNonContactPairById(int i);

	PfxRigBodyInfo       *getRigBody(string name);
	PfxRigStateInfo      *getRigState(string name);
	PfxRigJointInfo      *getRigJoint(string name);
	PfxRigConvexMeshInfo *getConvexMesh(PfxUInt32 id);
	PfxRigLargeMeshInfo  *getLargeMesh(PfxUInt32 id);

	PfxMatrix3 calcTotalInertia(PfxRigBodyInfo &body);
};

#endif /* __PFX_COMMON_FORMAT_H__ */
