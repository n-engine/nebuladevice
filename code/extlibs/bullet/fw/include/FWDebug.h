/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debugging functionality
//
// $File: //nextgendev/Framework_080/include/FWDebug.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_DEBUG_H__
#define __FW_DEBUG_H__

#ifdef _WIN32
#include "win32/FWWin32Debug.h"
#endif

#ifdef __linux__
#include "linux/FWLinuxDebug.h"
#endif//__linux__

#ifdef __CELLOS_LV2__
#include "cell/FWCellDebug.h"
#endif//__CELLOS_LV2__

#endif//__FW_DEBUG_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
