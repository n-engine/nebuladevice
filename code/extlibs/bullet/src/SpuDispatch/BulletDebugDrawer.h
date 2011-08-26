/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef BULLET_DEBUG_DRAWER_H
#define BULLET_DEBUG_DRAWER_H

#include "LinearMath/btIDebugDraw.h"

class	BulletDebugDrawer : public btIDebugDraw
{
	int		m_debugMode;

	public:

	BulletDebugDrawer()
		:m_debugMode(0)
	{
	}

	virtual ~BulletDebugDrawer();

	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	
	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

	virtual void	reportErrorWarning(const char* warningString);

	virtual void	draw3dText(const btVector3& location,const char* textString);
	
	virtual void	setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	}
	

	virtual int		getDebugMode() const
	{
		return m_debugMode;
	}
};

#endif// BULLET_DEBUG_DRAWER_H
