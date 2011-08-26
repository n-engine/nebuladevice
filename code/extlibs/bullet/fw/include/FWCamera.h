/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// camera class
//
// $File: //nextgendev/Framework_080/include/FWCamera.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_CAMERA_H__
#define __FW_CAMERA_H__

#include "FWMath.h"

// Camera class.
// Used by the <c>FWGLCamApplication</c> and <c>FWGLCamControlApplication</c> classes
// to implement two different camera models:
// A "fly-thru" camera, in which the user can move through the scene
// using the controller, and a "look-at" camera which observes a single point
// and can be rotated and zoomed.
class FWCamera
{
public:
	//-----------------------------------------------------------------------------
	// Description: Camera mode enumeration
	//-----------------------------------------------------------------------------
	enum			Mode
	{
					Mode_FlyThru,	// Camera moves through the world
					Mode_LookAt,	// Camera looks at a single point
	};

	//-----------------------------------------------------------------------------
	// Description: Constructor
	// Parameters:
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline FWCamera() :
	mMode(Mode_FlyThru),
	mPosition(0.f, 0.f, 0.f),
	mTarget(0.f, 0.f, 0.f),
	mPan(0.f),
	mTilt(0.f),
	mDist(1.f)
	{
	}

	//-----------------------------------------------------------------------------
	// Description: Destructor
	// Parameters:
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline ~FWCamera()
	{
	}

	//-----------------------------------------------------------------------------
	// Description: Get the current camera mode
	// Parameters:
	// Returns: The current camera mode
	// Notes:
	//-----------------------------------------------------------------------------
	inline Mode getMode() const
	{
		return mMode;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the current camera mode
	// Parameters:	mode - Camera mode
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setMode(Mode mode)
	{
		mMode = mode;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the current camera position
	// Parameters:	pos - Position
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setPosition(const Point3 &pos)
	{
		mPosition = pos;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the current camera target
	// Parameters:	tar - Camera target
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setTarget(const Point3 &tar)
	{
		mTarget = tar;
	}

	inline Point3 getTarget() const
	{
		return mTarget;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the pan angle (rotation about the y-axis)
	// Parameters:	pan - Angle in radians
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setPan(float pan)
	{
		mPan = pan;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the pan angle (rotation about the y-axis)
	// Parameters:
	// Returns: Angle in radians
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getPan() const
	{
		return mPan;
	}

	//-----------------------------------------------------------------------------
	// Description: Set the tilt angle (rotation about the x-axis)
	// Parameters:	tilt - Angle in radians
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setTilt(float tilt)
	{
		mTilt = tilt;
	}

	//-----------------------------------------------------------------------------
	// Description: Get the tilt angle (rotation about the x-axis)
	// Parameters:
	// Returns: Angle in radians
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getTilt() const
	{
		return mTilt;
	}

	//-----------------------------------------------------------------------------
	// Description: Set distance in look-at mode
	// Parameters:	dist - Distance from target
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setDistance(float dist)
	{
		mDist = dist;
	}

	//-----------------------------------------------------------------------------
	// Description: Get distance in look-at mode
	// Parameters:
	// Returns: Distance from target
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getDistance() const
	{
		return mDist;
	}

	//-----------------------------------------------------------------------------
	// Description: Get a copy of the camera matrix
	// Parameters:
	// Returns: Copy of the camera matrix
	// Notes:
	//-----------------------------------------------------------------------------
	inline Matrix4 getMatrix() const
	{
		return mMatrix;
	}

	//-----------------------------------------------------------------------------
	// Description: Get a copy of the inverse camera matrix
	// Parameters:
	// Returns: Copy of the inverse camera matrix
	// Notes:
	//-----------------------------------------------------------------------------
	inline Matrix4 getInverseMatrix() const
	{
		return mInvMatrix;
	}

	//-----------------------------------------------------------------------------
	// Description: Get camera position
	// Parameters:
	// Returns: Copy of the camera position
	// Notes:
	//-----------------------------------------------------------------------------
	inline Point3 getPosition() const
	{
		return mPosition;
	}

	void			update();

private:
	void			updateFlyThru();
	void			updateLookAt();

	// Camera mode
	Mode			mMode;
	// Camera position
	Point3			mPosition;
	// Camera target
	Point3			mTarget;
	// Pan value
	float			mPan;
	// Tilt value
	float			mTilt;
	// Distance from target
	float			mDist;
	// Camera matrix
	Matrix4			mMatrix;
	// Inverse camera matrix
	Matrix4         mInvMatrix;
};

#endif//__FW_CAMERA_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
