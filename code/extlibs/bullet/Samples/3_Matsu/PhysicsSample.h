/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICS_SAMPLE_H__
#define __PHYSICS_SAMPLE_H__

#include "Physics/RigidBody/RigidBodies.h"
#include "Physics/RayCast/raycast.h"
#include "Physics/RigidBody/Mass.h"

#include "PhysicsFramework.h"
#include "Util/PhysicsRigidBody.h"
#include "Util/PhysicsEffectsThreadUtil.h"

// タイムステップ
#define TIMESTEP	1.0f/60.0f

// 並列シミュレーション
//#define PARALLEL_SIMULATION_ENABLE

// 最大SPU、タスク数
#define NUM_MAX_SPU 5

// レイの最大数
#define NUMRAYS				200

///////////////////////////////////////////////////////////////////////////////
// スレッドパラメータ

struct PhysicsEffectsThreadParam {
	bool		isSpu;
	uint32_t	frame;
	float		timeStep;
	Ray			*rays;
	uint32_t	numRays;
	RigidBodies	*rigidbodies;
	RayCast		*raycast;
};

///////////////////////////////////////////////////////////////////////////////
// PhysicsSample class

class PhysicsSample : public PhysicsFramework , public MenuCtrlCallback
{
private:
	// --------------------------------------------------------
	// メニューコントロール

#ifdef WIN32
	MenuCtrlLabelBool *mCtrlSpuSimulationEnable;
#else
	MenuCtrlSpinBool *mCtrlSpuSimulationEnable;
#endif
	MenuCtrlSpinInteger *mCtrlSceneIndex;
	MenuCtrlSpinBool *mCtrlShowLocalAxis;
	MenuCtrlSpinBool *mCtrlShowContactPoints;
	MenuCtrlSpinBool *mCtrlShowRigidBodyState;
	MenuCtrlSpinBool *mCtrlShowJoint;
	MenuCtrlSpinBool *mCtrlShowAABB;
	MenuCtrlSpinBool *mCtrlSleepEnable;
	MenuCtrlSpinInteger *mCtrlNumSPUs;

	// --------------------------------------------------------
	// パラメータ
	
	RigidBodies *mRigidBodies;
	RayCast		*mRayCast;

	bool mSyncWait;
	int  mFrameCount;

	bool mStartThrowing;
	float mChargeTime;

	int mThrowBody;
	int mGroundBody;

	const char *mSceneDescription;

	// ラージメッシュ
	LargeTriMesh mLargeMesh[8];
	int mLargeMeshContainerIdx[8];
	int mLargeMeshInstance[8];
	
	// 凸メッシュ
	TriMesh mTaruMesh;
	int mTaruMeshContainerIdx;

	// --------------------------------------------------------
	// PhysicsEffectsスレッド

	PhysicsEffectsThreadParam mPfxThreadParam;
	PhysicsEffectsThreadUtil::PhysicsEffectsThread mPfxThread;

#ifndef WIN32
	CellSpurs mSpursInstance;
	SampleUtilSpursPrintfService mSpursPrintfService;
	RigidBodyTaskMulti *mRigidBodyTask;
	RayCastTaskMulti *mRayCastTask;
#endif

public:
	PhysicsSample(const char *appname);
	~PhysicsSample();
	
	// --------------------------------------------------------
	// フレームワークから継承したメソッド

	// 物理エンジン用
	bool onInitPhysicsEngine();
	void onShutdownPhysicsEngine();
	void onInitPhysicsWorld();
	void onReleasePhysicsWorld();
	void onInitPhysicsScene();
	void onWaitSimulation();
	void onUpdateSimulation();
	void onStartSimulation();
	
	// その他
	bool onUpdate();
	void onReset();
	void onRender();
	void onRenderAuxils();
	void initRenderContainerList();
	void clearRenderContainerList();
	void onInitMenuCtrl();
	void onMenuCtrlChange(MenuCtrlBase *ctrl);

	// --------------------------------------------------------
	// 剛体の作成

	#include "Util/PhysicsBodies.h"
	#include "PhysicsRagdoll.h"

	void createWall(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createPyramid(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createTowerCircle(const Vector3 &offsetPosition,int stackSize,int rotSize,const Vector3 &boxSize);

	// --------------------------------------------------------
	// 物理シーンの作成
	
	void createScene1();	// 剛体テスト1:
	void createScene2();	// 剛体テスト2:3000ボックス落下
	void createScene3();	// 剛体テスト3:スタック2000
	void createScene4();	// 剛体テスト4:ラグドール136
	void createScene5();	// 剛体テスト5:凸メッシュ1000個落下
	void createScene6();	// 剛体テスト6:ラージメッシュに基本形状剛体1000個落下
	void createScene7();	// 剛体テスト7:ラージメッシュに凸メッシュ剛体1000個落下
	void createScene8();	// 剛体テスト8:シーン5＋レイキャスト200本

	// --------------------------------------------------------
	// 剛体の操作

	void throwBody(int ballIndex);
	void createLargeMeshShape();
	void createLargeMeshBody();
	void createMeshShape();
	
	// --------------------------------------------------------
	// レイキャスト
	
	Ray worldRays[NUMRAYS];
	
	void initRays();
	void castRays();
};

#endif
