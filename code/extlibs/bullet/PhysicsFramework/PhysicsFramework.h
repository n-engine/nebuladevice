/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICSFRAMEWORK_H__
#define __PHYSICSFRAMEWORK_H__

#include <vector>
#include <vectormath_aos.h>

#include "FWGLApplication.h"
#include "tutorialUtils.h"
#include "tutorialLight.h"
#include "ShaderProgram.h"

#include "RenderShape.h"
#include "RenderObject.h"
#include "CustomPad.h"
#include "CustomTime.h"
#include "CommonRigidBody.h"
#include "MenuCtrl.h"

#include "PhysicsFramework/RenderContainer/RenderContainer.h"
#include "PhysicsFramework/RenderContainer/MeshContainer.h"
#include "PhysicsFramework/RenderContainer/InstanceMeshContainer.h"
#include "PhysicsFramework/RenderContainer/SkinMeshContainer.h"
#include "PhysicsFramework/RenderContainer/DynMeshContainer.h"
#include "PhysicsFramework/RenderContainer/CapsuleContainer.h"
#include "PhysicsFramework/RenderContainer/WaterSurfaceContainer.h"

using namespace Vectormath;
using namespace Vectormath::Aos;
using namespace std;

// Cg プログラム
#ifdef WIN32
	#define VS_PROGRAM_MESH				"shader/vs_mesh.cg"
	#define FS_PROGRAM_MESH				"shader/fs_mesh.cg"
	#define VS_PROGRAM_INSTANCEMESH		"shader/vs_instancemesh.cg"
	#define FS_PROGRAM_INSTANCEMESH		"shader/fs_instancemesh.cg"
	#define VS_PROGRAM_SKINMESH			"shader/vs_skinmesh.cg"
	#define FS_PROGRAM_SKINMESH			"shader/fs_skinmesh.cg"
#else
	#define VS_PROGRAM_MESH				"shader/vs_mesh.vpo"
	#define FS_PROGRAM_MESH				"shader/fs_mesh.fpo"
	#define VS_PROGRAM_INSTANCEMESH		"shader/vs_instancemesh.vpo"
	#define FS_PROGRAM_INSTANCEMESH		"shader/fs_instancemesh.fpo"
	#define VS_PROGRAM_SKINMESH			"shader/vs_skinmesh.vpo"
	#define FS_PROGRAM_SKINMESH			"shader/fs_skinmesh.fpo"
#endif

// 操作
#define MOVE_DELTA 0.5
#define ANGLE_DELTA 0.05

// クリア色
#define CLEAR_COLOR	0.1f

//パッド数
#define PAD_MAX_NUM 2

///////////////////////////////////////////////////////////////////////////////
// PhysicsFramework class

class PhysicsFramework : public FWGLApplication
{
protected:
	FWTimeVal mLastTime;
	float mTimeStep;
	bool mRenderActive;
	bool mParallelSimulation;
	char mDebugMsg[256];
	char mAppPath[256];
	const char *mApplicationID;
	
	MenuCtrlSpinBool *mCtrlVsyncActive;
	MenuCtrlSpinBool *mCtrlSimulating;
	MenuCtrlSpinBool *mCtrlStepSimulation;
	MenuCtrlSpinBool *mCtrlRotationInverse;
	
	virtual void getAppPath(const char *appId);
	
public:
	PhysicsFramework(const char *applicationName,const char *applicationID = NULL);
	virtual ~PhysicsFramework();

	// Cgエラーチェック
	bool checkGLError()
	{
		GLenum glError = glGetError();
		if(glError != 0) {
			FWDPRINT("GL error! %d\n",glError);
			return false;
		}
		return true;
	}
	
	// ---------------------------------------------------------------------------
	// パラメータの設定と取得

	void setRenderActive(bool flag) {mRenderActive=flag;}
	bool getRenderActive() {return mRenderActive;}
	void setTimeStep(float dt) {mTimeStep=dt;}
	float getTimeStep() {return mTimeStep;}
	void setParallelSimulationActive(bool flag) {mParallelSimulation=flag;}
	bool getParallelSimulationActive() {return mParallelSimulation;}
	
	// ---------------------------------------------------------------------------
	// Framework Method
	
	virtual bool onInit(int argc, char **ppArgv);
	virtual void onShutdown();
	virtual bool onUpdate();
	virtual void onRender();
	virtual void onUserRender() {}
	virtual void onRenderAuxils() {}

	// ---------------------------------------------------------------------------
	// Physics Framework Method
	// ※ 物理エンジンに固有のAPIを継承先で記述してください

	// 物理エンジンの初期化と開放
	virtual bool onInitPhysicsEngine();
	virtual void onShutdownPhysicsEngine();

	// 物理ワールドの構築と破棄
	virtual void onInitPhysicsWorld();
	virtual void onReleasePhysicsWorld();

	// シーンの構築と破棄
	virtual void onInitPhysicsScene();
	virtual void onReleasePhysicsScene();

	// 物理ワールドをmTimeStepに指定された時間で進める
	virtual void onStartSimulation() {}
	virtual void onWaitSimulation() {}

	// シミュレーションの更新（剛体属性を変更するなど）
	virtual void onUpdateSimulation() {}

	// 物理ワールドの再構築 : 下記手順で呼ばれます
	//  onReleasePhysicsScene
	//  onReleasePhysicsWorld
	//  onShutdownPhysicsEngine
	//  onInitPhysicsEngine
	//  onInitPhysicsWorld
	//  onInitPhysicsScene
	virtual void onReset();

