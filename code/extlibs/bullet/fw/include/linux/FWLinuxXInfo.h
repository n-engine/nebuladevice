/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux X Info class
//
// $File: //nextgendev/Framework_080/include/linux/FWLinuxXInfo.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_LINUXXINFO_H__
#define __FW_LINUXXINFO_H__

#include <X11/X.h>

// X information
class FWLinuxXInfo
{
public:
	// X Display
	Display		*mpDisplay;
	// Window handle
	Window		mWindow;
	// Window position
	int			mXPos, mYPos;
	// Window dimensions
	int			mWidth, mHeight;
	// Window moved?
	bool		mWindowMoved;
	// Window in focus?
	bool		mWindowFocus;
};

#endif//__FW_LINUXXINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
