/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Null Window class
//
// $File: //nextgendev/Framework_080/include/FWNullWindow.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_NULLWINDOW_H__
#define __FW_NULLWINDOW_H__

#include "FWWindow.h"

// Null graphics window encapsulation class.
// Derives from <c>FWWindow</c>.
class FWNullWindow : public FWWindow
{
public:
						FWNullWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
						~FWNullWindow();

	bool				update();
	void				destroy();

	void				*getWindowSystemContext();

private:
	void				setRenderingContext();
	void				clearRenderingContext();
	void				flip();
	FWDisplayInfo&		getDisplayInfo();

	// Generic display info
	FWDisplayInfo		mDispInfo;

};

#endif//__FW_NULLWINDOW_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
