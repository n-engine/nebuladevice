/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */
struct PhysicsRagdoll
{
	static bool bodyExists;

	static TrbDynBody *headBody;
	static TrbDynBody *torsoBody;
	static TrbDynBody *pelvisBody;

	static TrbDynBody *upperArmBody;
	static TrbDynBody *foreArmBody;
	static TrbDynBody *handBody;

	static TrbDynBody *thighBody;
	static TrbDynBody *calfBody;
	static TrbDynBody *footBody;

	CommonRigidBody *head;
	CommonRigidBody *torso;
	CommonRigidBody *pelvis;
	CommonRigidBody *leftUpperArm;
	CommonRigidBody *rightUpperArm;
	CommonRigidBody *leftForeArm;
	CommonRigidBody *rightForeArm;
	CommonRigidBody *leftHand;
	CommonRigidBody *rightHand;
	CommonRigidBody *leftThigh;
	CommonRigidBody *rightThigh;
	CommonRigidBody *leftCalf;
	CommonRigidBody *rightCalf;
	CommonRigidBody *leftFoot;
	CommonRigidBody *rightFoot;
};

void initRagdoll();
void createRagdollBodies(PhysicsRagdoll &ragdoll,float scale);
void createRagdollInstance(PhysicsRagdoll &ragdoll,const Vector3& pos,float scale);
void createRagdoll(PhysicsRagdoll &ragdoll,const Vector3& pos, float scale);
