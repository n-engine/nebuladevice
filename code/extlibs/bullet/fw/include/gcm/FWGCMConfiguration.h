/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#ifndef __FW_GCMCONFIGURATION_H__
#define __FW_GCMCONFIGURATION_H__

#include <cell/gcm.h>

class FWGCMConfiguration
{
public:
	FWGCMConfiguration() :
		mDefaultCBSize(512<<10), mColorFormat(CELL_GCM_SURFACE_A8R8G8B8),
		mDefaultStateCmdSize(512<<10)
		{}
	virtual ~FWGCMConfiguration() {}

	uint32_t mDefaultCBSize;
	uint32_t mColorFormat;
	uint32_t mDefaultStateCmdSize;
};

#endif // __FW_GCMCONFIGURATION_H__
