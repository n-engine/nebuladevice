/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Null debug font rendering
//
// $File: //nextgendev/Framework_080/include/FWNullDebugFontRenderer.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_NULLDEBUGFONTRENDERER_H__
#define __FW_NULLDEBUGFONTRENDERER_H__

#include "FWDebugFontRenderer.h"

// Null debug font renderer, used by <c>FWDebugFont</c>.
// Instantiated within <c>FWNullApplication</c>.
class FWNullDebugFontRenderer : public FWDebugFontRenderer
{
public:
					FWNullDebugFontRenderer();
	virtual 		~FWNullDebugFontRenderer();

	virtual void	init();
	virtual void	shutdown();
	virtual void	printStart(float r, float g, float b, float a);
	virtual void	printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts);
	virtual void	printEnd();

};

#endif//__FW_NULLDEBUGFONTRENDERER_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
