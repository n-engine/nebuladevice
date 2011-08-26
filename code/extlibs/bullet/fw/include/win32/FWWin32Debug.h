/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 debugging functionality
//
// $File: //nextgendev/Framework_080/include/win32/FWWin32Debug.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WIN32DEBUG_H__
#define __FW_WIN32DEBUG_H__

#include <windows.h>
#include "FWDebugConsole.h"

// if debugging enabled
#ifdef _DEBUG

// preprocessor macros to turn the numeric value of __LINE__ into string form
#define _VAL(x)	#x
#define _STRIZE(x)	_VAL(x)

#ifdef _WIN32OVERRIDENEW

// enable memory allocation tracing
// _CRTDBG_MAP_ALLOC needs to be defined before #including crtdbg.h
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

// override new to allow file and line tracing
#define FWDEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new FWDEBUG_NEW

#else

#include <stdlib.h>
#include <crtdbg.h>

#endif//_WIN32OVERRIDENEW

// FWASSERT macro
#ifdef _ASSERTE
#define FWASSERT(x) _ASSERTE(x)
#else
#include <assert.h>
#define FWASSERT(x) assert(x)
#endif

// FWWARNING() macro
// takes a literal string and outputs a message including the file and line number the macro was used
// Note: a bug in MSVC means __LINE__ doesn't work if using Edit & Continue
// see article KB199057 in the MS Knowledge Base
#define FWWARNING(string)																					\
							do																				\
							{																				\
								OutputDebugString(__FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");		\
								FWDebugConsole::print(__FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");	\
							} while(0)

// else if debugging disabled
#else

#include <malloc.h>

// discard FWASSERT()
#define FWASSERT(x) ((void)0)

// discard FWWARNING()
#define FWWARNING(string) ((void)0)

#endif //_DEBUG

#define LITTLE_SHORT(x) (x)
#define LITTLE_INT(x)	(x)
#define BIG_SHORT(x)	(((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define BIG_INT(x)		(((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x & 0xff000000) >> 24))

#endif//__FW_WIN32DEBUG_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
