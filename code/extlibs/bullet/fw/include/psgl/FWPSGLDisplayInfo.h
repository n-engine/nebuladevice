/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// PSGL Display Info class
//
// $File: //nextgendev/Framework_080/include/FWPSGLDisplayInfo.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_PSGLDISPLAYINFO_H__
#define __FW_PSGLDISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// PSGL display information class.
// Contains the PSGL context.
// Derives from <c>FWDisplayInfo</c>.
class FWPSGLDisplayInfo : public FWDisplayInfo
{
public:
	// PSGL context
	PSGLcontext	*mGlContext;
};

#endif//__FW_PSGLDISPLAYINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
