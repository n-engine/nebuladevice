#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::WindowMessageHandler
  
   Translate from WM_ messsages to DisplayEvent. 
    
    (C) 2010 xoyojank
*/
#include "coregraphics/displayevent.h"

//------------------------------------------------------------------------------
namespace Editor
{

class WindowMessageHandler
{
public:
	/// constructor
	WindowMessageHandler(HWND _hwnd);
	/// destructor
	~WindowMessageHandler();

	/// send display event to render thread
	void NotifyEventHandler(const CoreGraphics::DisplayEvent& event);
	/// called on WM_SIZE when window is minimized
	void OnMinimized();
	/// called on WM_SIZE when window is restored
	void OnRestored();
	/// called on WM_PAINT
	void OnPaint();
	/// called on WM_SETFOCUS
	void OnSetFocus();
	/// called on WM_KILLFOCUS
	void OnKillFocus();
	/// called on WM_CLOSE to request if window should be closed
	void OnCloseRequested();
	/// called on WM_KEYDOWN
	void OnKeyDown(WPARAM wParam);
	/// called on WM_KEYUP
	void OnKeyUp(WPARAM wParam);
	/// called on WM_CHAR
	void OnChar(WPARAM wParam);
	/// called on mouse button event
	void OnMouseButton(UINT uMsg, int x, int y);
	/// called on WM_MOUSEMOVE
	void OnMouseMove(int x, int y, bool dragging);
	/// called on WM_MOUSEWHEEL
	void OnMouseWheel(int delta);

private:
	/// compute absolute mouse position from lParam
	Math::float2 ComputeAbsMousePos(LPARAM lParam);
	/// compute normalized mouse position from absolute mouse pos
	Math::float2 ComputeNormMousePos(const Math::float2& absMousePos);

private:
	HWND hWnd;
	int width;
	int height;
};

//------------------------------------------------------------------------------
/**
*/
inline 
WindowMessageHandler::WindowMessageHandler(HWND _hwnd)
: hWnd(_hwnd)
, width(0)
, height(0)
{
}

//------------------------------------------------------------------------------
/**
*/
inline
WindowMessageHandler::~WindowMessageHandler()
{
}

}// Editor