	// ---------------------------------------------------------------------------
	// 剛体の管理

private:
	vector<CommonRigidBody*> mRigidBodyList;

public:
	void clearRigidBodyList();
	void updateRigidBodyList();
	int getCommonRigidBodyCount() {return mRigidBodyList.size();}
	CommonRigidBody *getCommonRigidBody(int i) {return mRigidBodyList[i];}
	void addCommonRigidBody(CommonRigidBody *body) {mRigidBodyList.push_back(body);}

	// ---------------------------------------------------------------------------
	// Utility
	
	void getModelViewMatrix(Matrix4 &modelview);
	void getModelViewProjectionMatrix(Matrix4 &modelviewproj);
	void screenToWorld(Vector3 &screenPosition);
	void worldToScreen(Vector3 &worldPosition);
	void setDebugMessage(const char *msg) {strcpy(mDebugMsg,msg);}

	// ---------------------------------------------------------------------------
	// 表示用基本形状の作成

	RenderObject *createRenderBox(const Vector3 &pos,const Matrix3 &rot,const Vector4 &color,const Vector3 &size);
	RenderObject *createRenderSphere(const Vector3 &pos,const Matrix3 &rot,const Vector4 &color,float radius);
	RenderObject *createRenderCapsule(const Vector3 &pos,const Matrix3 &rot,const Vector4 &color,float halfLength,float radius);

	// ---------------------------------------------------------------------------
	// 描画コンテナ 0:Box 1:Sphere 2:Capsule
	
private:
	CGcontext mContext;

	vector<ShaderProgramBase*> mShaderProgramList;
	vector<RenderContainer*> mRenderContainerList;

	void initShaderProgram();
	void clearShaderProgram();

protected:
	CGcontext getCgContext() {return mContext;}

	virtual void initRenderContainerList();
	virtual void clearRenderContainerList();
	virtual void setupRenderContainerList();	// ※ RenderObjectを全て登録してから呼び出す
	virtual void resetRenderContainerList();

	int  addRenderContainer(RenderContainer* container);
	int  getRenderContainerCount() {return mRenderContainerList.size();}
	RenderContainer* getRenderContainer(int containerIdx) {return mRenderContainerList[containerIdx];}
	
	void drawRenderContainerList();
	
	ShaderProgramBase *getShaderProgram(int progIdx) {return mShaderProgramList[progIdx];}
	
	// シェーダープログラムインデックス
	int mMeshShaderIdx,mInstanceMeshShaderIdx,mSkinMeshShaderIdx;
	
	// 初期状態で登録される基本形状用描画コンテナ
	int mBoxContainer,mSphereContainer,mCapsuleContainer;
private:
	// ---------------------------------------------------------------------------
	// GL Method

	void initScene();
	void clearScene();
	void drawObjects();

	// 補助オブジェクトの描画
	void drawAxis(float x,float y,float z,float len);
	void drawPlane();
	
protected:
	// ---------------------------------------------------------------------------
	// GL Parameter

	GLuint mFence;
	
	float mLightRadius,mLightRadX,mLightRadY;
	float mViewRadius,mViewRadX,mViewRadY,mViewHeight;
	Vector3	mViewPos;

	tutorialLight mLight;

	Matrix4 mMv;   // ModelView Matrix
	Matrix4 mProj; // Projection Matrix

	virtual void createModelViewMatrix(Matrix4 &m);
	virtual void createProjectionMatrix(Matrix4 &m);

	// ---------------------------------------------------------------------------
	// Selection
	
	bool drawCursorEnable;
	
	Vector3 mCursorPos; // カーソルのスクリーン座標
	GLuint  mCursorTex;

	GLuint loadTexture(const char *imageFile,int w,int h);
	void drawCursor(const float *color);

public:
	void enableDrawCursor() {drawCursorEnable = true;}
	void disableDrawCursor() {drawCursorEnable = false;}
	
protected:

	// ---------------------------------------------------------------------------
	// Pad
	int mPadNum;
	CustomPad mCustomPad;
	CustomPad mCustomPad2;
	CustomPad *mPadPtr[PAD_MAX_NUM];

	// ---------------------------------------------------------------------------
	// Performance Monitor

	CustomTime mLoopTime;
	CustomTime mSimTime;
	CustomTime mDrawTime;

	unsigned int mInternalFrameCount;
	unsigned int mSimulationCount;
	
	// ---------------------------------------------------------------------------
	// Menu
	
private:
	bool mMenuOpen;
	int mMenuCursor;
	int mContWait;

	vector<MenuCtrlBase*> mMenuCtrls;

	void initCursorPosition();
	void upMenuCursor();
	void downMenuCursor();
	void leftMenuCursor();
	void rightMenuCursor();

	void clearMenuCtrl();
	void initMenuCtrl();
	void updateMenuCtrl();
	void renderMenuCtrl();

protected:
	MenuCtrlBase *getCurMenuCtrl() {return mMenuCtrls[mMenuCursor];}
	MenuCtrlBase *getMenuCtrl(int i) {return mMenuCtrls[i];}

	int  addMenuCtrl(MenuCtrlBase *ctrl);

	virtual void onInitMenuCtrl() {}
	virtual void onUpdateMenuCtrl() {}
};

#endif
