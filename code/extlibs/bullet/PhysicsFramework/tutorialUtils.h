/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TUTORIALUTILS_H__
#define __TUTORIALUTILS_H__

#include <stdio.h>
#include "GLInclude.h"

CGprogram loadProgramFromFile(CGcontext context,CGprofile target, const char* filename);

inline void CheckCgError(int line)
{
	(void) line;

	CGerror err = cgGetError();

	if(err != CG_NO_ERROR) {
		printf("CG error:%d at line %d %s\n", err, line, cgGetErrorString (err));
		exit (0);
	}
}

#endif
