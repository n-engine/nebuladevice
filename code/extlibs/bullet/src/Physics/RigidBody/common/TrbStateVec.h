/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRBSTATEVEC_H__
#define __TRBSTATEVEC_H__

#include <stdlib.h>
#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PfxHandle.h"
// Move Type
enum {
	MoveTypeFixed    = 0,
	MoveTypeActive   = 1,
	MoveTypeKeyframe = 3,
	MoveTypeOneWay   = 5,
	MoveTypeTrigger  = 7,
	MoveTypeCount
};

#define MOVE_TYPE_CAN_SLEEP	((1<<MoveTypeActive)|(1<<MoveTypeKeyframe)|(1<<MoveTypeOneWay))
#define MOVE_TYPE_DYNAMIC	((1<<MoveTypeActive)|(1<<MoveTypeOneWay))
#define MOVE_TYPE_NODYNAMIC	~MOVE_TYPE_DYNAMIC

//
// Rigid Body state
//

class TrbState
{
public:
	TrbState()
	{
		setMoveType(MoveTypeActive);
		contactFilterSelf=contactFilterTarget=0xffff;
		sleeping = 0;
		useSleep = 1;
		bodyHandle=NULL;
		sleepCount=0;
		useCcd = 0;
		useContactCallback = 0;
		useSleepCallback = 0;
		uniqueId = 0;
		linearDamping = 1.0f;
		angularDamping = 0.99f;
	}

	TrbState(const uint8_t m, const Vector3 x, const Quat q, const Vector3 v, const Vector3 omega );

	PfxHandle	bodyHandle;
	uint16_t	uniqueId;

	uint16_t	sleepCount;
	uint8_t		moveType;

	uint8_t		sleeping           : 1;
	uint8_t		useSleep           : 1;
	uint8_t		useCcd		       : 1;
	uint8_t		useContactCallback : 1;
	uint8_t		useSleepCallback   : 1;

	uint16_t	contactFilterSelf;
	uint16_t	contactFilterTarget;

	float		center[3];		// AABB center(World)
	float		half[3];		// AABB half(World)

	float		linearDamping;
	float		angularDamping;

	Vector3     fX;				// position
	Quat        fQ;				// orientation
	Vector3     fV;				// velocity
	Vector3     fOmega;			// angular velocity

	inline void setZero();      // Zeroes out the elements
	inline void setIdentity();  // Sets the rotation to identity and zeroes out the other elements

	uint16_t	getContactFilterSelf() const {return contactFilterSelf;}
	void		setContactFilterSelf(uint16_t filter) {contactFilterSelf = filter;}

	uint16_t	getContactFilterTarget() const {return contactFilterTarget;}
	void		setContactFilterTarget(uint16_t filter) {contactFilterTarget = filter;}

	uint8_t		getMoveType() const {return moveType;}
	void		setMoveType(uint8_t t) {moveType = t;sleeping=0;sleepCount=0;}

	uint8_t		getMoveTypeBits() const {return (1<<moveType)|(1<<(moveType+sleeping));}

	bool		isAsleep() const {return sleeping==1;}
	bool		isAwake() const {return sleeping==0;}

	void		wakeup() {sleeping=0;sleepCount=0;}
	void		sleep() {if(useSleep) {sleeping=1;sleepCount=0;}}

	uint8_t		getUseSleep() const {return useSleep;}
	void		setUseSleep(uint8_t b) {useSleep=b;}

	uint8_t		getUseCcd() const {return useCcd;}
	void		setUseCcd(uint8_t b) {useCcd=b;}

	uint8_t		getUseContactCallback() const {return useContactCallback;}
	void		setUseContactCallback(uint8_t b) {useContactCallback=b;}

	uint8_t		getUseSleepCallback() const {return useSleepCallback;}
	void		setUseSleepCallback(uint8_t b) {useSleepCallback=b;}

	void	 	incrementSleepCount() {sleepCount++;}
	void		resetSleepCount() {sleepCount=0;}
	uint16_t	getSleepCount() const {return sleepCount;}

	inline void setAuxils(const Vector3 &centerLocal,const Vector3 &halfLocal);
	inline void	setAuxilsCcd(const Vector3 &centerLocal,const Vector3 &halfLocal,float timeStep);
} __attribute__ ((aligned(16)));

inline
TrbState::TrbState(const uint8_t m, const Vector3 x, const Quat q, const Vector3 v, const Vector3 omega)
{
	setMoveType(m);
	fX = x;
	fQ = q;
	fV = v;
	fOmega = omega;
	contactFilterSelf=contactFilterTarget=0xffff;
	bodyHandle=NULL;
	sleeping = 0;
	useSleep = 1;
	useCcd = 0;
	useContactCallback = 0;
	useSleepCallback = 0;
	sleepCount=0;
	linearDamping = 1.0f;
	angularDamping = 0.99f;
}

inline void
TrbState::setIdentity()
{
	fX = fV = fOmega = Vector3(0);
	fQ = Quat::identity();
}

inline void
TrbState::setZero()
{
	fX = fV = fOmega = Vector3(0);
	fQ = Quat(0);
}

inline void
TrbState::setAuxils(const Vector3 &centerLocal,const Vector3 &halfLocal)
{
	Vector3 centerW = fX + rotate(fQ,centerLocal);
	Vector3 halfW = absPerElem(Matrix3(fQ)) * halfLocal;
	center[0] = centerW[0];
	center[1] = centerW[1];
	center[2] = centerW[2];
	half[0] = halfW[0];
	half[1] = halfW[1];
	half[2] = halfW[2];
}

inline void
TrbState::setAuxilsCcd(const Vector3 &centerLocal,const Vector3 &halfLocal,float timeStep)
{
	Vector3 centerW = fX + rotate(fQ,centerLocal);
	Vector3 halfW = absPerElem(Matrix3(fQ)) * halfLocal;

	Vector3 diffvec = fV*timeStep;

	Vector3 newCenter = centerW + diffvec;
	Vector3 aabbMin = minPerElem(newCenter - halfW,centerW - halfW);
	Vector3 aabbMax = maxPerElem(newCenter + halfW,centerW + halfW);
	
	centerW = 0.5f * (aabbMin + aabbMax);
	halfW =0.5f * (aabbMax - aabbMin);

	center[0] = centerW[0];
	center[1] = centerW[1];
	center[2] = centerW[2];

	half[0] = halfW[0];
	half[1] = halfW[1];
	half[2] = halfW[2];
}

#endif /* __TRBSTATEVEC_H__ */

