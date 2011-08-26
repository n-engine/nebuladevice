#ifndef __DEBUGPRINT_H__
#define __DEBUGPRINT_H__

#define BENCHMARK 1
#if defined(DEBUG) || defined(BENCHMARK)
	#ifdef __SPU__
		#include <spu_printf.h>
		#define FWDPRINT(...) spu_printf(__VA_ARGS__)
	#elif __PPU__
		#include <stdio.h>
		#define FWDPRINT(...) printf(__VA_ARGS__)
	#else
		#include <windows.h>
		#include <stdio.h>
		#include <tchar.h>

		static void FWDPRINT(LPCTSTR lpszFormat, ...)
		{
		    TCHAR strDebug[1024]={0};
		    va_list argList;
		    va_start(argList, lpszFormat);
		    _vstprintf(strDebug,lpszFormat,argList);
			_stprintf(strDebug,_T("%s"),strDebug);
			OutputDebugString(strDebug);
		    va_end(argList);
		}
	#endif
#else
	#ifdef WIN32
		#define FWDPRINT
	#else
		#define FWDPRINT(...)
	#endif
#endif

#endif
