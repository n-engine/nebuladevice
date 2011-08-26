/*   SCE CONFIDENTIAL                                       */
/*   $PSLibId$ */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef __FW_DISPLAYINFO_H__
#define __FW_DISPLAYINFO_H__

#ifdef PSGL
#include <PSGL/psgl.h>
#endif//PSGL

// default values for display
#ifdef CELL_DISPLAY_MODE
#define FWDISPLAYINFO_DEFAULT_MODE			CELL_DISPLAY_MODE
#else
#define FWDISPLAYINFO_DEFAULT_MODE			DisplayMode_720p
#endif

#define FWDISPLAYINFO_DEFAULT_WIDTH			1024
#define FWDISPLAYINFO_DEFAULT_HEIGHT			768
#define FWDISPLAYINFO_DEFAULT_COLOR			24
#define FWDISPLAYINFO_DEFAULT_ALPHA			8
#define FWDISPLAYINFO_DEFAULT_DEPTH			24
#define FWDISPLAYINFO_DEFAULT_STENCIL			8
#define FWDISPLAYINFO_DEFAULT_ANTIALIAS			false
#define FWDISPLAYINFO_DEFAULT_VSYNC			true
#define FWDISPLAYINFO_DEFAULT_PERSISTENT_MEMORY_SIZE	(160 << 20)
#define FWDISPLAYINFO_DEFAULT_PSGL_RAW_SPUS		1
#define FWDISPLAYINFO_DEFAULT_HOST_MEMORY_SIZE		0

// Display information class.
// <c>FWDisplayInfo</c> is used by the application and window classes to
// contain information about the current display (resolution, bit-depth etc.).
// The application can set the starting video mode by setting the contents of
// the class in the application's constructor.
// PSGL initialization options are exposed in the <c>mPSGLInitOptions</c> member.
class FWDisplayInfo
{
public:
				FWDisplayInfo();
				~FWDisplayInfo();

	//-----------------------------------------------------------------------------
	// Description: Display mode enumeration
	//-----------------------------------------------------------------------------
	enum			DisplayMode
	{
				DisplayMode_VGA,	// VGA monitor
				DisplayMode_480i,	// 720x480 lines interlaced
				DisplayMode_480p,	// 720x480 lines progressive
				DisplayMode_576i,	// 720x576 lines interlaced
				DisplayMode_576p,	// 720x576 lines progressive
				DisplayMode_720p,	// 1280x720 lines progressive
				DisplayMode_1080i,	// 1920x1080 lines interlaced
				DisplayMode_1080p,	// 1920x1080 lines progressive

				DisplayMode_WXGA_720p, // 1280x720 lines progressive on VESA 1280x768
				DisplayMode_SXGA_720p, // 1280x720 lines progressive on VESA 1280x1024
				DisplayMode_WUXGA_1080p, // 1920x1080 lines progressive on VESA 1920x1200
	};

	// Display mode	
	DisplayMode		mDisplayMode;
	// Display width (pixels)
	int			mWidth;
	// Display height (pixels)
	int			mHeight;
	// Color depth (bits)
	int			mColorBits;
	// Alpha depth (bits)
	int			mAlphaBits;
	// Z depth (bits)
	int			mDepthBits;
	// Stencil depth (bits)
	int			mStencilBits;
	// Antialiasing enabled flag
	bool			mAntiAlias;
	// Vsync enabled flag
	bool			mVSync;
	// Aspect Ratio (16:9 wide-screen)
	bool		mWideScreen;
#ifdef PSGL
	// PSGL initialization options
	PSGLinitOptions		mPSGLInitOptions;
#endif//PSGL
};

#endif//__FW_DISPLAYINFO_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
