/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <float.h>
#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/SortCommon.h"
#include "Physics/Base/SimdFunc.h"
#include "Physics/RigidBody/common/CollObject.h"
#include "Physics/RigidBody/common/RigidBodyConfig.h"
#include "Physics/RigidBody/common/SubData.h"
//#include "Physics/RigidBody/common/ConstraintCache.h"

#define NO_CONTACT_DISTANCE	999.0f
#define CONTACT_EPSILON		0.0f
#define SWAP(type, x, y) do {type t; t=x; x=y; y=t; } while (0)

///////////////////////////////////////////////////////////////////////////////
// Contact Point

struct ContactPoint
{
//	ConstraintCache constraints[3];

	uint8_t duration;
	uint8_t primIdxA;
	uint8_t primIdxB;
	SubData subData;

	float distance;
	float normal[3];
	float localVelocityA[3];
	float localVelocityB[3];
	float localPointA[3];
	float localPointB[3];

	// --------------------------------------------

	ContactPoint()
	{
		reset();
	}

	void reset()
	{
		distance = FLT_MAX;
		duration = 0;
		subData.type = 0;
		localVelocityA[0] = 0.0f;
		localVelocityA[1] = 0.0f;
		localVelocityA[2] = 0.0f;
		localVelocityB[0] = 0.0f;
		localVelocityB[1] = 0.0f;
		localVelocityB[2] = 0.0f;
		normal[0] = 0.0f;
		normal[1] = 0.0f;
		normal[2] = 0.0f;
	}
	
	void exchange()
	{
		SWAP(float,localPointA[0],localPointB[0]);
		SWAP(float,localPointA[1],localPointB[1]);
		SWAP(float,localPointA[2],localPointB[2]);
		SWAP(uint8_t,primIdxA,primIdxB);
		SWAP(float,localVelocityA[0],localVelocityB[0]);
		SWAP(float,localVelocityA[1],localVelocityB[1]);
		SWAP(float,localVelocityA[2],localVelocityB[2]);
		setNormal(-getNormal());
	}

	void setA(Point3 &contactPoint, const Transform3 & objectRelativeTransform,uint8_t primIdx_)
	{
		Vector3 p(objectRelativeTransform * contactPoint);
		setLocalPointA(p);
		primIdxA = primIdx_;
	}

	void setB(Point3 &contactPoint, const Transform3 & objectRelativeTransform,uint8_t primIdx_)
	{
		Vector3 p(objectRelativeTransform * contactPoint);
		setLocalPointB(p);
		primIdxB = primIdx_;
	}
	
	void setLocalPointA(const Vector3 &p) {store_Vector3(p,localPointA);}
	void setLocalPointB(const Vector3 &p) {store_Vector3(p,localPointB);}
	void setLocalVelocityA(const Vector3 &v) {store_Vector3(v,localVelocityA);}
	void setLocalVelocityB(const Vector3 &v) {store_Vector3(v,localVelocityB);}
	void setNormal(const Vector3 &n) {store_Vector3(n,normal);}
	void setDistance(float d) {distance = d;}

	Vector3 getLocalPointA() const {return read_Vector3(localPointA);}
	Vector3 getLocalPointB() const {return read_Vector3(localPointB);}
	Vector3 getLocalVelocityA() const {return read_Vector3(localVelocityA);}
	Vector3 getLocalVelocityB() const {return read_Vector3(localVelocityB);}
	Vector3 getNormal() const {return read_Vector3(normal);}
	float   getDistance() const {return distance;}

	Vector3 getWorldPointA(const Vector3 &pos,const Quat &rot) const
	{
		return pos + rotate(rot,getLocalPointA());
	}
	
	Vector3 getWorldPointB(const Vector3 &pos,const Quat &rot) const
	{
		return pos + rotate(rot,getLocalPointB());
	}

	//float getMaxImpulse() const
	//{
	//	return constraints[0].accumImpulse;
	//}
};

///////////////////////////////////////////////////////////////////////////////
// Contact Pair (Contact Manifold)

struct ContactPair
{
	uint32_t duration;
	uint16_t numContacts;
	uint16_t stateIndex[2];
	
	float	compositeFriction;
	float	massInvA,massInvB;
	float	inertiaInvA[9];
	float	inertiaInvB[9];

