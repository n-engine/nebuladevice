/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2009 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __LOWLEVELAPP_H__
#define __LOWLEVELAPP_H__

#include "Physics/LowLevelPhysics.h"
#include "Physics/Base/PhysicsCommon.h"
#include "PhysicsFramework/PhysicsFramework.h"
#include "SpuUserDefined.h"

#ifdef __PPU__
	#include "Util/spurs_util_spu_printf_service.h"
#endif

#define TIMESTEP			0.016f
#define SOLVER_ITERATION	10
#define NUM_SPU				5
#define MAX_USERBODIES		5000
#define MAX_CONSTRAINTS		30000

///////////////////////////////////////////////////////////////////////////////
// User Render Object

class UserRenderObject : public CommonRigidBody
{
public:
	UserRenderObject(UserBody *userBody) : CommonRigidBody(userBody)
	{
	}
	
	Vector3 getPosition() {return ((UserBody*)getRigidBody())->position;}
	Matrix3	getRotation() {return Matrix3(((UserBody*)getRigidBody())->orientation);}
};

///////////////////////////////////////////////////////////////////////////////
// LowLevelApp class

class LowLevelApp : public PhysicsFramework , public MenuCtrlCallback
{
private:
	// --------------------------------------------------------
	// Menu Control

#ifdef WIN32
	MenuCtrlLabelBool *mCtrlSpuSimulationEnable;
#else
	MenuCtrlSpinBool *mCtrlSpuSimulationEnable;
#endif
	MenuCtrlSpinInteger *mCtrlSceneIndex;
	MenuCtrlSpinBool *mCtrlShowLocalAxis;
	MenuCtrlSpinBool *mCtrlShowContactPoints;
	MenuCtrlSpinBool *mCtrlShowRigidBodyState;
	MenuCtrlSpinBool *mCtrlShowAABB;
	MenuCtrlSpinInteger *mCtrlNumSPUs;

	// --------------------------------------------------------
	// Parameter
	
	int  mFrameCount;

	const char *mSceneDescription;

#ifdef __PPU__
	CellSpurs mSpursInstance;
	SampleUtilSpursPrintfService mSpursPrintfService;
#else
	void *mSpursInstance;
#endif

	// --------------------------------------------------------
	// User Data
	
	int mNumUserBodies;
	UserBody mUserBodies[MAX_USERBODIES];
	
	void createSphere(float radius,float mass,Vector3 pos,Quat rot);
	void createBox(Vector3 extent,float mass,Vector3 pos,Quat rot);
	void createCapsuleX(float halfLen,float radius,float mass,Vector3 pos,Quat rot);
	void createComposite(float mass,Vector3 pos,Quat rot);
	
	// --------------------------------------------------------
	// Low Level Components

	plPairInfo mPairInfo;

	int mNumConstraints;
	plConstraintHandle mConstraints[MAX_CONSTRAINTS];
	
	plBroadphaseHandle mBroadphase;
	plNarrowphaseHandle			mNarrowphase;
	plConstraintSolverHandle	mConstraintSolver;

	// --------------------------------------------------------
	// Simulation phases
	
	void broadphase();
	void detectCollision();
	void refreshContacts();
	void solveConstraints();
	void integrate();

public:
	LowLevelApp(const char *appname);
	~LowLevelApp();
	
	// --------------------------------------------------------
	// Framework Method
	
	// Physics
	bool onInitPhysicsEngine();
	void onShutdownPhysicsEngine();
	void onInitPhysicsWorld();
	void onInitPhysicsScene();
	void onReleasePhysicsScene();
	void onWaitSimulation();
	void onUpdateSimulation();
	void onStartSimulation();

	// Etc
	bool onUpdate();
	void onReset();
	void onRenderAuxils();
	void initRenderContainerList();
	void onInitMenuCtrl();
	void onMenuCtrlChange(MenuCtrlBase *ctrl);

	// --------------------------------------------------------
	// Helpers

	void createWall(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createPyramid(const Vector3 &offsetPosition,int stackSize,const Vector3 &boxSize);
	void createTowerCircle(const Vector3 &offsetPosition,int stackSize,int rotSize,const Vector3 &boxSize);
	
	// --------------------------------------------------------
	// Scene

	void createScene1();
	void createScene2();
	void createScene3();
};

#endif
