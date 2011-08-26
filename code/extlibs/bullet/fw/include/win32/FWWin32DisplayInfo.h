/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 OGL Display Info class
//
// $File: //nextgendev/Framework_080/include/win32/FWWin32DisplayInfo.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WIN32DISPLAYINFO_H__
#define __FW_WIN32DISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// Win32 display information class.
// Contains the Win32 OpenGL context.
// Derives from <c>FWDisplayInfo</c>.
class FWWin32DisplayInfo : public FWDisplayInfo
{
public:
	// OpenGL context
	HGLRC		mGlContext;

};

#endif//__FW_WIN32DISPLAYINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
