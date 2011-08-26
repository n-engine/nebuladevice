/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OGL includes
//
// $File: //nextgendev/Framework_080/include/FWGLInclude.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLINCLUDE_H__
#define __FW_GLINCLUDE_H__

// stop some gl.h's including glext.h
#define GL_GLEXT_LEGACY

// OGL on win32
#if defined(_WIN32) && !defined(PSGL)
#include "win32/FWWin32GLInclude.h"
#endif//defined(_WIN32) && !defined(PSGL)

// OGL on linux
#if defined(__linux__) && !defined(PSGL)
#include "linux/FWLinuxGLInclude.h"
#endif//defined(__linux__) && !defined(PSGL)

// PSGL (Cell only at present)
#ifdef PSGL
#include "FWPSGLInclude.h"
#endif//PSGL

#endif//__FW_GLINCLUDE_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
