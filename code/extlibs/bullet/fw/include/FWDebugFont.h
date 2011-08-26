/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Debug font functionality
//
// $File: //nextgendev/Framework_080/include/FWDebugFont.h $
// $Author: asidwell $
// $Date: 2006/02/03 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_DEBUGFONT_H__
#define __FW_DEBUGFONT_H__

#define FWDEBUGFONT_TEXTURE_WIDTH		128
#define FWDEBUGFONT_TEXTURE_HEIGHT		128
#define FWDEBUGFONT_GLYPH_WIDTH			8
#define FWDEBUGFONT_GLYPH_HEIGHT		9
#define FWDEBUGFONT_DATA_SIZE			(FWDEBUGFONT_TEXTURE_WIDTH * FWDEBUGFONT_TEXTURE_HEIGHT)
#define FWDEBUGFONT_TAB_SIZE			4
#define FWDEBUGFONT_MAX_CHAR_COUNT		256
#define FWDEBUGFONT_DEFAULT_SAFE_AREA	40

#define FWDEBUGFONT_USE_QUADS

#ifdef FWDEBUGFONT_USE_QUADS
#define FWDEBUGFONT_PRIMITIVE			GL_QUADS
#else
#define FWDEBUGFONT_PRIMITIVE			GL_TRIANGLES
#endif

// debug font renderer
class FWDebugFontRenderer;

// Debug text rendering.
// <c>FWDebugFont</c> is used by the debug console, but can also be used directly
// by the application to print text on the screen. The position and color
// can be set before the text is written. Newlines within the strings are
// supported, so the position only need be set before printing a number of
// strings.
class FWDebugFont
{
public:
	static void					init();
	static void					shutdown();

	//-----------------------------------------------------------------------------
	// Description: Set text position
	// Parameters:	x - X coordinate
	//				y - Y coordinate
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void setPosition(int x, int y)
	{
		sXPos = x;
		sYPos = y;
	}

	//-----------------------------------------------------------------------------
	// Description: Set text color
	// Parameters:	r - Red component
	//				g - Green component
	//				b - Blue component
	//				a - Alpha component
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void	setColor(float r, float g, float b, float a)
	{
		sR = r;
		sG = g;
		sB = b;
		sA = a;
	}

	static void					print(const char *pText);
	static void					printf(const char *pText, ...);

