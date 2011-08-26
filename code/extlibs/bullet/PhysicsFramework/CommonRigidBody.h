/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __COMMON_RIGIDBODY_H__
#define __COMMON_RIGIDBODY_H__

#include <vector>
#include "RenderObject.h"

using namespace std;

class CommonRigidBody
{
protected:
	void *mBody;
	vector<RenderObject*> mRenderObjList;

public:
	CommonRigidBody(void *body) {setRigidBody(body);}
	virtual ~CommonRigidBody() {clear();}

	void addRenderObject(RenderObject *renderObj) {mRenderObjList.push_back(renderObj);}
	int  getRenderObjectCount() {return mRenderObjList.size();}
	RenderObject *getRenderObject(int i) {return mRenderObjList[i];}
	
	void setRigidBody(void *body) {mBody = body;}
	void *getRigidBody() {return mBody;}

	void init();
	void clear();
	void update();
	
	// -----------------------------------------------
	// ※ 物理エンジン固有の剛体オブジェクトのパラメータにアクセスするコードを
	//    継承先で実装してください

	// 位置
	virtual Vector3 getPosition() = 0;
	virtual Matrix3 getRotation() = 0;

	Transform3 getTransform() {return Transform3(getRotation(),getPosition());}
};

#endif
