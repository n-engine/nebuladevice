/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2008 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
///btLowLevelBroadphase implementation
#ifndef BT_LOW_LEVEL_BROADPHASE_H
#define BT_LOW_LEVEL_BROADPHASE_H

#include "BulletCollision/BroadphaseCollision/btDbvt.h"
#include "BulletCollision/BroadphaseCollision/btOverlappingPairCache.h"
#include "Physics/LowLevelPhysics.h"
struct btLowLevelBroadphase;

struct	btMyClientData
{
	btDispatcher* m_dispatcher;
	btLowLevelBroadphase*	m_bp;
};

///btLowLevelBroadphase is a binding between Open Physics low-level broadphase and Bullet, through the btBroadphaseInterface
struct	btLowLevelBroadphase : btBroadphaseInterface
{
	plBroadphaseHandle	m_llBroadphaseHandle;
	
	btOverlappingPairCache*	m_paircache;				// Pair cache
	bool					m_releasepaircache;			// Release pair cache on delete
	int						m_guidGenerator;
	btVector3				m_broadphaseAabbMin;
	btVector3				m_broadphaseAabbMax;

	btMyClientData			m_clientData;

	/* Methods		*/ 
	btLowLevelBroadphase(btOverlappingPairCache* paircache,class PfxDefaultAllocator* allocator,class PfxStackAllocator* stackPool,class CellSpurs* spursInstance);
	~btLowLevelBroadphase();

	/* btBroadphaseInterface Implementation	*/ 
	btBroadphaseProxy*				createProxy(const btVector3& aabbMin,const btVector3& aabbMax,int shapeType,void* userPtr,short int collisionFilterGroup,short int collisionFilterMask,btDispatcher* dispatcher,void* multiSapProxy);
	void							destroyProxy(btBroadphaseProxy* proxy,btDispatcher* dispatcher);
	void							setAabb(btBroadphaseProxy* proxy,const btVector3& aabbMin,const btVector3& aabbMax,btDispatcher* dispatcher);
	virtual void	rayTest(const btVector3& rayFrom,const btVector3& rayTo, btBroadphaseRayCallback& rayCallback, const btVector3& aabbMin=btVector3(0,0,0), const btVector3& aabbMax = btVector3(0,0,0));

	virtual void	getAabb(btBroadphaseProxy* proxy,btVector3& aabbMin, btVector3& aabbMax ) const;
	void							calculateOverlappingPairs(btDispatcher* dispatcher);
	btOverlappingPairCache*			getOverlappingPairCache();
	const btOverlappingPairCache*	getOverlappingPairCache() const;
	void							getBroadphaseAabb(btVector3& aabbMin,btVector3& aabbMax) const;
	virtual void	printStats();

	virtual void	setNumTasks(int numTasks);
	
	virtual void	setUseSpu(bool useSpu);
};

#endif
