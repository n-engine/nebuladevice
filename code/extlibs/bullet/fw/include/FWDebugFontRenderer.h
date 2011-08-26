/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug font rendering
//
// $File: //nextgendev/Framework_080/include/FWDebugFontRenderer.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_DEBUGFONTRENDERER_H__
#define __FW_DEBUGFONTRENDERER_H__

#include "FWDebugFont.h"

// Abstract base class of debug font renderer.
// Used by <c>FWDebugFont</c>.
class FWDebugFontRenderer
{
public:
					FWDebugFontRenderer();
	virtual 		~FWDebugFontRenderer();

	//-----------------------------------------------------------------------------
	// Description: Initialize debug font renderer
	// Parameters:	
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void	init() = 0;

	//-----------------------------------------------------------------------------
	// Description: Shutdown debug font renderer
	// Parameters:	
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void	shutdown() = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Prepare for rendering text
	// Parameters:	r - Red
	//				g - Green
	//				b - Blue
	//				a - Alpha
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void	printStart(float r, float g, float b, float a) = 0;

	//-----------------------------------------------------------------------------
	// Description: Do a single pass of text rendering
	// Parameters:	pPositions - Vertex position array
	//				pTexCoords - Vertex texture co-ord array
	//				pColors - Vertex color array
	//				numVerts - Number of vertices
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void	printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts) = 0;
	
	//-----------------------------------------------------------------------------
	// Description: Stop text rendering
	// Parameters:
	// Returns:
	// Notes: Pure virtual function
	//-----------------------------------------------------------------------------
	virtual void	printEnd() = 0;

protected:
	//-----------------------------------------------------------------------------
	// Description: Returns pointer to font data
	// Parameters:	
	// Returns: Pointer to font data
	// Notes:
	//-----------------------------------------------------------------------------
	static inline unsigned char *getFontData()
	{
		return FWDebugFont::sFontData;
	}

	// Default color red component
	static float	sR;
	// Default color green component
	static float	sG;
	// Default color blue component
	static float	sB;
	// Default color alpha component
	static float	sA;

};

#endif//__FW_DEBUGFONTRENDERER_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
