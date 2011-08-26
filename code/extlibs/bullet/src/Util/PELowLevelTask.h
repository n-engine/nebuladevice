/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PE_LOWLEVEL_TASK_H__
#define __PE_LOWLEVEL_TASK_H__

#include "Util/SpursTask.h"

class PELowLevelTask : public SpursTask
{
private:
	uint32_t mRCTasks;
	void *mSpursElf;

	static const uint32_t MAX_TASKS = 6;

public:
	PELowLevelTask(uint32_t numSPUs, uint32_t numTask,uint8_t *p_prios = NULL)
		 : SpursTask(numSPUs,p_prios)
	{
		mRCTasks = numTask;
		strcpy(mSpursPrefix,"PELowLevelTask");
		strcpy(mTasksetName,"PELowLevelTaskset");
	}

	virtual~PELowLevelTask()
	{
	}
	
	void setTask(void *elf) {mSpursElf = elf;}
	
protected:
	// シミュレーション用パイプラインキュー
	CellSpursQueue	mQueuePpu2Spu[MAX_TASKS]		__attribute__((aligned(128)));
	CellSpursQueue	mQueueSpu2Ppu[MAX_TASKS]		__attribute__((aligned(128)));

	char	mQueuePpu2RayBuf[MAX_TASKS][QUEUE_SIZE * QUEUE_DEPTH] __attribute__((aligned(128)));
	char	mQueueRay2PpuBuf[MAX_TASKS][QUEUE_SIZE * QUEUE_DEPTH] __attribute__((aligned(128)));

	CellSpursBarrier mBarrier;

	int startTask(int i);
	int initializeEvent();
	int finalizeEvent();

public:

	int getNumSPU() {return mNumSPUs;}

	int getNumTasks() {return mRCTasks;}
	void setNumTasks(uint32_t numTasks)
	{
		mRCTasks = numTasks;
		cellSpursBarrierInitialize(&mTaskset,&mBarrier,mRCTasks); // バリア再初期化
	}

	int sendEvent(int i, uint32_t data1,uint32_t data2,uint32_t data3,uint32_t data4);
	int recvEvent(int i, uint32_t &data1, uint32_t &data2, uint32_t &data3, uint32_t &data4);
};

#endif /* __PE_LOWLEVEL_TASK_H__ */
