#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::CanvasPanel
        
    (C) 2011 xiongyouyi
*/
#include <wx/window.h>
#include "wx/timer.h"

//------------------------------------------------------------------------------
namespace Editor
{
class CanvasPanel : public wxWindow
{
public:
	CanvasPanel();
	CanvasPanel(wxWindow* parent);
	~CanvasPanel();


	DECLARE_DYNAMIC_CLASS(CanvasPanel);

protected:
	DECLARE_EVENT_TABLE()

	// Event
	void OnSize(wxSizeEvent& e);
	void OnPaint(wxPaintEvent& e);
	void OnLeftDown(wxMouseEvent& e);
	void OnLeftUp(wxMouseEvent& e);
	void OnMiddleDown(wxMouseEvent& e);
	void OnMiddleUp(wxMouseEvent& e);
	void OnRightDown(wxMouseEvent& e);
	void OnRightUp(wxMouseEvent& e);
	void OnMotion(wxMouseEvent& e);
	void OnKeyDown(wxKeyEvent& e);
	void OnKeyUp(wxKeyEvent& e);
	void OnChar(wxKeyEvent& e);
	void OnMouseWheel(wxMouseEvent& e);
	void OnEnterWindow(wxMouseEvent& e);
	void OnLeaveWindow(wxMouseEvent& e);
	void OnRenderTimer(wxTimerEvent& e);
	void OnEraseBackground(wxEraseEvent& e);

	void OnToolsSolid(wxCommandEvent& e);
	void OnToolsWireframe(wxCommandEvent& e);
	void OnToolsPoints(wxCommandEvent& e);

	void createToolbar();

private:
	wxToolBar*	toolbar;
	wxTimer		rendertimer;
	bool		mouseInClient;
};

};
