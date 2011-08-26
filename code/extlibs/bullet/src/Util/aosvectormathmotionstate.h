/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef AOS_VECTORMATH_MOTIONSTATE_H
#define AOS_VECTORMATH_MOTIONSTATE_H


#include "LinearMath/btMotionState.h"

///AosVectormathMotionState synchronizes Bullet <-> vectormath transforms
class	AosVectormathMotionState : public btMotionState
{
	public:
	
		Vectormath::Aos::Vector3	m_worldPosition;
		Vectormath::Aos::Matrix3	m_worldOrientation;
		Vectormath::Aos::Quat		m_worldOrientationQ;

		AosVectormathMotionState()
		{
			m_worldPosition = Vectormath::Aos::Vector3(0.f,0.f,0.f);
			m_worldOrientation = Vectormath::Aos::Matrix3::identity();
			m_worldOrientationQ = Vectormath::Aos::Quat::identity();
		}
		virtual void	getWorldTransform(btTransform& worldTrans) const
		{
			btVector3 worldPos;
			worldPos.setValue(m_worldPosition.getX(),m_worldPosition.getY(), m_worldPosition.getZ());

			///convert to quat, probably very slow, check inline Quat::Quat( const Matrix3 & tfrm )
			Vectormath::Aos::Quat quat(m_worldOrientationQ);
			btQuaternion orn;
			orn.setValue(quat.getX(),quat.getY(),quat.getZ(),quat.getW());

			worldTrans.setOrigin(worldPos);
			worldTrans.setBasis(btMatrix3x3(orn));
		}
		
		virtual void	setWorldTransform(const btTransform& worldTransform)
		{
			m_worldPosition.setX(worldTransform.getOrigin().getX());
			m_worldPosition.setY(worldTransform.getOrigin().getY());
			m_worldPosition.setZ(worldTransform.getOrigin().getZ());

			btQuaternion orn;
			worldTransform.getBasis().getRotation(orn);

			Vectormath::Aos::Quat quat;
			quat.setX(orn.getX());
			quat.setY(orn.getY());
			quat.setZ(orn.getZ());
			quat.setW(orn.getW());
			m_worldOrientationQ = quat;
			m_worldOrientation = Vectormath::Aos::Matrix3(quat);
		}
		
		
};

#endif //AOS_VECTORMATH_MOTIONSTATE_H
