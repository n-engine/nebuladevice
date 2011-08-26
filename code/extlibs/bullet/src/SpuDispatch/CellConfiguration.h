/* SCE CONFIDENTIAL
 * $PSLibId$
 * Copyright (C) 2008 Sony Computer Entertainment Inc.
 * All Rights Reserved.
*/


#ifndef __CELL_CONFIGURATION_H
#define __CELL_CONFIGURATION_H

///enable/disable SPU Tree optimizations
#define SCE_USE_SPU_MIDPHASE 1

#define SCE_USE_SPU_CONVEX

#ifndef __CELL_OPT__
#define __CELL_OPT__
#endif

#define SCE_SPURS_NP
#define SCE_SPURS_MP
#define SCE_SPURS_CONPREP

// Sauce: Removed this.  It will be passed in by the makefile when building
// external releases.  We should not explicitly disable it.
#undef SCE_EXTERNAL_RELEASE

#define USE_VECTORMATH

// Solver-related #define's.
#define SCE_USE_SOLVER
// Sauce: Working on job-based solving
//#define SCE_JOB_BASED_SOLVING
#define SCE_SPURS_SOLVER


#undef SCE_CONTROL_CONSOLE

#ifdef WIN32
#define EXPORT_SYM __declspec( dllexport )
#else
#define EXPORT_SYM 
#endif

#endif
