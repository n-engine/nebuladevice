/*   SCE CONFIDENTIAL                                       */
/*   $PSLibId$ */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef __FW_STARTUPINFO_H__
#define __FW_STARTUPINFO_H__

#ifdef __CELLOS_LV2__
#include <sys/paths.h>
#endif

#include <string.h>

#define FWSTARTUPINFO_DEFAULT_NUMRAWSPUS	3
#define FWSTARTUPINFO_DEFAULT_USEDEBUGCONSOLE	true
#define FWSTARTUPINFO_DEFAULT_WINDOWTITLE	"Sample Framework"
#define FWSTARTUPINFO_DEFAULT_ARGUMENTSFILENAME	"fwArgs.txt"

// Startup information class.
// Contains initialization settings that can be changed from within
// the application's constructor.
class FWStartupInfo
{
public:
	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters: 
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline FWStartupInfo() :
	mNumRawSPUs(FWSTARTUPINFO_DEFAULT_NUMRAWSPUS),
	mUseDebugConsole(FWSTARTUPINFO_DEFAULT_USEDEBUGCONSOLE)
	{
		strcpy(mWindowTitle, FWSTARTUPINFO_DEFAULT_WINDOWTITLE);
		strcpy(mArgumentsFilename, FWSTARTUPINFO_DEFAULT_ARGUMENTSFILENAME);
	}

	//-----------------------------------------------------------------------------
	// Description: Destructor
	// Parameters: 
	// Returns:
	// Notes: 
	//-----------------------------------------------------------------------------
	inline ~FWStartupInfo()
	{
	}

	// Number of SPUs to allocate as Raw SPUs
	int	mNumRawSPUs;
	// Whether to use debug console
	bool	mUseDebugConsole;
	// Title on platforms with window managers
	char	mWindowTitle[256];
	// Arguments file to parse, if any
	char	mArgumentsFilename[256];

};

#endif//__FW_STARTUPINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
