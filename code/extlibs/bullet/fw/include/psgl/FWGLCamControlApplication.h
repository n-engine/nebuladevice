/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GL & Controlled Camera Application class
//
// $File: //nextgendev/Framework_080/include/FWGLCamControlApplication.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLCAMCONTROLAPPLICATION_H__
#define __FW_GLCAMCONTROLAPPLICATION_H__

// camera default values

// turn rate
#define FWGLCAMAPP_DEFAULT_TURN_RATE	500.f
// move rate
#define FWGLCAMAPP_DEFAULT_MOVE_RATE	500.f

#include "FWGLCamApplication.h"
#include "FWInput.h"
#include "FWTime.h"

// OpenGL, camera and input control application class.
// Derives from <c>FWGLCamApplication</c>. Sets up controller inputs
// and uses them to manipulate the camera.
class FWGLCamControlApplication : public FWGLCamApplication
{
public:
					FWGLCamControlApplication();
	virtual			~FWGLCamControlApplication();

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

#endif//__FW_GLCAMCONTROLAPPLICATION_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
