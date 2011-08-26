/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __T_RB_DYN_BODY_H__
#define __T_RB_DYN_BODY_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "TrbStateVec.h"

class CollObject;

class TrbDynBody
{
public:
	TrbDynBody()
	{
		fMass   = 0.0f;
		fCollObject = NULL;
		fElasticity = 0.2f;
		fFriction = 0.8f;
	}

	// Get methods
	float          getMass() const {return fMass;};
	float          getElasticity() const {return fElasticity;}
	float          getFriction() const {return fFriction;}
	CollObject*    getCollObject() const {return fCollObject;}
	const Matrix3 &getBodyInertia() const {return fIBody;}
	const Matrix3 &getBodyInertiaInv() const {return fIBodyInv;}
	float          getMassInv() const {return fMassInv;}

	// Set methods
	void           setMass(float mass) {fMass=mass;fMassInv=mass>0.0f?1.0f/mass:0.0f;}
	void           setBodyInertia(const Matrix3 bodyInertia) {fIBody = bodyInertia;fIBodyInv = inverse(bodyInertia);}
	void           setElasticity(float elasticity) {fElasticity = elasticity;}
	void           setFriction(float friction) {fFriction = friction;}
	void           setCollObject(CollObject *collObj) {fCollObject = collObj;}

private:
	// Rigid Body constants
	float          fMass;        // Rigid Body mass
	float          fMassInv;     // Inverse of mass
	Matrix3        fIBody;       // Inertia matrix in body's coords
	Matrix3        fIBodyInv;    // Inertia matrix inverse in body's coords
	float          fElasticity;  // Coefficient of restitution
	float          fFriction;    // Coefficient of friction

public:
	CollObject*    fCollObject;  // Collision object corresponding the RB
} __attribute__ ((aligned(16)));

#endif /* __T_RB_DYN_BODY_H__ */
