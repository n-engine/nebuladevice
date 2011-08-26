/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SPURSTASK_H__
#define __SPURSTASK_H__

#include <cell/spurs.h>

class SpursTask
{
public:
	SpursTask(uint32_t numSPUs, uint8_t *p_prios = NULL)
	{
		strcpy(mSpursPrefix,"SpursTask");
		strcpy(mTasksetName,"SpursTask");

		mNumSPUs = numSPUs;

		if (p_prios == NULL) {
			for(int i=0;i<8;i++) {
				m_prios[i] = 1;
			}
		}
		else {
			for(int i=0;i<8;i++) {
				m_prios[i] = p_prios[i];
			}
		}
	}

	virtual~SpursTask()
	{
	}

protected:
	// constants & variables
	char mSpursPrefix[32];
	char mTasksetName[32];

	uint8_t					m_prios[8];
	uint32_t				mNumSPUs;
	static const uint32_t	QUEUE_SIZE = 16;
	static const uint32_t	QUEUE_DEPTH = 4;

	CellSpurs *mSpurs;
	CellSpursTaskset mTaskset	__attribute__((aligned(128)));

	virtual int initializeEvent() = 0;
	virtual int finalizeEvent() = 0;

public:
	virtual int initialize(CellSpurs *spurs);
	virtual int destroy();

	virtual int sendEvent(int i, uint32_t data1,uint32_t data2,uint32_t data3,uint32_t data4)
		{(void)i;(void)data1;(void)data2;(void)data3;(void)data4;return CELL_OK;}
	virtual int recvEvent(int i, uint32_t &data1, uint32_t &data2, uint32_t &data3, uint32_t &data4)
		{(void)i;(void)data1;(void)data2;(void)data3;(void)data4;return CELL_OK;}
};

#endif /* __SPURSTASK_H__ */