	//-----------------------------------------------------------------------------
	// Description: Get the glyph width
	// Parameters:
	// Returns: The glyph width in pixels
	// Notes:
	//-----------------------------------------------------------------------------
	static inline int getGlyphWidth()
	{
		return FWDEBUGFONT_GLYPH_WIDTH;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the glyph height
	// Parameters:
	// Returns: The glyph height in pixels
	// Notes:
	//-----------------------------------------------------------------------------
	static inline int getGlyphHeight()
	{
		return FWDEBUGFONT_GLYPH_HEIGHT;
	}

	static void	getExtents(const char *pText, int *piWidth, int *piHeight, int iScrWidth);

	//-----------------------------------------------------------------------------
	// Description: Set the screen resolution
	// Parameters:	x - X resolution in pixels
	//				y - Y resolution in pixels
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void setScreenRes(int x, int y)
	{
		sXRes = x;
		sYRes = y;
	}

	//-----------------------------------------------------------------------------
	// Description: Set size of safe area
	// Parameters:	left - Left position of safe area in pixels
	//				right - Right position of safe area in pixels
	//				top - Top position of safe area in pixels
	//				bottom - Bottom position of safe area in pixels
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void setSafeArea(int left, int right, int top, int bottom)
	{
		sLeftSafe = left;
		sRightSafe = right;
		sTopSafe = top;
		sBottomSafe = bottom;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the extents of the safe area
	// Parameters:	pLeft - Pointer to int to return left position of safe area in pixels
	//				pRight - Pointer to int to return right position of safe area in pixels
	//				pTop - Pointer to int to return top position of safe area in pixels
	//				pBottom - Pointer to int to return bottom position of safe area in pixels
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	static inline void getSafeArea(int *pLeft, int *pRight, int *pTop, int *pBottom)
	{
		*pLeft = sLeftSafe;
		*pRight = sRightSafe;
		*pTop = sTopSafe;
		*pBottom = sBottomSafe;
	}

	// Vertex position
	class Position
	{
	public:
		// X coordinate
		float mX;
		// Y coordinate
		float mY;
		// Z coordinate
		float mZ;
	};

	// Vertex texture co-ordinates
	class TexCoord
	{
	public:
		// S texture coordinate
		float mS;
		// T texture coordinate
		float mT;
	};

	// Vertex color
	class Color
	{
	public:
		// Red
		float mR;
		// Green
		float mG;
		// Blue
		float mB;
		// Alpha
		float mA;
	};

private:

	static void			print(const char *pText, int iNumChars);

	//-----------------------------------------------------------------------------
	// Description: Calculate position in screen space
	// Parameters:	pos - Pixel coordinate
	//				dim - Screen dimension in pixels
	// Returns: Float coordinate from -1 to +1
	// Notes:
	//-----------------------------------------------------------------------------
	static inline float calcPos(int pos, int dim)
	{
		return ((float)pos - ((float)dim * 0.5f)) / ((float)dim * 0.5f);
	}

	//-----------------------------------------------------------------------------
	// Description: Calculate left texture coordinate for glyph
	// Parameters:	c - Character
	// Returns: Left texture coordinate
	// Notes:
	//-----------------------------------------------------------------------------
	static inline float calcS0(unsigned char c)
	{
		return (float)((c % 16) * getGlyphWidth()) / (float)FWDEBUGFONT_TEXTURE_WIDTH;
	}

	//-----------------------------------------------------------------------------
	// Description: Calculate right texture coordinate for glyph
	// Parameters:	c - Character
	// Returns: Right texture coordinate
	// Notes:
	//-----------------------------------------------------------------------------
	static inline float calcS1(unsigned char c)
	{
		return (float)(((c % 16) * getGlyphWidth()) + getGlyphWidth()) / (float)FWDEBUGFONT_TEXTURE_WIDTH;
	}


	//-----------------------------------------------------------------------------
	// Description: Calculate top texture coordinate for glyph
	// Parameters:	c - Character
	// Returns: Top texture coordinate
	// Notes:
	//-----------------------------------------------------------------------------
	static inline float calcT0(unsigned char c)
	{
		return (float)((((c / 16) - 2) * getGlyphHeight()) + 1) / (float)FWDEBUGFONT_TEXTURE_HEIGHT;
	}

	//-----------------------------------------------------------------------------
	// Description: Calculate bottom texture coordinate for glyph
	// Parameters:	c - Character
	// Returns: Bottom texture coordinate
	// Notes:
	//-----------------------------------------------------------------------------
	static inline float calcT1(unsigned char c)
	{
		return (float)((((c / 16) - 2) * getGlyphHeight()) + getGlyphHeight() + 1) / (float)FWDEBUGFONT_TEXTURE_HEIGHT;
	}

	//-----------------------------------------------------------------------------
	// Description: Get whether character is printable
	// Parameters:	c - Character
	// Returns: True if printable, false otherwise
	// Notes:
	//-----------------------------------------------------------------------------
	static inline bool getPrintable(char c)
	{
		return ((unsigned char)c & 0x7f) > 31;
	}

	// font data
	static unsigned char		sFontData[FWDEBUGFONT_DATA_SIZE];

	// Current screen X position
	static int					sXPos;
	// Current screen Y position
	static int					sYPos;
	// Screen X resolution
	static int					sXRes;
	// Screen Y resolution
	static int					sYRes;
	// Left safe area position
	static int					sLeftSafe;
	// Right safe area position
	static int					sRightSafe;
	// Top safe area position
	static int					sTopSafe;
	// Bottom safe area position	
	static int					sBottomSafe;
	// Current color red component
	static float				sR;
	// Current color green component
	static float				sG;
	// Current color blue component
	static float				sB;
	// Current color alpha component
	static float				sA;
	// double buffer position array
	static Position				*spPositions[2];
	// double buffer texture co-ordinate array
	static TexCoord				*spTexCoords[2];
	// double buffer color array
	static Color				*spColors[2];
	// control code colors
	static Color				sDefaultColors[8];
	// rendering code
	static FWDebugFontRenderer	*spRenderer;
	// make <c>FWDebugFontRenderer</c> a friend
	friend class				FWDebugFontRenderer;
	// make <c>FWDebugConsole</c> a friend
	friend class				FWDebugConsole;
};

#endif//__FW_DEBUGFONT_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
