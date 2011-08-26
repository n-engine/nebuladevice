/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef BULLET_PE_GATHER_SCATTER_SPURS_SUPPORT
#define BULLET_PE_GATHER_SCATTER_SPURS_SUPPORT

#include "BulletMultiThreaded/btThreadSupportInterface.h"



class BulletPEGatherScatterSpursSupport : public btThreadSupportInterface
{
	class BulletSpursTask*	m_bulletSpursTask;

	struct CellSpurs*	m_spursInstance;

	

public:

	BulletPEGatherScatterSpursSupport(CellSpurs* spursInstance,int numSpus,int numTasks);
	
	~BulletPEGatherScatterSpursSupport();
	
	void sendRequest(uint32_t uiCommand, ppu_address_t uiArgument0, uint32_t uiArgument1=0);
	
	void waitForResponse(unsigned int *puiArgument0, unsigned int *puiArgument1);
	
	void startSPU();
	
	void stopSPU();

	virtual void	setNumTasks(int numTasks);

	virtual int getNumTasks() const;

protected:
	
};

#endif //BULLET_PE_GATHER_SCATTER_SPURS_SUPPORT
