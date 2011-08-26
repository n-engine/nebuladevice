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
// $File: //nextgendev/Framework_050/include/FWGLDebugFontRenderer.h $
// $Author: asidwell $
// $Date: 2005/09/09 $
// $Revision: #1 $
//
// Copyright (C) 2005 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef _FWGCMDEBUGFONTRENDERER_H_
#define _FWGCMDEBUGFONTRENDERER_H_

#include <stdint.h>
#include <cell/gcm.h>

#include "FWDebugFontRenderer.h"

// convert font texture to 32-bit GCM workaround
//#define FWGCMDEBUGFONTRENDERER_USE_32BIT

#undef FWDEBUGFONT_PRIMITIVE
#ifdef FWDEBUGFONT_USE_QUADS
#define FWDEBUGFONT_PRIMITIVE CELL_GCM_PRIMITIVE_QUADS
#define NUM_VERTS_PER_GLYPH	4
#else
#define FWDEBUGFONT_PRIMITIVE CELL_GCM_PRIMITIVE_TRIANGLES
#define NUM_VERTS_PER_GLYPH	6
#endif

// GCM implementation of debug font renderer
class FWGCMDebugFontRenderer : public FWDebugFontRenderer
{
public:
					FWGCMDebugFontRenderer();
	virtual			~FWGCMDebugFontRenderer();

	virtual void	init();
	virtual void	shutdown();
	virtual void	printStart(float r, float g, float b, float a);
	virtual void	printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts);
	virtual void	printEnd();

private:
	static void initShader();

private:
	// pointer to texture
	static uint8_t	*spTextureData;

	static uint8_t *mPosition;
	static uint8_t *mTexCoord;
	static uint8_t *mColor;

	static uint32_t mPositionOffset;
	static uint32_t mTexCoordOffset;
	static uint32_t mColorOffset;

	static uint8_t *mpTexture;
	static CGresource mPosIndex;
	static CGresource mTexIndex;
	static CGresource mColIndex;
	static CGresource mTexUnit;

	static CGprogram mCGVertexProgram;				// CG binary program
	static CGprogram mCGFragmentProgram;			// CG binary program

	static uint32_t mFragmentProgramOffset;
	static uint32_t mTextureOffset;

	static void *mVertexProgramUCode;				// this is sysmem
	static void *mFragmentProgramUCode;			// this is vidmem

	static CGparameter mModelViewProj;
	static float mMVPMatrix[16];

	static uint32_t *mLabel;
	static uint32_t mLabelValue;

private:
	static const uint32_t sLabelId = 65;
};

#endif//_FWGCMDEBUGFONTRENDERER_H_
