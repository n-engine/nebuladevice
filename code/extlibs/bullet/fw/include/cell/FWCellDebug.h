/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Cell debugging functionality
//
// $File: //nextgendev/Framework_080/include/cell/FWCellDebug.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_CELLDEBUG_H__
#define __FW_CELLDEBUG_H__

#include "FWDebugConsole.h"

// if debugging enabled
#ifdef _DEBUG

// preprocessor macros to turn the numeric value of __LINE__ into string form
#define _VAL(x)	#x
#define _STRIZE(x)	_VAL(x)

#include <assert.h>
#include <stdio.h>

// FWASSERT macro
#define FWASSERT(x)			assert((x))

// FWWARNING() macro
// takes a literal string and outputs a message including the file and line number the macro was used
#define FWWARNING(string)																					\
							do																				\
							{																				\
								printf(__FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");					\
								FWDebugConsole::print(__FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");	\
							} while(0)

#else

// discard FWASSERT()
#define FWASSERT(x)			((void)0)

// discard FWWARNING()
#define FWWARNING(string)	((void)0)

#endif//_DEBUG

#ifndef NULL
#define NULL	0
#endif//NULL

#define LITTLE_SHORT(x) (((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define LITTLE_INT(x)	(((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x & 0xff000000) >> 24))
#define BIG_SHORT(x)	(x)
#define BIG_INT(x)		(x)

#endif//__FW_CELLDEBUG_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
