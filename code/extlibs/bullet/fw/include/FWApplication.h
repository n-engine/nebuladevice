/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Application class
//
// $File: //nextgendev/Framework_080/include/FWApplication.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_APPLICATION_H__
#define __FW_APPLICATION_H__

#include "FWDebug.h"
#include "FWDisplayInfo.h"
#include "FWStartupInfo.h"

// Abstract base class for applications within the sample framework.
// This class contains a number of virtual functions which can be
// overridden by derived classes in order to implement application functionality.
class FWApplication
{
public:
							FWApplication();
	virtual					~FWApplication();

	virtual bool			onInit(int argc, char **ppArgv);
	virtual void			onShutdown();
	virtual bool			onUpdate();
	
	//-----------------------------------------------------------------------------
	// Description: Overloadable render function
	// Parameters: 
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			onRender() = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Overloadable size function
	// Parameters:	dispInfo - Reference to display info class
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			onSize(const FWDisplayInfo &dispInfo) = 0;

	//-----------------------------------------------------------------------------
	// Description: Retrieves the static pointer for the application
	// Parameters: 
	// Returns: Pointer to the application
	// Notes: Used by the framework to drive the application
	//-----------------------------------------------------------------------------
	static inline FWApplication *getApplication()
	{
		FWASSERT(spApplication != NULL);
		return spApplication;
	}

	//-----------------------------------------------------------------------------
	// Description: Retrieves the display information for the application
	// Parameters: 
	// Returns: Reference to the display information for the application
	// Notes: Used by the framework to get the application's display settings
	//-----------------------------------------------------------------------------
	inline const FWDisplayInfo &getDisplayInfo() const
	{
		return mDispInfo;
	}

	//-----------------------------------------------------------------------------
	// Description: Retrieves the startup information for the application
	// Parameters: 
	// Returns: Reference to the startup information for the application
	// Notes: Used by the framework to get the application's startup settings
	//-----------------------------------------------------------------------------
	inline const FWStartupInfo &getStartupInfo() const
	{
		return mStartupInfo;
	}

protected:
	// Display info class
	FWDisplayInfo			mDispInfo;
	// Startup info class
	FWStartupInfo			mStartupInfo;

	// Static pointer to the application
	static FWApplication	*spApplication;
};

#endif//__FW_APPLICATION_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
