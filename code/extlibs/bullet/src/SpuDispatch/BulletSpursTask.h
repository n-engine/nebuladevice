/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef __BULLET_SPURS_TASK_H
#define __BULLET_SPURS_TASK_H

#include "Util/SpursTask.h"


class BulletSpursTask : public SpursTask
{
private:
	int mRBTasks;

	void* m_spursElf;

	
public:
	
	static const uint32_t	MAX_TASKS = 6;
	
	
	BulletSpursTask(int  numSPUs,int numTask,unsigned char* p_prios);

	void	setPrefixNames(const char* taskName,const char* taskSetName);


	virtual int initializeEvent();

	virtual int finalizeEvent();


	virtual~BulletSpursTask()
	{
	}
	

	void setTaskElf(void* elf)
	{
		m_spursElf = elf;
	}
	
protected:
	// ??????????????????
	CellSpursQueue	mQueuePpu2Spu[MAX_TASKS]		__attribute__((aligned(128)));
	CellSpursQueue	mQueueSpu2Ppu[MAX_TASKS]		__attribute__((aligned(128)));

	char	mQueuePpu2SpuBuf[MAX_TASKS][QUEUE_SIZE * QUEUE_DEPTH] __attribute__((aligned(128)));
	char	mQueueSpu2PpuBuf[MAX_TASKS][QUEUE_SIZE * QUEUE_DEPTH] __attribute__((aligned(128)));

	// ???
	CellSpursBarrier mBarrier;


public:
	int getNumTasks() {return mRBTasks;}
	void setNumTasks(uint32_t numTasks)
	{
		mRBTasks = numTasks;
		cellSpursBarrierInitialize(&mTaskset,&mBarrier,mRBTasks); // ???????
	}
	
	// ????
	int startTask(int i, uint32_t data1,uint32_t data2,uint32_t data3,uint32_t data4);
	int waitTask(int& i, uint32_t &data1, uint32_t &data2, uint32_t &data3, uint32_t &data4);


};

#endif //__BULLET_SPURS_TASK_H
