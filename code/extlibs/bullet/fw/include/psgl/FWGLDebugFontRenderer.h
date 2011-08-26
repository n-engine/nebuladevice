/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OGL debug font rendering
//
// $File: //nextgendev/Framework_080/include/FWGLDebugFontRenderer.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef _FWGLDEBUGFONTRENDERER_H_
#define _FWGLDEBUGFONTRENDERER_H_

#include "FWDebugFontRenderer.h"
#include "FWGLInclude.h"

// convert font texture to 32-bit PSGL workaround
#define FWGLDEBUGFONTRENDERER_USE_32BIT

// OGL implementation of debug font renderer. Instantiated within <c>FWGLApplication</c>.
class FWGLDebugFontRenderer : public FWDebugFontRenderer
{
public:
					FWGLDebugFontRenderer();
	virtual			~FWGLDebugFontRenderer();

	virtual void	init();
	virtual void	shutdown();
	virtual void	printStart(float r, float g, float b, float a);
	virtual void	printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts);
	virtual void	printEnd();

private:
#ifdef FWGLDEBUGFONTRENDERER_USE_32BIT
	// pointer to texture
	static GLubyte	*spTextureData;
#endif//FWGLDEBUGFONTRENDERER_USE_32BIT
	// OGL texture handle
	static GLuint	sTextureHandle;

};

#endif//_FWGLDEBUGFONTRENDERER_H_

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
