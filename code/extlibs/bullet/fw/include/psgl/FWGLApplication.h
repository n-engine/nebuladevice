/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// GL Application class
//
// $File: //nextgendev/Framework_080/include/FWGLApplication.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLAPPLICATION_H__
#define __FW_GLAPPLICATION_H__

#include "FWMath.h"

// application default values

// projection mode
#define FWGLAPPLICATION_DEFAULT_PROJECTIONMODE	ProjectionMode_Perspective
// field of view
#define FWGLAPPLICATION_DEFAULT_FOV				45.f
// near clip distance
#define FWGLAPPLICATION_DEFAULT_NEARCLIP		1.f
// far clip distance
#define FWGLAPPLICATION_DEFAULT_FARCLIP			1000.f
// clear red component
#define FWGLAPPLICATION_DEFAULT_CLEAR_RED		0.2f
// clear green component
#define FWGLAPPLICATION_DEFAULT_CLEAR_GREEN		0.2f
// clear blue component
#define FWGLAPPLICATION_DEFAULT_CLEAR_BLUE		0.2f
// clear alpha component
#define FWGLAPPLICATION_DEFAULT_CLEAR_ALPHA		0.f
// clear depth color
#define FWGLAPPLICATION_DEFAULT_CLEAR_DEPTH		1.f

#include "FWApplication.h"
#include "FWGLDebugFontRenderer.h"

// OpenGL application class.
// Derives from <c>FWApplication</c>. Sets view and projection matrices and
// clears the screen.
// If an application requires camera functionality, it should be derived from
// either <c>FWGLCamApplication</c> or <c>FWGLCamControlApplication</c>.
class FWGLApplication : public FWApplication
{
public:
							FWGLApplication();
	virtual					~FWGLApplication();

	virtual bool			onInit(int argc, char **ppArgv);
	virtual void			onShutdown();
	virtual bool			onUpdate();
	virtual void			onRender();
	virtual void			onSize(const FWDisplayInfo &dispInfo);

	void					captureScreen(const char *pFilename);

	//-----------------------------------------------------------------------------
	// Description: Projection mode enumeration
	//-----------------------------------------------------------------------------
	enum					ProjectionMode
	{
							ProjectionMode_Perspective,		// Perspective projection
							ProjectionMode_Orthographic,	// Orthographic projection
	};

	//-----------------------------------------------------------------------------
	// Description: Set projection matrix mode
	// Parameters:	mode - Projection mode to set
	// Returns:
	// Notes: Defaults to perspective mode
	//-----------------------------------------------------------------------------
	inline void setProjectionMode(ProjectionMode mode)
	{
		mProjMode = mode;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the clear color red component
	// Parameters:	red - Clear color red component (0 -> 1)
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setClearRed(float red)
	{
		mClearRed = red;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the clear color green component
	// Parameters:	green - Clear color green component (0 -> 1)
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setClearGreen(float green)
	{
		mClearGreen = green;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the clear color blue component
	// Parameters:	blue - Clear color blue component (0 -> 1)
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setClearBlue(float blue)
	{
		mClearBlue = blue;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the clear color alpha component
	// Parameters:	alpha - Clear color alpha component (0 -> 1)
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setClearAlpha(float alpha)
	{
		mClearAlpha = alpha;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the clear depth component
	// Parameters:	depth - Clear depth component
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setClearDepth(float depth)
	{
		mClearDepth = depth;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the view matrix
	// Parameters:	mat - View matrix reference
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setViewMatrix(const Matrix4 &mat) 
	{
		mViewMatrix = mat;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the current view matrix
	// Parameters:
	// Returns: A copy of the current view matrix
	// Notes:
	//-----------------------------------------------------------------------------
	inline Matrix4 getViewMatrix() const
	{
		return mViewMatrix;
	}

	inline float getFOV() const
	{
		return mFOV;
	}

	inline void setFOV(const float fov)
	{
		mFOV = fov;
	}

protected:
	// Projection mode
	ProjectionMode			mProjMode;
	// Field of view in degrees
	float					mFOV;
	// Near clip distance
	float					mNear;
	// Far clip distance
	float					mFar;
	// Clear color (red component)
	float					mClearRed;
	// Clear color (green component)
	float					mClearGreen;
	// Clear color (blue component)
	float					mClearBlue;
	// Clear color (alpha component)
	float					mClearAlpha;
	// Clear depth value
	float					mClearDepth;
	// View matrix
	Matrix4					mViewMatrix;

private:
	// Font renderer instance
	FWGLDebugFontRenderer	mFontRenderer;

};

#endif//__FW_GLAPPLICATION_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
