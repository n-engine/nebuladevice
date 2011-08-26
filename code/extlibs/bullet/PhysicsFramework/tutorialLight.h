/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TUTORIALLIGHT_H__
#define __TUTORIALLIGHT_H__

#include "GLInclude.h"

#include <vectormath_aos.h>

using namespace Vectormath::Aos;

//-----------------------------------------------------------------------------
// Description: 
// The tutorial light class is used to hold data about a simple point light 
// source
// the light has position, diffuse and ambient colors
// Notes: 
//-----------------------------------------------------------------------------
class tutorialLight
{
public:
	tutorialLight():
		mPos(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f)),
		mCol(Vectormath::Aos::Vector3(1.0f,1.0f,1.0f)),
		mAmb(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f))
		{};

	Vectormath::Aos::Vector3 mPos;		//light position in world space
	Vectormath::Aos::Vector3 mCol;		//light color
	Vectormath::Aos::Vector3 mAmb;		//Ambient light color

	void	render();	//renders the light

private:

};
//----------------------------------------------------------------------------








#endif



