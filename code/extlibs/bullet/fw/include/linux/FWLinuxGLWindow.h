/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux Window class
//
// $File: //nextgendev/Framework_080/include/linux/FWLinuxGLWindow.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_LINUXGLWINDOW_H__
#define __FW_LINUXGLWINDOW_H__

#include "FWWindow.h"
#include "FWGLInclude.h"
#include "FWLinuxGLDisplayInfo.h"
#include "FWStartupInfo.h"
#include "FWLinuxXInfo.h"

// Linux OpenGL specific graphics window encapsulation class.
// Derives from <c>FWWindow</c>.
class FWLinuxGLWindow : public FWWindow
{
public:
							FWLinuxGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual 				~FWLinuxGLWindow();

	bool					update();
	void					destroy();

	virtual void			*getWindowSystemContext();

private:
	virtual void			setRenderingContext();
	virtual void			clearRenderingContext();
	virtual void			flip();
	virtual FWDisplayInfo&	getDisplayInfo();

	bool					xUpdate();

	// X Info
	FWLinuxXInfo			mXInfo;
	// display info
	FWLinuxGLDisplayInfo	mDispInfo;

};

#endif//__FW_LINUXGLWINDOW_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
