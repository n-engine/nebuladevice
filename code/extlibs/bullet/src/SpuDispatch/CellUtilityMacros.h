/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/

#ifndef __CELL_UTILITY_MACROS_H
#define __CELL_UTILITY_MACROS_H

#ifndef __CELLOS_LV2__
typedef unsigned int uint32_t;
#endif

// This type pretends to be a pointer to a type on the PPU, and
// just an unsigned int on the SPU.
#ifndef CELL_PPU_POINTER
#define CELL_PPU_PTR_TYPE uint32_t

#ifdef __SPU__
#define CELL_PPU_POINTER(x) CELL_PPU_PTR_TYPE
#else // __SPU__
#define CELL_PPU_POINTER(x) x *

// Hope we never switch away from 32 bits...
// But this is here just in case...
//NX_COMPILE_TIME_ASSERT(sizeof(void *)==sizeof(CELL_PPU_PTR_TYPE));
#endif // __SPU__
#endif // CELL_PPU_POINTER



// Make windows/MSVC ignore GCC specific keywords.
#ifdef WIN32
#ifndef __attribute__
#define __attribute__(x) 
#endif // __attribute__

#ifndef __builtin_prefetch
#define __builtin_prefetch(x, y) do {} while (0)
#endif // __builtin_prefetch

#ifndef __builtin_expect
#define __builtin_expect(cond, exp) (cond)
#endif // __builtin_expect
#endif // WIN32


#endif
