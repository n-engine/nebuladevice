/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Cell GCM Window class
//
// $File: //nextgendev/Framework_050/include/cell/FWCellGCMWindow.h $
// $Author: asidwell $
// $Date: 2005/09/28 $
// $Revision: #3 $
//
// Copyright (C) 2005 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_CELLGCMWINDOW_H__
#define __FW_CELLGCMWINDOW_H__

#include <cell/gcm.h>
#include <sys/event.h>

#include "FWWindow.h"
#include "FWStartupInfo.h"
#include "FWGCMConfiguration.h"

// Cell GCM specific graphics encapsulation class.
// Derives from the FWWindow class.
class FWCellGCMWindow : public FWWindow
{
public:
	FWCellGCMWindow(int argc, char **ppArgv,
					const FWDisplayInfo &dispInfo,
					const FWStartupInfo &startupInfo,
					const FWGCMConfiguration &gcmConfig);
	virtual	~FWCellGCMWindow();

	bool update();
	void destroy();

	virtual void *getWindowSystemContext();

public:
	void resetRenderTarget() {
		setRenderTarget(mFrameIndex);
	}

	static FWCellGCMWindow* getInstance() {
		return spCellGCMWindow;
	}

	// getters for state command buffer
	uint32_t* getStateCmdAddress() {
		return mStateCmdAddress;
	}

	uint32_t getStateCmdOffset() {
		return mStateCmdOffset;
	}

	uint32_t getStateCmdSize() {
		return mStateCmdSize;
	}

	// getters for framebuffer
	uint32_t getFrameIndex() {
		return mFrameIndex;
	}

	void* getFrameAddress(uint32_t index) {
		return mFrameAddress[index];
	}

	uint32_t getFrameOffset(uint32_t index) {
		return mFrameOffset[index];
	}

	uint32_t getFramePitch(uint32_t index) {
		return mFramePitch[index];
	}

	uint32_t getFrameSize() {
		return mFrameSize;
	}

	uint32_t getDepthSize() {
		return mDepthSize;
	}

	static const uint32_t sTiledRegionBoundary = 0x10000; // 64KB
	static const uint32_t sLabelId = 64;

	virtual FWDisplayInfo&		getDisplayInfo();

private:
	void				createDeviceAndSurfaces();
	virtual void			setRenderingContext();
	virtual void			clearRenderingContext();
	virtual void			flip();

	static void onFlip(const uint32_t arg);


	void getCpuGpuSync(void);
	void setRenderTarget(const uint32_t Index);
	void initFlipEvent(void);

	// display info
	FWDisplayInfo mDispInfo;

	FWGCMConfiguration mConfig;

	// window instance
	static FWCellGCMWindow *spCellGCMWindow;

	uint32_t mFrameIndex;

	void *mFrameAddress[3];
	uint32_t mFrameOffset[3];
	uint32_t mFramePitch[3];

	uint32_t *mLabel;

	//void* mDefaultCB;
	uint32_t mDefaultCB;
	uint32_t mFrameSize;
	uint32_t mDepthSize;

	// state command buffer
	uint32_t *mStateCmdAddress;
	uint32_t mStateCmdOffset;
	uint32_t mStateCmdSize;

	int mFlipEventId;
	sys_event_queue_t mFlipEventQueue;
	static sys_event_port_t  sFlipEventPort;


};


inline void *FWCellGCMWindow::getWindowSystemContext()
{
	return NULL;
}

#endif//__FW_CELLGCMWINDOW_H__