	ContactPoint contactPoints[NUMCONTACTS_PER_BODIES];

	// --------------------------------------------
	
	void reset()
	{
		numContacts = 0;
		duration = 0;
		for(int i=0;i<NUMCONTACTS_PER_BODIES;i++)
			contactPoints[i].reset();
	}

	void exchange()
	{
		for(int i=0;i<numContacts;i++) {
			contactPoints[i].exchange();
		}
		SWAP(uint16_t,stateIndex[0],stateIndex[1]);
	}
	
	ContactPoint &getContactPoint(int idx) {return contactPoints[idx];}

	void setA(int idx,Point3 & localPoint, const Transform3 & objectRelativeTransform, uint8_t primIdx)
	{
		contactPoints[idx].setA(localPoint, objectRelativeTransform, primIdx);
	}

	void setB(int idx,Point3 & localPoint, const Transform3 & objectRelativeTransform,uint8_t primIdx)
	{
		contactPoints[idx].setB(localPoint, objectRelativeTransform, primIdx);
	}

	float getMassInvA() {return massInvA;}
	float getMassInvB() {return massInvB;}

	Matrix3 getInertiaInvA() {return Matrix3(
		read_Vector3(&inertiaInvA[0]),
		read_Vector3(&inertiaInvA[3]),
		read_Vector3(&inertiaInvA[6]));}

	Matrix3 getInertiaInvB() {return Matrix3(
		read_Vector3(&inertiaInvB[0]),
		read_Vector3(&inertiaInvB[3]),
		read_Vector3(&inertiaInvB[6]));}

	void setMassInvA(float massInv) {massInvA = massInv;}
	void setMassInvB(float massInv) {massInvB = massInv;}
	void setInertiaInvA(const Matrix3 &inertiaInv)
	{
		store_Vector3(inertiaInv[0],&inertiaInvA[0]);
		store_Vector3(inertiaInv[1],&inertiaInvA[3]);
		store_Vector3(inertiaInv[2],&inertiaInvA[6]);
	}

	void setInertiaInvB(const Matrix3 &inertiaInv)
	{
		store_Vector3(inertiaInv[0],&inertiaInvB[0]);
		store_Vector3(inertiaInv[1],&inertiaInvB[3]);
		store_Vector3(inertiaInv[2],&inertiaInvB[6]);
	}

	// --------------------------------------------
	
	inline uint32_t merge(ContactPair &contactPair);
	inline void refreshContactPoints(const Vector3 &pA,const Quat &qA,const Vector3 &pB,const Quat &qB);
	inline void removeContactPoint(int idx);
} __attribute__ ((aligned(128)));

static inline 
int findNearestContactPoint(ContactPoint *cp,int numContacts,const Vector3 &newCP)
{
	int nearestIdx = -1;
	for(int i=0;i<numContacts;i++) {
		Vector3 dist = cp[i].getLocalPointA()-newCP;
		float diff = lengthSqr(dist);
		if(diff < CONTACT_THRESHOLD_TANGENT) {
			nearestIdx = i;
		}
	}
	return nearestIdx;
}

static inline
int  sort4ContactPoints(ContactPoint *cp,const Vector3 &newCP,float newDistance)
{
	int maxPenetrationIndex = -1;
	float maxPenetration = newDistance;

	// 最も深い衝突点は排除対象からはずす
	for(int i=0;i<NUMCONTACTS_PER_BODIES;i++) {
		if(cp[i].distance < maxPenetration) {
			maxPenetrationIndex = i;
			maxPenetration = cp[i].distance;
		}
	}
	
	float res[4] = {0.0f};
	
	// 各点を除いたときの衝突点が作る面積のうち、最も大きくなるものを選択
	if(maxPenetrationIndex != 0) {
		Vector3 a0 = newCP-cp[1].getLocalPointA();
		Vector3 b0 = cp[3].getLocalPointA()-cp[2].getLocalPointA();
		res[0] = lengthSqr(cross(a0,b0));
	}
 
	if(maxPenetrationIndex != 1) {
		Vector3 a1 = newCP-cp[0].getLocalPointA();
		Vector3 b1 = cp[3].getLocalPointA()-cp[2].getLocalPointA();
		res[1] = lengthSqr(cross(a1,b1));
	}

	if(maxPenetrationIndex != 2) {
		Vector3 a2 = newCP-cp[0].getLocalPointA();
		Vector3 b2 = cp[3].getLocalPointA()-cp[1].getLocalPointA();
		res[2] = lengthSqr(cross(a2,b2));
	}

	if(maxPenetrationIndex != 3) {
		Vector3 a3 = newCP-cp[0].getLocalPointA();
		Vector3 b3 = cp[2].getLocalPointA()-cp[1].getLocalPointA();
		res[3] = lengthSqr(cross(a3,b3));
	}

	int maxIndex = 0;
	float maxVal = res[0];

	if (res[1] > maxVal) {
		maxIndex = 1;
		maxVal = res[1];
	}

	if (res[2] > maxVal) {
		maxIndex = 2;
		maxVal = res[2];
	}

	if (res[3] > maxVal) {
		maxIndex = 3;
		maxVal = res[3];
	}

	return maxIndex;
}

