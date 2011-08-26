/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Null Application class
//
// $File: //nextgendev/Framework_080/include/FWNullApplication.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_NULLAPPLICATION_H__
#define __FW_NULLAPPLICATION_H__

#include "FWApplication.h"
#include "FWNullDebugFontRenderer.h"

// Null application base class.
// Derives from <c>FWApplication</c>.
class FWNullApplication : public FWApplication
{
public:
							FWNullApplication();
	virtual					~FWNullApplication();

	virtual bool			onInit(int argc, char **ppArgv);
	virtual void			onShutdown();
	virtual bool			onUpdate();
	virtual void			onRender();
	virtual void			onSize(const FWDisplayInfo &dispInfo);

private:
	// null font renderer instance
	FWNullDebugFontRenderer	mFontRenderer;

};

#endif//__FW_NULLAPPLICATION_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
