/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __UTIL_COMMON_H__
#define __UTIL_COMMON_H__

#if 0
	#define PFX_UTIL_PRINTF DPRINT
#else
	#ifdef WIN32
		#define PFX_UTIL_PRINTF
	#else
		#define PFX_UTIL_PRINTF(...)
	#endif
#endif

#ifdef WIN32
	#define PFX_UTIL_ALLOC(align,size) malloc(size)
#else
	#define PFX_UTIL_ALLOC(align,size) memalign(align,size)
#endif

#define PFX_UTIL_FREE(ptr) if(ptr) {free(ptr);ptr=NULL;}

#endif /* __UTIL_COMMON_H__ */
