/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_SOLVER_FUNC_H__
#define __PFX_SOLVER_FUNC_H__

#include "Physics/LowLevelPhysics.h"

static inline
void setupConstraint(PfxConstraintPtr &constraint,PfxGenericConstraintRow *constraintRows,
	void *userConstraint,void *userObjectA,void *userObjectB,
	PfxSolverBody *solverBodyA,PfxSolverBody *solverBodyB)
{

	memset(constraintRows,0,NumConstraintRows(constraint)*sizeof(PfxGenericConstraintRow));

	// Get rigid body info from the user rigid body
	PfxRigidBody bodyA,bodyB;
	plBodyInfo bodyInfoA,bodyInfoB;

	bodyInfoA.position = (plReal*)&bodyA.position;
	bodyInfoA.orientation = (plReal*)&bodyA.orientation;
	bodyInfoA.linearVelocity = (plReal*)&bodyA.linearVelocity;
	bodyInfoA.angularVelocity = (plReal*)&bodyA.angularVelocity;
	bodyInfoA.restitution = &bodyA.restitution;
	bodyInfoA.friction = &bodyA.friction;
	bodyInfoA.invMass = &bodyA.invMass;
	bodyInfoA.invInertiaCol0 = (plReal*)&bodyA.invInertia[0];
	bodyInfoA.invInertiaCol1 = (plReal*)&bodyA.invInertia[1];
	bodyInfoA.invInertiaCol2 = (plReal*)&bodyA.invInertia[2];

	bodyInfoB.position = (plReal*)&bodyB.position;
	bodyInfoB.orientation = (plReal*)&bodyB.orientation;
	bodyInfoB.linearVelocity = (plReal*)&bodyB.linearVelocity;
	bodyInfoB.angularVelocity = (plReal*)&bodyB.angularVelocity;
	bodyInfoB.restitution = &bodyB.restitution;
	bodyInfoB.friction = &bodyB.friction;
	bodyInfoB.invMass = &bodyB.invMass;
	bodyInfoB.invInertiaCol0 = (plReal*)&bodyB.invInertia[0];
	bodyInfoB.invInertiaCol1 = (plReal*)&bodyB.invInertia[1];
	bodyInfoB.invInertiaCol2 = (plReal*)&bodyB.invInertia[2];

	plGetRigidBodyInfo(userObjectA,&bodyInfoA);
	plGetRigidBodyInfo(userObjectB,&bodyInfoB);

	// Get constraint info from the user constraint
	plConstraintInfo2 constraintInfo;
	constraintInfo.type = &constraintRows->type;
	constraintInfo.strideInBytes = sizeof(PfxGenericConstraintRow);
	constraintInfo.fps = 60.0f; // Todo:
	constraintInfo.erp = 0.0f;
	constraintInfo.cfm = &constraintRows->cfm;
	constraintInfo.constraintError = &constraintRows->rhs;
	constraintInfo.lowerLimit = &constraintRows->lowerLimit;
	constraintInfo.upperLimit = &constraintRows->upperLimit;
	constraintInfo.accumlatedImpulse = &constraintRows->accumImpulse;
	constraintInfo.jacobianLinearAxisA = (plReal*)&constraintRows->normal;
	constraintInfo.jacobianAngularAxisA = (plReal*)&constraintRows->relposCrossNormalA;
	constraintInfo.jacobianLinearAxisB = NULL;
	constraintInfo.jacobianAngularAxisB = (plReal*)&constraintRows->relposCrossNormalB;

	plGetConstraintInfo2(userConstraint,userObjectA,userObjectB,&constraintInfo);

	float restitution = 0.5f * (bodyA.restitution + bodyB.restitution);
	
	Matrix3 mA(bodyA.orientation);
	Matrix3 mB(bodyB.orientation);
	
	float massInvA,massInvB;
	Matrix3 inertiaInvA,inertiaInvB;
	
	massInvA = bodyA.invMass;
	inertiaInvA = mA * bodyA.invInertia * transpose(mA);

	massInvB = bodyB.invMass;
	inertiaInvB = mB * bodyB.invInertia * transpose(mB);

	solverBodyA->massInv = massInvA;
	solverBodyB->massInv = massInvB;
//	solverBodyA->friction = bodyA.friction;
//	solverBodyB->friction = bodyB.friction;

	for(int i=0;i<NumConstraintRows(constraint);i++) {
		PfxGenericConstraintRow &constraintRow = constraintRows[i];
		
		Vector3 normal = constraintRow.normal;
		
		float denom = massInvA + massInvB +
			dot(inertiaInvA * constraintRow.relposCrossNormalA,constraintRow.relposCrossNormalA) + 
			dot(inertiaInvB * constraintRow.relposCrossNormalB,constraintRow.relposCrossNormalB);
		
		float relVel = 
			(dot(bodyA.linearVelocity,normal) + dot(constraintRow.relposCrossNormalA,bodyA.angularVelocity)) - 
			(dot(bodyB.linearVelocity,normal) + dot(constraintRow.relposCrossNormalB,bodyB.angularVelocity));
		
		//constraintRow.rhs = -constraintRow.rhs-(1.0f+restitution)*relVel;
		constraintRow.rhs = -constraintRow.rhs-(1.0f+restitution)*relVel;
		constraintRow.rhs /= denom;
		constraintRow.jacDiagInv = (1.0f+restitution)/denom;

		constraintRow.angularComponentA = inertiaInvA * constraintRow.relposCrossNormalA;
		constraintRow.angularComponentB = inertiaInvB * constraintRow.relposCrossNormalB;

		float deltaImpulse = constraintRow.accumImpulse;
		solverBodyA->deltaLinearVelocity  += deltaImpulse * massInvA * normal;
		solverBodyA->deltaAngularVelocity += deltaImpulse * constraintRow.angularComponentA;
		solverBodyB->deltaLinearVelocity  -= deltaImpulse * massInvB * normal;
		solverBodyB->deltaAngularVelocity -= deltaImpulse * constraintRow.angularComponentB;
	}
}

