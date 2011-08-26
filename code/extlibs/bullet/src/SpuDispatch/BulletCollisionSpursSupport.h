/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef BULLET_COLLISION_SPURS_TASK1
#define BULLET_COLLISION_SPURS_TASK1

#include "BulletMultiThreaded/btThreadSupportInterface.h"

class BulletCollisionSpursSupport : public btThreadSupportInterface
{
	class BulletSpursTask*	m_bulletCollisionTaskMulti;

	struct CellSpurs*	m_spursInstance;

public:

	BulletCollisionSpursSupport(CellSpurs* spursInstance,int numSpus,int numTasks);
	
	~BulletCollisionSpursSupport();
	
	void sendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1=0);
	
	void waitForResponse(unsigned int *puiArgument0, unsigned int *puiArgument1);
	
	void startSPU();
	
	void stopSPU();

	virtual void	setNumTasks(int numTasks);

	virtual int		getNumTasks() const;

protected:
	
};

#endif //BULLET_COLLISION_SPURS_TASK
