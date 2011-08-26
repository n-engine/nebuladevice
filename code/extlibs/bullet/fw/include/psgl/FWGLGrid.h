/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// debug grid rendering
//
// $File: //nextgendev/Framework_080/include/FWGLGrid.h $
// $Author: asidwell $
// $Date: 2006/01/06 $
// $Revision: #1 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLGRID_H__
#define __FW_GLGRID_H__

// Grid rendering class. It can be useful as a graphical debugging aid.
// Can set the color, size, width and spacing between adjacent grid lines, as well
// as the plane in which to render the grid.
class FWGLGrid
{
public:
	//-----------------------------------------------------------------------------
	// Description: Grid plane enumeration
	//-----------------------------------------------------------------------------
	enum			Plane
	{
					Plane_Undefined,	// Undefined
					Plane_XY,			// The XY plane
					Plane_XZ,			// The XZ plane
					Plane_YZ,			// The YZ plane
	};

					FWGLGrid();
					~FWGLGrid();

	//-----------------------------------------------------------------------------
	// Description: Set the plane in which the grid is set
	// Parameters:	plane - Plane
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setPlane(Plane plane)
	{
		if(mPlane != plane)
		{
			mPlane = plane;
			mBuildGrid = true;
		}
	}

	//-----------------------------------------------------------------------------
	// Description: Get the plane in which the grid is set
	// Parameters:
	// Returns: Plane of grid
	// Notes:
	//-----------------------------------------------------------------------------
	inline Plane getPlane() const
	{
		return mPlane;
	}

	//-----------------------------------------------------------------------------
	// Description: Set size of grid
	// Parameters:	size - Size of grid
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void	setSize(float size)
	{
		if(mSize != size)
		{
			mSize = size;
			mBuildGrid = true;
		}
	}

	//-----------------------------------------------------------------------------
	// Description: Get size of grid
	// Parameters:
	// Returns: Size of grid
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getSize() const
	{
		return mSize;
	}

	//-----------------------------------------------------------------------------
	// Description: Set spacing between grid lines
	// Parameters:	spacing - Distance between grid lines
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void	setSpacing(float spacing)
	{
		if(mSpacing != spacing)
		{
			mSpacing = spacing;
			mBuildGrid = true;
		}
	}

	//-----------------------------------------------------------------------------
	// Description: Get spacing between major grid lines
	// Parameters:
	// Returns: Distance between grid lines
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getSpacing() const
	{
		return mSpacing;
	}

	//-----------------------------------------------------------------------------
	// Description: Set number of sub-lines between major grid lines
	// Parameters:	sublines - Number of sub-lines
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setSubLines(int sublines)
	{
		if(mSubLines != sublines)
		{
			mSubLines = sublines;
			mBuildGrid = true;
		}
	}

	//-----------------------------------------------------------------------------
	// Description: Get number of sub-lines between major grid lines
	// Parameters:
	// Returns: Number of sub-lines between major grid lines
	// Notes:
	//-----------------------------------------------------------------------------
	inline int getSubLines() const
	{
		return mSubLines;
	}

	//-----------------------------------------------------------------------------
	// Description: Set major axis color
	// Parameters:	r - Red
	//				g - Green
	//				b - Blue
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setAxisColor(float r, float g, float b)
	{
		mAxisR = r;
		mAxisG = g;
		mAxisB = b;
		mBuildGrid = true;
	}

	//-----------------------------------------------------------------------------
	// Description: Set grid line color
	// Parameters:	r - Red
	//				g - Green
	//				b - Blue
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setGridLineColor(float r, float g, float b)
	{
		mLineR = r;
		mLineG = g;
		mLineB = b;
		mBuildGrid = true;
	}

	//-----------------------------------------------------------------------------
	// Description: Set sub-line color
	// Parameters:	r - Red
	//				g - Green
	//				b - Blue
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setSubLineColor(float r, float g, float b)
	{
		mSubR = r;
		mSubG = g;
		mSubB = b;
		mBuildGrid = true;
	}

	//-----------------------------------------------------------------------------
	// Description: Set line width in pixels
	// Parameters:	width - Line width in pixels
	// Returns:
	// Notes:
	//-----------------------------------------------------------------------------
	inline void setLineWidth(float width)
	{
		mLineWidth = width;
	}

	//-----------------------------------------------------------------------------
	// Description: Get line width in pixels
	// Parameters:
	// Returns: Line width in pixels
	// Notes:
	//-----------------------------------------------------------------------------
	inline float getLineWidth() const
	{
		return mLineWidth;
	}

	void			render();

private:
	void			buildGrid();
	int				calcNumVerts();

	// Plane of the grid
	Plane			mPlane;
	// Size of the grid
	float			mSize;
	// Spacing of the grid
	float			mSpacing;
	// Number of sub-lines per grid line
	int				mSubLines;
	// Main axis color red component
	float			mAxisR;
	// Main axis color rgreen component
	float			mAxisG;
	// Main axis color blue component
	float			mAxisB;
	// Line color red component
	float			mLineR;
	// Line color green component
	float			mLineG;
	// Line color blue component
	float			mLineB;
	// Sub-line color red component
	float			mSubR;
	// Sub-line color green component
	float			mSubG;
	// Sub-line color blue component
	float			mSubB;
	// Array of verts
	float			*mpVerts;
	// Array of colors
	float			*mpCols;
	// Number of verts
	int				mNumVerts;
	// Total number of grid lines
	int				mNumGridLines;
	// Total number of sub-lines
	int				mNumSubLines;
	// Line width
	float			mLineWidth;
	// Grid needs building
	bool			mBuildGrid;

};

#endif//__FW_GLGRID_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
