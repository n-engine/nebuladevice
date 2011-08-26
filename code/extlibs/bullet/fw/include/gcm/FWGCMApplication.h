/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#ifndef __FW_GCMAPPLICATION_H__
#define __FW_GCMAPPLICATION_H__

#include "FWMath.h"
#include "FWGCMConfiguration.h"

// application default values

// projection mode
#define FWGCMAPPLICATION_DEFAULT_PROJECTIONMODE	ProjectionMode_Perspective
// field of view
#define FWGCMAPPLICATION_DEFAULT_FOV		(60.f/180.f*M_PI)
// near clip distance
#define FWGCMAPPLICATION_DEFAULT_NEARCLIP		1.f
// far clip distance
#define FWGCMAPPLICATION_DEFAULT_FARCLIP			1000.f
// clear red component
#define FWGCMAPPLICATION_DEFAULT_CLEAR_RED		0.2f
// clear green component
#define FWGCMAPPLICATION_DEFAULT_CLEAR_GREEN		0.2f
// clear blue component
#define FWGCMAPPLICATION_DEFAULT_CLEAR_BLUE		0.2f
// clear alpha component
#define FWGCMAPPLICATION_DEFAULT_CLEAR_ALPHA		0.f
// clear depth color
#define FWGCMAPPLICATION_DEFAULT_CLEAR_DEPTH		1.f

#include "FWApplication.h"
#include "FWGCMDebugFontRenderer.h"

// GCM application class.
// Derives from FWApplication. Sets view and projection matrices and
// clears the screen.
class FWGCMApplication : public FWApplication
{
public:
							FWGCMApplication();
	virtual					~FWGCMApplication();

	virtual bool			onInit(int argc, char **ppArgv);
	virtual void			onShutdown();
	virtual bool			onUpdate();
	virtual void			onRender();
	virtual void			onSize(const FWDisplayInfo &dispInfo);
	virtual void			onFlip() {}

	void					captureScreen(const char *pFilename);
	void					setViewport();

	static inline FWGCMApplication *getApplication()
	{
		FWASSERT(spApplication != NULL);
		return spApplication;
	}

	inline const FWGCMConfiguration &getConfiguration() const
	{
		return mConfig;
	}

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

	inline Matrix4 getProjectionMatrix() const
	{
		return mProjMatrix;
	}

	inline float getFOV() const
	{
		return mFOV;
	}

	inline void setFOV(const float fov)
	{
		mFOV = fov;
	}

	inline float getNear() const
	{
		return mNear;
	}

	inline void setNear(const float near)
	{
		mNear = near;
	}

	inline float getFar() const
	{
		return mFar;
	}

	inline void setFar(const float far)
	{
		mFar = far;
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
	// Projection matrix
	Matrix4					mProjMatrix;

protected:
	FWGCMConfiguration mConfig;

private:
	// Font renderer instance
	FWGCMDebugFontRenderer	mFontRenderer;

	// Static pointer to the application
	static FWGCMApplication	*spApplication;

private:
	// Clear Buffer By Shader for non-8bit Surfaces
	void renderClear();
	void initClearShader();

	bool	mClearByShader;
	CGprogram	mClearCGVertexProgram;
	CGprogram	mClearCGFragmentProgram;

	void	*mClearVertexProgramUCode;
	void	*mClearFragmentProgramUCode;

	float*	mClearPositionBuffer;
	float*	mClearColorBuffer;
	int mClearVertexCount;
	uint32_t mClearFragmentOffset;
	CGresource mClearPosIndex;
	CGresource mClearColIndex;
	uint32_t mClearPosOffset;
	uint32_t mClearColOffset;
	uint32_t mClearPosDimension;
	uint32_t mClearColDimension;

};

#endif//__FW_GCMAPPLICATION_H__