inline
uint32_t ContactPair::merge(ContactPair &contactPair)
{
	if(stateIndex[0] != contactPair.stateIndex[0])
		contactPair.exchange();

	uint32_t ret = 0;

	for(int i=0;i<contactPair.numContacts;i++) {
		int idx = findNearestContactPoint(contactPoints,numContacts,contactPair.contactPoints[i].getLocalPointA());

		if(idx >= 0) {
			// 同一点を発見、蓄積された情報を継続
			uint8_t d = contactPoints[idx].duration;
			//float accumN  = contactPoints[idx].constraints[0].accumImpulse;
			//float accumF1 = contactPoints[idx].constraints[1].accumImpulse;
			//float accumF2 = contactPoints[idx].constraints[2].accumImpulse;
			contactPoints[idx] = contactPair.contactPoints[i];
			//contactPoints[idx].constraints[0].accumImpulse = accumN ;
			//contactPoints[idx].constraints[1].accumImpulse = accumF1;
			//contactPoints[idx].constraints[2].accumImpulse = accumF2;
			contactPoints[idx].duration = d;
			ret |= 1; // 継続
			continue;
		}

		if(numContacts < NUMCONTACTS_PER_BODIES) {
			// 衝突点を新規追加
			contactPoints[numContacts++] = contactPair.contactPoints[i];
			ret |= 2; // 新規
		}
		else {
			// ソート
			int newIdx = sort4ContactPoints(contactPoints,contactPair.contactPoints[i].getLocalPointA(),contactPair.contactPoints[i].distance);
			
			// コンタクトポイント入れ替え
			contactPoints[newIdx] = contactPair.contactPoints[i];
			ret |= 4; // 入替
		}
	}

	return ret;
}

inline
void ContactPair::removeContactPoint(int idx)
{
	contactPoints[idx] = contactPoints[numContacts-1];
	numContacts--;
}

inline
void ContactPair::refreshContactPoints(const Vector3 &pA,const Quat &qA,const Vector3 &pB,const Quat &qB)
{
	// 衝突点の更新
	// 両衝突点間の距離が閾値（CONTACT_THRESHOLD）を超えたら消去
	for(int i=0;i<(int)numContacts;i++) {
		if(contactPoints[i].duration > 0) {
			Vector3 cpA = contactPoints[i].getWorldPointA(pA,qA);
			Vector3 cpB = contactPoints[i].getWorldPointB(pB,qB);

			// 貫通深度がプラスに転じたかどうかをチェック
			contactPoints[i].distance = dot(contactPoints[i].getNormal(),(cpA - cpB));
			if(contactPoints[i].distance > CONTACT_THRESHOLD_NORMAL) {
				removeContactPoint(i);
				i--;
				continue;
			}

			// 深度方向を除去して両点の距離をチェック
			cpA = cpA - contactPoints[i].distance * contactPoints[i].getNormal();
			float distanceAB = lengthSqr(cpA - cpB);
			if(distanceAB > CONTACT_THRESHOLD_TANGENT) {
				removeContactPoint(i);
				i--;
				continue;
			}
		}
		if(contactPoints[i].duration < 255) contactPoints[i].duration++;
	}
	duration++;
}

#endif /* __CONTACT_H__ */

