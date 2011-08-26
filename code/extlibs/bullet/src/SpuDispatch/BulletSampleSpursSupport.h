/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef BULLET_SAMPLE_SPURS_TASK1
#define BULLET_SAMPLE_SPURS_TASK1

#include "BulletMultiThreaded/btThreadSupportInterface.h"



class BulletSampleSpursSupport : public btThreadSupportInterface
{
	class BulletSpursTask*	m_bulletSampleTask;

	struct CellSpurs*	m_spursInstance;

	

public:

	BulletSampleSpursSupport(CellSpurs* spursInstance,int numSpus,int numTasks);
	
	~BulletSampleSpursSupport();
	
	void sendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1=0);
	
	void waitForResponse(unsigned int *puiArgument0, unsigned int *puiArgument1);
	
	void startSPU();
	
	void stopSPU();

	virtual void	setNumTasks(int numTasks);

protected:
	
};

#endif //BULLET_SAMPLE_SPURS_TASK1
