/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/
#ifndef ERRORSTREAM_H
#define ERRORSTREAM_H

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "DebugPrint.h"

class ErrorStream : public NxUserOutputStream
	{
	public:
	void reportError(NxErrorCode e, const char* message, const char* file, int line)
		{
		FWDPRINT("%s (%d) :", file, line);
		switch (e)
			{
			case NXE_INVALID_PARAMETER:
				FWDPRINT( "invalid parameter");
				break;
			case NXE_INVALID_OPERATION:
				FWDPRINT( "invalid operation");
				break;
			case NXE_OUT_OF_MEMORY:
				FWDPRINT( "out of memory");
				break;
			case NXE_DB_INFO:
				FWDPRINT( "info");
				break;
			case NXE_DB_WARNING:
				FWDPRINT( "warning");
				break;
			default:
				FWDPRINT("unknown error");
			}

		FWDPRINT(" : %s\n", message);
		}

	NxAssertResponse reportAssertViolation(const char* message, const char* file, int line)
		{
		FWDPRINT("access violation : %s (%s line %d)\n", message, file, line);
#ifdef WIN32
		switch (MessageBox(0, message, "AssertViolation, see console for details.", MB_ABORTRETRYIGNORE))
			{
			case IDRETRY:
				return NX_AR_CONTINUE;
			case IDIGNORE:
				return NX_AR_IGNORE;
			case IDABORT:
			default:
				return NX_AR_BREAKPOINT;
			}
#elif LINUX
		assert(0);
#elif _XBOX
		return NX_AR_BREAKPOINT;
#endif
		}

	void print(const char* message)
		{
		FWDPRINT(message);
		}
	};



#endif
