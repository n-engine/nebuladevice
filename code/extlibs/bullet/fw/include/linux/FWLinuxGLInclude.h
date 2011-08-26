/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Linux OGL includes
//
// $File: //nextgendev/Framework_080/include/linux/FWLinuxGLInclude.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_LINUXGLINCLUDE_H__
#define __FW_LINUXGLINCLUDE_H__

// stop some glx.h's including glxext.h
#define GLX_GLXEXT_LEGACY

// OpenGL & Cg includes
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <Cg/cgGL.h>

// OGL extensions supported by PSGL, but not by OGL 1.1
#include "psgl/FWGLExtensions.h"

// PSGL defines some functions differently, so map those to standard OpenGL
#define glClearDepthf	glClearDepth
#define gluPerspectivef gluPerspective
#define gluOrtho2Df		gluOrtho2D
#define gluLookAtf		gluLookAt

// GL get proc function
#define FW_GETGLPROC(x)	glXGetProcAddressARB((const GLubyte *)x)

#endif//__FW_LINUXGLINCLUDE_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
