/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 OGL includes
//
// $File: //nextgendev/Framework_080/include/win32/FWWin32GLInclude.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WIN32GLINCLUDE_H__
#define __FW_WIN32GLINCLUDE_H__

// OpenGL & Cg includes
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <Cg/cgGL.h>

// OGL extensions supported by PSGL, but not by OGL 1.1
#include "FWGLExtensions.h"

// PSGL defines some functions differently, so map those to standard OpenGL
#define glClearDepthf	glClearDepth
#define gluPerspectivef	gluPerspective
#define gluOrtho2Df		gluOrtho2D
#define gluLookAtf		gluLookAt

// GL get proc function
#define FW_GETGLPROC	wglGetProcAddress

#endif//__FW_WIN32GLINCLUDE_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
