/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

///////////////////////////////////////////////////////////////////////////////
// 基本形状の剛体作成

TrbDynBody* createRigidBodyBox(const Vector3 &boxSize,const float boxMass)
{
	CollObject *collObj = mRigidBodies->createCollObject();
	assert(collObj);

	collObj->addBox(Box(boxSize), Transform3::identity());
	collObj->finish();

	RigidBodyProperty bodyProperty;
	bodyProperty.mass = boxMass;
	calcInertiaBox(boxSize,boxMass,bodyProperty.inertia);
	bodyProperty.collObject = collObj;
	TrbDynBody *rigidBody = mRigidBodies->createRigidBody(bodyProperty);
	assert(rigidBody);
	
	return rigidBody;
}

TrbDynBody* createRigidBodySphere(const float sphereRadius,const float sphereMass)
{
	CollObject *collObj = mRigidBodies->createCollObject();
	assert(collObj);

	collObj->addSphere(sphereRadius, Transform3::identity());
	collObj->finish();

	RigidBodyProperty bodyProperty;
	bodyProperty.mass = sphereMass;
	calcInertiaSphere(sphereRadius,sphereMass,bodyProperty.inertia);
	bodyProperty.collObject = collObj;
	TrbDynBody *rigidBody = mRigidBodies->createRigidBody(bodyProperty);
	assert(rigidBody);

	return rigidBody;
}

TrbDynBody* createRigidBodyCapsule(const float capsuleHalf,const float capsuleRadius,const float capsuleMass)
{
	CollObject *collObj = mRigidBodies->createCollObject();
	assert(collObj);

	collObj->addCapsule(Capsule(capsuleHalf,capsuleRadius), Transform3::identity());
	collObj->finish();

	RigidBodyProperty bodyProperty;
	bodyProperty.mass = capsuleMass;
	calcInertiaCylinderX(capsuleRadius,capsuleHalf,capsuleMass,bodyProperty.inertia);
	bodyProperty.collObject = collObj;
	TrbDynBody *rigidBody = mRigidBodies->createRigidBody(bodyProperty);
	assert(rigidBody);
	
	return rigidBody;
}

CommonRigidBody* createInstanceBox(TrbDynBody *boxBody,const Vector3 &boxSize,
								   const Vector3 &pos,const Quat &rot,
								   const Vector4 &color = Vector4(1.0f))
{
	InstanceProperty instProperty;
	instProperty.moveType = MoveTypeActive;
	instProperty.position = pos;
	instProperty.orientation = rot;
	instProperty.rigidBody = boxBody;
	int instance = mRigidBodies->createInstance(instProperty);
	assert(instance >= 0);
	
	PhysicsRigidBody *cmbody = new PhysicsRigidBody(mRigidBodies,instance);
	RenderObject *renderObj = createRenderBox(Vector3(0.0f),Matrix3::identity(),color,boxSize);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return cmbody;
}

CommonRigidBody* createInstanceSphere(TrbDynBody *sphereBody,float sphereRadius,
									  const Vector3 &pos,const Quat &rot,
									  const Vector4 &color = Vector4(1.0f))
{
	InstanceProperty instProperty;
	instProperty.moveType = MoveTypeActive;
	instProperty.position = pos;
	instProperty.orientation = rot;
	instProperty.rigidBody = sphereBody;
	int instance = mRigidBodies->createInstance(instProperty);
	assert(instance >= 0);
	
	PhysicsRigidBody *cmbody = new PhysicsRigidBody(mRigidBodies,instance);
	RenderObject *renderObj = createRenderSphere(Vector3(0.0f),Matrix3::identity(),color,sphereRadius);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return cmbody;
}

CommonRigidBody* createInstanceCapsule(TrbDynBody *capsuleBody,float capsuleHalf,float capsuleRadius,
									   const Vector3 &pos,const Quat &rot,
									   const Vector4 &color = Vector4(1.0f))
{
	InstanceProperty instProperty;
	instProperty.moveType = MoveTypeActive;
	instProperty.position = pos;
	instProperty.orientation = rot;
	instProperty.rigidBody = capsuleBody;
	int instance = mRigidBodies->createInstance(instProperty);
	assert(instance >= 0);
	
	PhysicsRigidBody *cmbody = new PhysicsRigidBody(mRigidBodies,instance);
	RenderObject *renderObj = createRenderCapsule(Vector3(0.0f),Matrix3::identity(),color,capsuleHalf,capsuleRadius);
	cmbody->addRenderObject(renderObj);
	cmbody->init();
	addCommonRigidBody(cmbody);

	return cmbody;
}

///////////////////////////////////////////////////////////////////////////////
// 地面の作成

int createGround()
{
	Vector3 groundSize(150.0f, 2.0f, 150.0f);
	TrbDynBody *rigidBody = createRigidBodyBox(groundSize,5.0f);
	
	CommonRigidBody *rb = createInstanceBox(rigidBody,groundSize,Vector3(0.0f, -2.0f, 0.0f),Quat::identity(),Vector4(0.4,0.25,0.15,1));
	mRigidBodies->setMoveType((int)rb->getRigidBody(),MoveTypeFixed);
	
	return (int)rb->getRigidBody();
}

///////////////////////////////////////////////////////////////////////////////
// インタラクション用剛体の作成

int createThrowingBody(const Vector3 &offsetPos)
{
	const Vector3 boxSize(1.0f);
	const float boxMass = 2.0f;

	TrbDynBody *rigidBody = createRigidBodyBox(boxSize,boxMass);

	CommonRigidBody *rb = createInstanceBox(rigidBody,boxSize,offsetPos,Quat::identity(),Vector4(1,0.7,0.7,1));

	return (int)rb->getRigidBody();
}
