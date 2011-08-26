/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// Win32 Window class
//
// $File: //nextgendev/Framework_080/include/win32/FWWin32GLWindow.h $
// $Author: asidwell $
// $Date: 2006/02/14 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_WIN32GLWINDOW_H__
#define __FW_WIN32GLWINDOW_H__

#include <windows.h>
#include "FWWindow.h"
#include "win32/FWWin32DisplayInfo.h"

#define WIN32_WINDOWNAME	"SCE Framework"
#define WIN32_CLASSNAME		"SCEFrameworkClass"

// Win32 specific graphics window encapsulation class.
// Derives from <c>FWWindow</c>.
class FWWin32GLWindow : public FWWindow
{
public:
									FWWin32GLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual 						~FWWin32GLWindow();

	void							update();
	void							destroy();

	virtual void					*getWindowSystemContext();

private:
	virtual void					setRenderingContext();
	virtual void					clearRenderingContext();
	virtual void					flip();
	virtual FWDisplayInfo&			getDisplayInfo();

	// Callback methods for windows stuff
	void							onCreate(HWND hwnd);							// called on WM_CREATE
	void							onSize(int width, int height);					// called on WM_SIZE
	void							onClose();										// called on WM_CLOSE
	void							onDestroy();									// called on WM_DESTROY
	void							onPaint();										// called on WM_PAINT
	// Window proc, calls virtual methods on windows messages
	static LRESULT WINAPI			wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Function to create window.
	void							createWindow();
	// Function to destroy window.
	void							destroyWindow();
	// Function to enable multisampling AA.
	void							enableAA();

	bool							mDontQuit;
	int								mAAPixelFormat;

	// Win32 window handle
	HWND							mHwnd;
	// Win32 device context
	HDC								mHDc;
	// OGL rendering context	
	HGLRC							mHRc;
	// Pixel format descriptor for choosing ogl pixel format
	PIXELFORMATDESCRIPTOR			mPfdPreferredFormat;
	// Win32 display info
	FWWin32DisplayInfo				mDispInfo;
};

#endif //__FW_WIN32GLWINDOW_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
