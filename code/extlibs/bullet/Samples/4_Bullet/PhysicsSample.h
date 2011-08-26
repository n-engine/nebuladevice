/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICS_SAMPLE_H__
#define __PHYSICS_SAMPLE_H__


// Framework Include
#include "PhysicsFramework.h"
#include "PhysicsActor.h"
#include "BulletMultiThreaded/Vectormath2Bullet.h"
#ifndef WIN32
#include "Util/SpursTask.h"
#include "Util/spurs_util_spu_printf_service.h"
#endif //WIN32

#define NUM_THREADS		1

// Collision Radius
#define COLLISION_RADIUS 0.01f

// Visual Debugger
//#define VISUALDEBUGGER_ENABLE

// タイムステップ
#define TIMESTEP	1.0f/60.0f

//#define USE_BATCH_RAYCASTER 1

//Experimental/testing to integrate Physics Effects batch raycaster on PS3
#ifndef WIN32
//#define USE_HYBRID_RAYCASTER 1
//#define USE_PHYSICS_EFFECTS_RAYCASTER 1
//#define USE_BATCH_RAYCASTER 1
#endif //WIN32

#define TRACK_CAMERA 0.2f

enum {
        CAM_TYPE_WORLD = 0,
        CAM_TYPE_TARGET,
        CAM_TYPE_FLYBY1,
        CAM_TYPE_FLYBY2,
        CAM_TYPE_FLYBY3,
        CAM_TYPE_TOP,
        CAM_TYPE_COUNT
};

///////////////////////////////////////////////////////////////////////////////
// レイキャスト設定

//#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
//#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
//#include <Physics/Collide/Query/CastUtil/hkpWorldRayCaster.h>
//#include <Physics/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h>

#include "btBulletDynamicsCommon.h"
#include "Util/aosvectormathmotionstate.h"
#include "Util/BulletRigidBody.h"
#include "BulletRagDoll.h"

#define NUMRAYS 500
class RagDoll;

///////////////////////////////////////////////////////////////////////////////
// PhysicsSample class

class PhysicsSample : public PhysicsFramework , public MenuCtrlCallback
{
private:
	// --------------------------------------------------------
	// メニューコントロール

	MenuCtrlSpinBool *mCtrlSpuSimulationEnable;
	
	MenuCtrlSpinBool*	mCtrlDebugDrawEnable;

	MenuCtrlSpinBool*	mMultiThreadedBroadphase;
	MenuCtrlSpinBool *mMultiThreadedConstraintSolver ;
	MenuCtrlSpinBool *mMultiThreadedNarrowphase;
	MenuCtrlSpinInteger *mCtrlSceneIndex;

	
	MenuCtrlSpinInteger* mCtrlNumSPUs;
	MenuCtrlSpinBool *mCtrlSleepEnable;

	// --------------------------------------------------------
	// パラメータ

	class btRigidBody*	mThrowBody;
	class btCollisionObject*	mGroundBody;

	class btRigidBody*  mCharacterBody;
	class BulletRigidBody* mRenderCharacter;
	class btHingeConstraint* mCharacterHinge;
	PhysicsActor viewerActor;
	bool mDoCharacterController;
	int mCamType;

	///raycast
	btVector3 m_raySource[NUMRAYS];
	btVector3 m_rayDest[NUMRAYS];
	btScalar m_rayHitFraction[NUMRAYS];
	btVector3 m_rayDirection[NUMRAYS];
	btVector3 m_rayHitPoint[NUMRAYS];
	btVector3 m_rayHitNormal[NUMRAYS];

//	RayCast		*mRayCast;


	bool mStartThrowing;
	float mChargeTime;

	int mFrameCount;
	const char *mSceneDescription;

	// メッシュ
	int mTaruMeshContainerIdx;

	// ラージメッシュ
	int mLargeMeshContainerIdx[8];

	char* stackBuffer;
	

	class btDefaultCollisionConfiguration*	m_collisionConfiguration;
	class btBroadphaseInterface*	m_pairCache;
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;
	
	btAlignedObjectArray<BulletRagDoll*>	m_ragdolls;
	class	btThreadSupportInterface*		m_collisionThreadSupport;
	class	btThreadSupportInterface*		m_solverThreadSupport;

	class btCollisionDispatcher*	m_dispatcher;
	class btConstraintSolver*		m_constraintSolver;
	class btDiscreteDynamicsWorld*	m_physicsWorld;

#ifndef WIN32
	CellSpurs mSpursInstance;
	SampleUtilSpursPrintfService mSpursPrintfService;

#endif //WIN32


	void destroyPERayCast ();
	void setupPERayCast ();

public:
	PhysicsSample(const char *appname);
	~PhysicsSample();
	
	// --------------------------------------------------------
	// フレームワークから継承したメソッド

	// 初期化と終了
	bool onInit(int argc, char **ppArgv);
	void onShutdown();
	
	// 物理エンジン用
	bool onInitPhysicsEngine();
	void onShutdownPhysicsEngine();
	void onInitPhysicsWorld();
	void onReleasePhysicsWorld();
	void onInitPhysicsScene();
	void onReleasePhysicsScene();
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

	virtual void createModelViewMatrix(Matrix4 &m);
	virtual void createProjectionMatrix(Matrix4 &m);

	// --------------------------------------------------------
	// 剛体の作成

	#include "Util/bulletbodies.h"

	void createWall(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createPyramid(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createTowerCircle(const Vector3 &offsetPosition,int stackSize,int rotSize,const Vector3 &boxSize);

	// --------------------------------------------------------
	// 物理シーンの作成
	
	void createScene1();	// 剛体テスト1
	void createScene2();	// 剛体テスト2
	void createScene3();	// 剛体テスト3
	void createScene4();	// 剛体テスト4
	void createScene5();	// 剛体テスト5
	void createScene6();	// 剛体テスト6
	void createScene7();	// 剛体テスト7
	void createScene8();	// 剛体テスト8
	void createScene9();
	void createScene10();
	void createScene11();

	// --------------------------------------------------------
	// 剛体の操作

//	void throwBody(hkpRigidBody *ballBody);
	void createLargeMeshShape();
	void createLargeMeshBody();
	void createMeshShape();

	// --------------------------------------------------------
	// レイキャスト
	
	

	void initRays();
	void castRays();
};

#endif
