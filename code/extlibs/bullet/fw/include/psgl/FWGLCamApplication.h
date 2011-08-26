/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OpenGL and camera application class
//
// $File: //nextgendev/Framework_080/include/FWGLCamApplication.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLCAMAPPLICATION_H__
#define __FW_GLCAMAPPLICATION_H__

#include "FWGLApplication.h"
#include "FWCamera.h"

// OpenGL and camera application class.
// Derives from <c>FWGLApplication</c>. This class contains an <c>FWCamera</c> object,
// but does not implement any input. If a default input implementation is required,
// the application should derive from <c>FWGLCamControlApplication</c> instead.
class FWGLCamApplication : public FWGLApplication
{
public:
					FWGLCamApplication();
	virtual			~FWGLCamApplication();

	virtual bool	onInit(int argc, char **ppArgv);
	virtual void	onShutdown();
	virtual bool	onUpdate();
	virtual void	onRender();
	virtual void	onSize(const FWDisplayInfo &dispInfo);

protected:
	// Camera object
	FWCamera				mCamera;
};

#endif//__FW_GLCAMAPPLICATION_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
