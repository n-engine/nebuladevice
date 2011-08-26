/*   SCE CONFIDENTIAL                                       */
/*   $PSLibId$ */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef __GCM_UTILS_H__
#define __GCM_UTILS_H__

#include <sys/cdefs.h>

CDECL_BEGIN

enum {
	CELL_GCM_UTIL_RGBA8 = 0x8058,
	CELL_GCM_UTIL_ARGB8 = 0xff00,
	CELL_GCM_UTIL_BGRA8 = 0xff01,
	CELL_GCM_UTIL_DXT1  = 0x83f1,
	CELL_GCM_UTIL_DXT3  = 0x83f2,
	CELL_GCM_UTIL_DXT5  = 0x83f3,
	CELL_GCM_UTIL_FP16  = 0x881a,
	CELL_GCM_UTIL_FP32  = 0x8814,
};

extern void cellGcmUtilInitializeLocalMemory(const size_t base,
											 const size_t size);
extern void *cellGcmUtilAllocateLocalMemory(const size_t size,
											const size_t alignment);

extern uint32_t cellGcmUtilGetOffsetOfMainMemory(void* ea);
extern void cellGcmUtilInitializeMainMemory(const size_t size);
extern void *cellGcmUtilAllocateMainMemory(const size_t size,
											 const size_t alignment);

extern int cellGcmUtilGetTextureAttribute(const uint32_t glFormat,
										  uint32_t *gcmFormat, uint32_t *remap,
										  uint32_t swizzle, uint32_t normalize);

CDECL_END

#endif /* __GCM_UTILS_H__ */
