/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GCM & Controlled Camera Application class
//
// $File: //nextgendev/Framework_050/include/FWGLCamControlApplication.h $
// $Author: asidwell $
// $Date: 2005/09/23 $
// $Revision: #2 $
//
// Copyright (C) 2005 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GCMCAMCONTROLAPPLICATION_H__
#define __FW_GCMCAMCONTROLAPPLICATION_H__

// camera default values

// turn rate
#define FWGCMCAMAPP_DEFAULT_TURN_RATE	500.f
// move rate
#define FWGCMCAMAPP_DEFAULT_MOVE_RATE	500.f

#include "FWGCMCamApplication.h"
#include "FWInput.h"
#include "FWTime.h"

// GCM, camera and input control application class.
// Derives from FWGCMCamApplication. Sets up controller inputs
// and uses them to manipulate the camera.
class FWGCMCamControlApplication : public FWGCMCamApplication
{
public:
					FWGCMCamControlApplication();
	virtual			~FWGCMCamControlApplication();

	virtual bool	onInit(int argc, char **ppArgv);
	virtual void	onShutdown();
	virtual bool	onUpdate();
	virtual void	onRender();
	virtual void	onSize(const FWDisplayInfo &dispInfo);

protected:
	void			setInputsFlyThru(float deltaTime);
	void			setInputsLookAt(float deltaTime);

	// X-axis #0 input
	FWInputFilter	*mpInputX0;
	// Y-axis #0 input
	FWInputFilter	*mpInputY0;
	// X-axis #1 inpu
	FWInputFilter	*mpInputX1;
	// Y-axis #1 input
	FWInputFilter	*mpInputY1;
	// Time last updated
	FWTimeVal		mLastUpdate;
	// Turn rate
	float			mTurnRate;
	// Move rate
	float			mMoveRate;
};

#endif//__FW_GCMCAMCONTROLAPPLICATION_H__
