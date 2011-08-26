/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PHYSICS_COMMON_H__
#define __PHYSICS_COMMON_H__

#ifdef WIN32
	#ifdef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
		#undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
		#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
	#endif

	#include <windows.h>
	#include <stdio.h>
	#include <tchar.h>

	typedef char				int8_t;
	typedef unsigned char		uint8_t;
	typedef long				int32_t;
	typedef unsigned long		uint32_t;
	typedef short				int16_t;
	typedef unsigned short		uint16_t;
	typedef long long			int64_t;
	typedef unsigned long long	uint64_t;

	#define __attribute__(a)
	#define aligned(a)
	
	#define fmaxf max
	#define fminf min

	static void OutputDebugStringEx(LPCTSTR lpszFormat, ...)
	{
	    TCHAR strDebug[1024]={0};
	    va_list argList;
	    va_start(argList, lpszFormat);
	    _vstprintf_s(strDebug,lpszFormat,argList);
		_stprintf_s(strDebug,_T("%s"),strDebug);
		OutputDebugString(strDebug);
	    va_end(argList);
	}
#else
	#include <stdio.h>
	#include <stdint.h>

	#define PFX_MAX_SPUS  6 // 最大SPU数
#endif

#define PFX_MAX_TASKS 6

// Debug Print
#if defined(DEBUG)
	#ifdef __SPU__
		#include <spu_printf.h>
		#define DPRINT(...) spu_printf(__VA_ARGS__)
	#elif __PPU__
		#define DPRINT(...) printf(__VA_ARGS__)
	#else
		#define DPRINT OutputDebugStringEx
	#endif
#else
	#ifdef WIN32
		#define DPRINT
	#else
		#define DPRINT(...)
	#endif
#endif

// Printf
#if defined(__SPU__)
	#include <spu_printf.h>
	#define PRINTF(...) spu_printf(__VA_ARGS__)
#elif defined(__PPU__)
	#define PRINTF(...) printf(__VA_ARGS__)
#else
	#define PRINTF OutputDebugStringEx
#endif

#ifdef __SPU__
	#define PFX_UNLIKELY(a)		__builtin_expect((a),0)
	#define PFX_LIKELY(a)		__builtin_expect((a),1)
#else
	#define PFX_UNLIKELY(a)		(a)
	#define PFX_LIKELY(a)		(a)
#endif

// Assert
#include <stdlib.h>

#ifdef __SPU__
	#define PFX_HALT() spu_hcmpeq(0,0)
#else
	#define PFX_HALT() abort()
#endif

//#if defined(_DEBUG)
#if defined(__PPU__)
	#define PFX_ASSERT(x) {if(!(x)){PRINTF("Assert "__FILE__ ":%u ("#x")\n", __LINE__);PFX_HALT();}}
#else
	#define PFX_ASSERT(x)
#endif

// ETC
#define PFX_MIN(a,b) (((a)<(b))?(a):(b))
#define PFX_MAX(a,b) (((a)>(b))?(a):(b))
#define PFX_CLAMP(v,a,b) PFX_MAX(a,PFX_MIN(v,b))
#define PFX_SWAP(type, x, y) do {type t; t=x; x=y; y=t; } while (0)

#define PFX_ALIGN16(count,size)   ((((((count) * (size)) + 15) & (~15)) + (size)-1) / (size))
#define PFX_ALIGN128(count,size)  ((((((count) * (size)) + 127) & (~127)) + (size)-1) / (size))

#define PFX_PI 3.14159265358979f

#endif
