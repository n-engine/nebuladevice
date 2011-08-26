/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef BULLET_RAYCAST_SPURS_TASK1
#define BULLET_RAYCAST_SPURS_TASK1

#include "BulletMultiThreaded/btThreadSupportInterface.h"



class BulletRaycastSpursSupport : public btThreadSupportInterface
{
	class BulletSpursTask*	m_bulletRaycastTask;

	struct CellSpurs*	m_spursInstance;

	

public:

	BulletRaycastSpursSupport(CellSpurs* spursInstance,int numSpus,int numTasks);
	
	~BulletRaycastSpursSupport();
	
	void sendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1=0);
	
	void waitForResponse(unsigned int *puiArgument0, unsigned int *puiArgument1);
	
	void startSPU();
	
	void stopSPU();

	virtual void	setNumTasks(int numTasks);

	virtual int		getNumTasks() const;
protected:
	
};

#endif //BULLET_RAYCAST_SPURS_TASK1
