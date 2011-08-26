#ifndef __PFX_BROADPHASE_H__
#define __PFX_BROADPHASE_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PerfCounter.h"
#include "Physics/Base/SortCommon.h"
#include "Physics/Base/PfxAllocator.h"
#include "Physics/Base/PfxStackAllocator.h"
#include "Physics/Base/PfxPtrArray.h"
#include "Physics/RigidBody/common/TrbStateVec.h"
#include "Physics/RigidBody/common/WorldVolume.h"

#ifdef __PPU__
	#include "Util/PELowLevelTask.h"
#endif

#ifdef __cplusplus
extern "C" { 
#endif

typedef void(*pfxBroadphaseCallback)(void* clientData, void* userObject0,void* userObject1,void* userPointer);

struct BroadphaseConfig {
	bool enableRemovePairs;
	WorldVolume worldVolume;
	uint32_t maxCachedPairs;
	PfxAllocator *allocator;
	PfxStackAllocator *stackAllocator;

	void *clientData;
	pfxBroadphaseCallback beginCallback;
	pfxBroadphaseCallback endCallback;

	uint32_t numTasks;

#ifdef __PPU__
	PELowLevelTask *task;
#endif
};

void findPairs(
	PfxPtrArray<TrbState> &proxyArray,
	PfxBroadphasePair *&pairs,uint32_t &numPairs,
	BroadphaseConfig &config);

#ifdef __PPU__

void findPairsSPU(
	PfxPtrArray<TrbState> &proxyArray,
	PfxBroadphasePair *&pairs,uint32_t &numPairs,
	BroadphaseConfig &config);

#endif

struct PfxBroadphase {
	BroadphaseConfig config;

	PfxPtrArray<TrbState> bodyArray;
	PfxBroadphasePair *pairs;
	uint32_t numPairs;
	bool useSPU;
};

#ifdef __cplusplus
}
#endif

#endif /* __PFX_BROADPHASE_H__ */
