//------------------------------------------------------------------------------
//  windowmessagehandler.cc
//  (C) 2010 xoyojank
//------------------------------------------------------------------------------
#include "stdneb.h"
#pragma unmanaged
#include "windowmessagehandler.h"
#include "coregraphics/displaydevice.h"
#include "input/inputserver.h"
#include "graphics/display.h"
#include "graphics/graphicsserver.h"
#include "graphics/cameraentity.h"

//------------------------------------------------------------------------------
namespace Editor
{

using namespace Win32;
using namespace Math;
using namespace CoreGraphics;
using namespace Input;
using namespace Graphics;


//------------------------------------------------------------------------------
void
WindowMessageHandler::OnMinimized()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::DisplayMinimized));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnRestored()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::DisplayRestored));
	// resizing
	if (NULL == this->hWnd)
		return;
	// new size
	RECT rect = { 0 };
	GetClientRect(this->hWnd, &rect);
	// update camera's aspect
	float aspect = float(rect.right) / float(rect.bottom);
	const Ptr<View>& view = GraphicsServer::Instance()->GetDefaultView();
	const Ptr<CameraEntity>& camera = view->GetCameraEntity();
	if (camera.isvalid())
	{
		Shared::CameraSettings settings = camera->GetCameraSettings();
		settings.SetupPerspectiveFov(settings.GetFov(), aspect,
			settings.GetZNear(), settings.GetZFar());
		camera->SetCameraSettings(settings);
	}
	// update device's size
	Display::Instance()->AdjustSize();
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnPaint()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::Paint));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnSetFocus()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::SetFocus));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnKillFocus()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::KillFocus));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnCloseRequested()
{
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::CloseRequested));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnKeyDown(WPARAM wParam)
{
	Key::Code keyCode = Win32DisplayDevice::TranslateKeyCode(wParam);
	if (Key::InvalidKey != keyCode)
	{
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::KeyDown, keyCode));
	}
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnKeyUp(WPARAM wParam)
{
	Key::Code keyCode = Win32DisplayDevice::TranslateKeyCode(wParam);
	if (Key::InvalidKey != keyCode)
	{
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::KeyUp, keyCode));
	}
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnChar(WPARAM wParam)
{
	Char chr = (Char) wParam;
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::Character, chr));
}

//------------------------------------------------------------------------------
inline float2
WindowMessageHandler::ComputeAbsMousePos(LPARAM lParam)
{
	return float2(float(short(LOWORD(lParam))), float(short(HIWORD(lParam))));
}

//------------------------------------------------------------------------------
inline float2
WindowMessageHandler::ComputeNormMousePos(const float2& absMousePos)
{
	float2 normMousePos;
	RECT clientRect = { 0 };
	if ((0 != this->hWnd) && GetClientRect(this->hWnd, &clientRect))
	{
		LONG w = n_max(clientRect.right - clientRect.left, 1);
		LONG h = n_max(clientRect.bottom - clientRect.top, 1);
		normMousePos.set(absMousePos.x() / float(w), absMousePos.y() / float(h));
	}
	else
	{
		n_error("GetClientRect failed!");
	}
	return normMousePos;
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnMouseButton(UINT uMsg, int x, int y)
{
	float2 absMousePos((float)x, (float)y);
	float2 normMousePos = this->ComputeNormMousePos(absMousePos);
	switch (uMsg)
	{
	case WM_LBUTTONDBLCLK:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDoubleClick, MouseButton::LeftButton, absMousePos, normMousePos));
		break;

	case WM_RBUTTONDBLCLK:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDoubleClick, MouseButton::RightButton, absMousePos, normMousePos));
		break;

	case WM_MBUTTONDBLCLK:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDoubleClick, MouseButton::MiddleButton, absMousePos, normMousePos));
		break;

	case WM_LBUTTONDOWN:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDown, MouseButton::LeftButton, absMousePos, normMousePos));
		//SetCapture(this->hWnd);
		break;

	case WM_RBUTTONDOWN:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDown, MouseButton::RightButton, absMousePos, normMousePos));
		//SetCapture(this->hWnd);
		break;

	case WM_MBUTTONDOWN:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonDown, MouseButton::MiddleButton, absMousePos, normMousePos));
		//SetCapture(this->hWnd);
		break;

	case WM_LBUTTONUP:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonUp, MouseButton::LeftButton, absMousePos, normMousePos));
		//ReleaseCapture();
		break;

	case WM_RBUTTONUP:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonUp, MouseButton::RightButton, absMousePos, normMousePos));
		//ReleaseCapture();
		break;

	case WM_MBUTTONUP:
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseButtonUp, MouseButton::MiddleButton, absMousePos, normMousePos));
		//ReleaseCapture();
		break;
	}
	// set keyboard focus to the rendering window
	SetFocus(this->hWnd);
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnMouseMove(int x, int y, bool dragging)
{
	float2 absMousePos((float)x, (float)y);
	float2 normMousePos = this->ComputeNormMousePos(absMousePos);
	this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseMove, absMousePos, normMousePos, dragging));
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::OnMouseWheel(int delta)
{
	if (delta > 0)
	{
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseWheelForward));
	}
	else
	{
		this->NotifyEventHandler(DisplayEvent(DisplayEvent::MouseWheelBackward));
	}
}

//------------------------------------------------------------------------------
void
WindowMessageHandler::NotifyEventHandler(const DisplayEvent& event)
{
	InputServer* inputServer = InputServer::Instance();
	const Ptr<Win32InputDisplayEventHandler> eventHandler = inputServer->GetDisplayEventHandler();
	eventHandler->PutEvent(event);
}

}// Editor