static inline
void solveGenericConstraintRow(PfxGenericConstraintRow &constraint,PfxSolverBody &solverBodyA,PfxSolverBody &solverBodyB)
{
	const Vector3 normal = constraint.normal;
	float deltaImpulse = constraint.rhs - constraint.accumImpulse * constraint.cfm;
	float dVAdotN = dot(normal,solverBodyA.deltaLinearVelocity) + dot(constraint.relposCrossNormalA,solverBodyA.deltaAngularVelocity);
	float dVBdotN = dot(normal,solverBodyB.deltaLinearVelocity) + dot(constraint.relposCrossNormalB,solverBodyB.deltaAngularVelocity);
	deltaImpulse -= constraint.jacDiagInv * (dVAdotN - dVBdotN);

	float oldImpulse = constraint.accumImpulse;
	constraint.accumImpulse = PFX_CLAMP(oldImpulse + deltaImpulse,constraint.lowerLimit,constraint.upperLimit);
	deltaImpulse = constraint.accumImpulse - oldImpulse;

	solverBodyA.deltaLinearVelocity  += deltaImpulse * solverBodyA.massInv * normal;
	solverBodyA.deltaAngularVelocity += deltaImpulse * constraint.angularComponentA;
	solverBodyB.deltaLinearVelocity  -= deltaImpulse * solverBodyB.massInv * normal;
	solverBodyB.deltaAngularVelocity -= deltaImpulse * constraint.angularComponentB;
}

static inline
void postConstraint(PfxConstraintPtr &constraint,PfxGenericConstraintRow *constraintRows,void *userConstraint)
{
	plSetAccumlatedImpulse(userConstraint,&constraintRows->accumImpulse,sizeof(PfxGenericConstraintRow));
}

static inline
void updateVelocity(PfxSolverBody &solverBody,void *userObject)
{
	plSetDeltaVelocity(userObject,(plReal*)&solverBody.deltaLinearVelocity,(plReal*)&solverBody.deltaAngularVelocity);
}

#endif /* __PFX_SOLVER_FUNC_H__ */
