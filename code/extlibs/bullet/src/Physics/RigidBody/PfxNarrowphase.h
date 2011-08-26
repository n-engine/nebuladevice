#ifndef __PFX_NARROWPHASE_H__
#define __PFX_NARROWPHASE_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PerfCounter.h"
#include "Physics/Base/SortCommon.h"
#include "Physics/Base/PfxAllocator.h"
#include "Physics/Base/PfxStackAllocator.h"
#include "Physics/Base/PfxPtrArray.h"
#include "Physics/RigidBody/common/Contact.h"
#include "Physics/RigidBody/common/PfxContactPairInfo.h"

#ifdef __PPU__
	#include "Util/PELowLevelTask.h"
#endif

#ifdef __cplusplus
extern "C" { 
#endif

struct NarrowphaseConfig {
	PfxAllocator *allocator;
	PfxStackAllocator *stackAllocator;
	
	void* clientData;

	uint32_t numTasks;

	uint32_t bytesOfUserObject;
	uint32_t bytesOfUserContact;

#ifdef __PPU__
	PELowLevelTask *task;
#endif
};

void findContacts(PfxContactPairInfo *contactPairs,uint32_t numContactPairs,NarrowphaseConfig &config);

#ifdef __PPU__

void findContactsSPU(PfxContactPairInfo *contactPairs,uint32_t numContactPairs,NarrowphaseConfig &config);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __PFX_NARROWPHASE_H__ */
