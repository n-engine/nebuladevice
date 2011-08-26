/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Generic test application
//
// $File: //nextgendev/Framework_080/testapp/include/testapp.h $
// $Author: asidwell $
// $Date: 2006/01/09 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef _TESTAPP_H_
#define _TESTAPP_H_

#include "psgl/FWGLCamControlApplication.h"
#include "psgl/FWGLGrid.h"

class TestApp : public FWGLCamControlApplication
{
public:
					TestApp();
	virtual bool	onInit(int argc, char **ppArgv);
	virtual void	onRender();
	virtual	void	onShutdown();
	virtual void	onSize(const FWDisplayInfo & dispInfo);

private:
	FWInputFilter	*mpSpaceKey, *mpMouseX, *mpMouseY, *mpMouseLeft, *mpMouseMiddle, *mpMouseRight;
	FWInputFilter	*mpLeftX, *mpLeftY, *mpRightX, *mpRightY;
	FWInputFilter	*mpUp, *mpRight, *mpDown, *mpLeft;
	FWInputFilter	*mpTriangle, *mpCircle, *mpCross, *mpSquare;
	FWInputFilter	*mpL1, *mpL2, *mpL3;
	FWInputFilter	*mpR1, *mpR2, *mpR3;
	FWInputFilter	*mpSelect, *mpStart;
	
	FWTimeVal		mLastTime;
	FWGLGrid		mGrid;

};

#endif//_TESTAPP_H_
