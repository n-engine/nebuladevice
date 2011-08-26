/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef SPU_PE_GATHER_SCATTER_TASK_H
#define SPU_PE_GATHER_SCATTER_TASK_H

#include "BulletMultiThreaded/PlatformDefinitions.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"

#include "LinearMath/btAlignedAllocator.h"


//just add your commands here, try to keep them globally unique for debugging purposes

#define CMD_PE_GATHER_BODIES 15
#define CMD_PE_GATHER_MANIFOLDS 16
#define CMD_PE_SCATTER_VELOCITIES 17
#define CMD_PE_SCATTER_ACCUMULATED_IMPULSES 18
#define CMD_SAMPLE_INTEGRATE_BODIES 19
#define CMD_SAMPLE_PREDICT_MOTION_BODIES 20


ATTRIBUTE_ALIGNED16(struct) SpuPEGatherScatterTaskDesc
{
	BT_DECLARE_ALIGNED_ALLOCATOR();

	uint32_t m_command;
	uint32_t m_taskId;

	// for scatter / gather of bodies and manifolds
	uint32_t m_bulletArrayAddress;
	uint32_t m_peArrayAddress;
	uint32_t m_peArray2Address;
	uint32_t m_startIndex;
	uint32_t m_numElements;
};


void	processPEGatherScatterTask(void* userPtr, void* lsMemory);
void*	createPEGatherScatterLocalStoreMemory();


#endif //SPU_PE_GATHER_SCATTER_TASK_H

