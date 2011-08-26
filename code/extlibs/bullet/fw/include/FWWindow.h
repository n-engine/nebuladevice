/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Generic Window class
//
// $File: //nextgendev/Framework_080/include/FWWindow.h $
// $Author: asidwell $
// $Date: 2006/02/03 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WINDOW_H__
#define __FW_WINDOW_H__

#include "FWDisplayInfo.h"
#include "FWStartupInfo.h"

// Generic graphics window encapsulation abstract base class.
// Base class for platform specific window classes.
class FWWindow
{
public:
							FWWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual 				~FWWindow();

	void					render();

	//-----------------------------------------------------------------------------
	// Description: Obtain pointer to window object
	// Parameters: 
	// Returns: Pointer to window object
	// Notes:
	//-----------------------------------------------------------------------------
	static inline FWWindow *getWindow()
	{
		return spWindow;
	}

	//-----------------------------------------------------------------------------
	// Description: Returns the window system handle
	// Parameters: 
	// Returns: The window handle
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			*getWindowSystemContext() = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Returns reference to display info class
	// Parameters: 
	// Returns: Reference to display info class
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual FWDisplayInfo	&getDisplayInfo() = 0;

protected:
	void					init();
	void					update();
	void					destroy();
	void					parseArgumentsFile(const char *pArgumentsFile);
	void					resize(int width, int height);
	
	//-----------------------------------------------------------------------------
	// Description: Sets rendering context
	// Parameters: 
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			setRenderingContext() = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Clears rendering context
	// Parameters: 
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			clearRenderingContext() = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Does buffer flip
	// Parameters: 
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void			flip() = 0;

	// Copied from startup info class, whether to use the debug console
	bool					mUseDebugConsole;
	// Result of calling <c>FWApplication::onInit()</c>
	bool					mInit;
	// Result of calling <c>FWApplication::onUpdate()</c>
	bool					mUpdate;
	// Number of command line arguments
	int						mArgc;
	// Array of command line arguments
	char					**mppArgv;	
	// Arguments file pointer
	char					*mpArgFile;
	// Pointer to the window object
	static FWWindow			*spWindow;
};

#endif//__FW_WINDOW_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
