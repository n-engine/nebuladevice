/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux OGL Display Info class
//
// $File: //nextgendev/Framework_080/include/linux/FWLinuxGLDisplayInfo.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_LINUXGLDISPLAYINFO_H__
#define __FW_LINUXGLDISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// Linux OpenGL display information class.
// Contains the GLX context for the window.
// Derives from <c>FWDisplayInfo</c>.
class FWLinuxGLDisplayInfo : public FWDisplayInfo
{
public:
	// OpenGL context
	GLXContext	mGlContext;
};

#endif//__FW_LINUXGLDISPLAYINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
