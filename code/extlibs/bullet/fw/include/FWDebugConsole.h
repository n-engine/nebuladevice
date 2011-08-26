/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug console
//
// $File: //nextgendev/Framework_080/include/FWDebugConsole.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_DEBUGCONSOLE_H__
#define __FW_DEBUGCONSOLE_H__

#include "FWDebugFont.h"
#include "FWDisplayInfo.h"
#include "FWTime.h"

#define FWDEBUGCONSOLE_DEFAULT_TIMEOUT		5.f
#define FWDEBUGCONSOLE_STRING_LENGTH		256
#define FWDEBUGCONSOLE_NUMBER_OF_STRINGS	128
#define FWDEBUGCONSOLE_DEFAULT_COLOR		1.f, 1.f, 1.f

// Debug console class. Uses the <c>FWDebugFont</c> class.
// The debug console is used to print status or debugging messages
// on top of the rendered scene. Messages output to the console will
// scroll if more messages are added, and a timeout value can be set
// to fade them over time.
class FWDebugConsole
{
public:
	static void		init();
	static void		shutdown();
	static void		update();
	static void		render();
	static void		print(const char *pText);
	static void		printf(const char *pText, ...);
	static void		resize(const FWDisplayInfo &dispInfo);

	//-----------------------------------------------------------------------------
	// Description: Set the text timeout value
	// Parameters:	secs - Time in seconds
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void setTimeout(float secs)
	{
		sTimeout = secs;
	}

private:
	class ConsoleString
	{
		char			mString[FWDEBUGCONSOLE_STRING_LENGTH];
		FWTimeVal		mTimeOfBirth;
		bool			mIsAlive;
		int				mHeight;
		int				mLength;
		friend class	FWDebugConsole;
	};

	static bool				sInit;
	static ConsoleString	sStrings[FWDEBUGCONSOLE_NUMBER_OF_STRINGS];
	static int				sCurrentString;
	static float			sTimeout;
	static int				sScrWidth;
	static int				sScrHeight;

};

#endif//__FW_DEBUGCONSOLE_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
