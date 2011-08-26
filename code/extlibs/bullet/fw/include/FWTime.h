/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Time class
//
// $File: //nextgendev/Framework_080/include/FWTime.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------
#ifndef __FW_TIME_H__
#define __FW_TIME_H__

#ifdef _WIN32
#include "win32/FWWin32Time.h"
#endif//_MSC_VER

#ifdef __linux__
#include "linux/FWLinuxTime.h"
#endif//__linux__

#ifdef __CELLOS_LV2__
#include "cell/FWCellTime.h"
#endif//__CELLOS_LV2__

#endif//__FW_TIME_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
