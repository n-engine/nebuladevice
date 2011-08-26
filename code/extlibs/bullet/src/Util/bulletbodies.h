/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef _BULLET_RIGIDBODIES_H
#define _BULLET_RIGIDBODIES_H


btRigidBody*	createRigidBodyBox(const Vector3 &boxSize,const float boxMass,btDiscreteDynamicsWorld* dynaWorld)
{
	//bad to create a boxshape for each box!
	btBoxShape* boxShape = new btBoxShape(btVector3(boxSize[0]-COLLISION_RADIUS,boxSize[1]-COLLISION_RADIUS,boxSize[2]-COLLISION_RADIUS));
	m_collisionShapes.push_back(boxShape);

	btVector3 invInertia(0,0,0);

	boxShape->calculateLocalInertia(boxMass,invInertia);
	
	AosVectormathMotionState* motionState = new AosVectormathMotionState();

	btRigidBody::btRigidBodyConstructionInfo boxInfo(boxMass,motionState,boxShape,invInertia);

	btRigidBody* rigidBody = new btRigidBody(boxInfo);

	if(dynaWorld) {
		dynaWorld->addRigidBody(rigidBody);
	}
	
	return rigidBody;
}



btRigidBody*	createRigidBodySphere(const float radius,const float boxMass,btDiscreteDynamicsWorld* dynaWorld)
{
	//bad to create sphere shape for each sphere!
	btSphereShape* boxShape = new btSphereShape(radius);
	m_collisionShapes.push_back(boxShape);
	btVector3 invInertia(0,0,0);

	boxShape->calculateLocalInertia(boxMass,invInertia);
	
	AosVectormathMotionState* motionState = new AosVectormathMotionState();

	btRigidBody::btRigidBodyConstructionInfo boxInfo(boxMass,motionState,boxShape,invInertia);

	btRigidBody* rigidBody = new btRigidBody(boxInfo);

	if(dynaWorld) {
		dynaWorld->addRigidBody(rigidBody);
	}
	
	return rigidBody;
}

btRigidBody*	createRigidBodyCapsule(const float capsuleHalf,const float capsuleRadius,const float mass,btDiscreteDynamicsWorld* dynaWorld)
{
	//bad to create sphere shape for each sphere!
	btCapsuleShape* capsuleShape = new btCapsuleShapeX(capsuleRadius,capsuleHalf*2);
	m_collisionShapes.push_back(capsuleShape);
	btVector3 invInertia(0,0,0);

	capsuleShape->calculateLocalInertia(mass,invInertia);
	
	AosVectormathMotionState* motionState = new AosVectormathMotionState();

	btRigidBody::btRigidBodyConstructionInfo boxInfo(mass,motionState,capsuleShape,invInertia);

	btRigidBody* rigidBody = new btRigidBody(boxInfo);

	if(dynaWorld) {
		dynaWorld->addRigidBody(rigidBody);
	}
	
	return rigidBody;
}



btCollisionObject*	createFixedRigidBodyBox(const Vector3 &boxSize,const float boxMass,btDiscreteDynamicsWorld* dynaWorld)
{
	//bad to create a boxshape for each box!
	btBoxShape* boxShape = new btBoxShape(btVector3(boxSize[0]-COLLISION_RADIUS,boxSize[1]-COLLISION_RADIUS,boxSize[2]-COLLISION_RADIUS));
	m_collisionShapes.push_back(boxShape);

	btVector3 invInertia(0,0,0);

	boxShape->calculateLocalInertia(boxMass,invInertia);
	
	AosVectormathMotionState* motionState = new AosVectormathMotionState();

	//btRigidBody::btRigidBodyConstructionInfo boxInfo(boxMass,motionState,boxShape,invInertia);
//
//	btRigidBody* rigidBody = new btRigidBody(boxInfo);
	btCollisionObject* colObj = new btCollisionObject();
	colObj->setCollisionShape(boxShape);
	

	if(dynaWorld) {
		dynaWorld->addCollisionObject(colObj);
	}
	
	return colObj;
}


btCollisionObject *createGroundBullet()
{
	//for Bullet better to create infinite plane instead of box!
	Vector3 groundSize(150.0f, 2.0f, 150.0f);
	Vector4 groundColor(129/255.0f, 62/255.0f, 22/255.0f, 0.0f);
	btCollisionObject* rigidBody = createFixedRigidBodyBox(groundSize,.0f,this->m_physicsWorld);
	
	rigidBody->setActivationState(ISLAND_SLEEPING);

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(0.0f, -2.0f, 0.0f));

	BulletRigidBody *cmbody = new BulletRigidBody(rigidBody);
	
	rigidBody->setWorldTransform(trans);

	RenderObject *renderObj = createRenderBox(Vector3(0.0f),Matrix3::identity(),groundColor,groundSize);
	renderObj->mRelTransform.setTranslation(Vector3(0,-2,0));

	
	
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return rigidBody;
}


CommonRigidBody* createInstanceBox(btRigidBody *boxBody,const Vector3 &boxSize,const Vector3 &pos,const Quat &rot,const Vector4 &color = Vector4(1.0f))
{
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(getBtVector3(pos));
	trans.setRotation(getBtQuat(rot));

	boxBody->setCenterOfMassTransform(trans);

	
	BulletRigidBody *cmbody = new BulletRigidBody(boxBody);
	RenderObject *renderObj = createRenderBox(Vector3(0.0f),Matrix3::identity(),color,boxSize);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);
	
	return cmbody;
}

CommonRigidBody* createInstanceSphere(btRigidBody *sphereBody,float sphereRadius,const Vector3 &pos,const Quat &rot,const Vector4 &color = Vector4(1.0f))
{


	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(getBtVector3(pos));
	trans.setRotation(getBtQuat(rot));

	sphereBody->setCenterOfMassTransform(trans);


	BulletRigidBody *cmbody = new BulletRigidBody(sphereBody);
	RenderObject *renderObj = createRenderSphere(Vector3(0.0f),Matrix3::identity(),color,sphereRadius);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return cmbody;
}



CommonRigidBody* createInstanceCapsule(btRigidBody *capsuleBody,float capsuleHalf,float capsuleRadius,const Vector3 &pos,const Quat &rot,const Vector4 &color = Vector4(1.0f))
{


	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(getBtVector3(pos));
	trans.setRotation(getBtQuat(rot));

	capsuleBody->setCenterOfMassTransform(trans);


	BulletRigidBody* cmbody = new BulletRigidBody(capsuleBody);
	RenderObject *renderObj = createRenderCapsule(Vector3(0.0f),Matrix3::identity(),color,capsuleHalf,capsuleRadius);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return cmbody;
}


#endif //_BULLET_RIGIDBODIES_H
