//------------------------------------------------------------------------------
//  canvaspanel.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "wx/wx.h"
#include "editorapp.h"
#include "CanvasPanel.h"
#include "../app/editorapplication.h"
#include "basegamefeature/managers/envquerymanager.h"

namespace Editor
{
const long ID_RENDERTIMER	 = wxNewId();
const long ID_TOOLS_POLYMODE = wxNewId();
const long ID_TOOLS_SOLID	 = wxNewId();
const long ID_TOOLS_WIREFRAME= wxNewId();
const long ID_TOOLS_POINTS   = wxNewId();

using namespace Editor;


IMPLEMENT_DYNAMIC_CLASS(CanvasPanel, wxWindow)

BEGIN_EVENT_TABLE(CanvasPanel, wxWindow)
	EVT_SIZE(CanvasPanel::OnSize)
	EVT_PAINT(CanvasPanel::OnPaint)
	EVT_KEY_DOWN(CanvasPanel::OnKeyDown)
	EVT_KEY_UP(CanvasPanel::OnKeyUp)
	EVT_CHAR(CanvasPanel::OnChar)
	EVT_LEFT_DOWN(CanvasPanel::OnLeftDown)
	EVT_LEFT_UP(CanvasPanel::OnLeftUp)
	EVT_MIDDLE_DOWN(CanvasPanel::OnMiddleDown)
	EVT_MIDDLE_UP(CanvasPanel::OnMiddleUp)
	EVT_RIGHT_DOWN(CanvasPanel::OnRightDown)
	EVT_RIGHT_UP(CanvasPanel::OnRightUp)
	EVT_MOTION(CanvasPanel::OnMotion)
	EVT_MOUSEWHEEL(CanvasPanel::OnMouseWheel)
	EVT_ENTER_WINDOW(CanvasPanel::OnEnterWindow)
	EVT_LEAVE_WINDOW(CanvasPanel::OnLeaveWindow)
	EVT_ERASE_BACKGROUND(CanvasPanel::OnEraseBackground)
	EVT_TIMER(ID_RENDERTIMER, CanvasPanel::OnRenderTimer)
	EVT_MENU(ID_TOOLS_SOLID, CanvasPanel::OnToolsSolid)
	EVT_MENU(ID_TOOLS_WIREFRAME, CanvasPanel::OnToolsWireframe)
	EVT_MENU(ID_TOOLS_POINTS, CanvasPanel::OnToolsPoints)
END_EVENT_TABLE()

//---------------------------------------------------------------------
//---------------------------------------------------------------------
CanvasPanel::CanvasPanel()
: wxWindow(NULL, -1)
, toolbar(0)
, rendertimer(this, ID_RENDERTIMER)
, mouseInClient(false)
{
	//createToolbar();
	rendertimer.Start(10);
}

//---------------------------------------------------------------------
CanvasPanel::CanvasPanel(wxWindow* parent)
: wxWindow(parent, -1)
, toolbar(0)
, rendertimer(this, ID_RENDERTIMER)
, mouseInClient(false)
{
	//createToolbar();
	rendertimer.Start(10);
}

//---------------------------------------------------------------------
CanvasPanel::~CanvasPanel()
{
	if (GetEditor()->IsOpen())
	{
		GetEditor()->EndUpdate();
		GetEditor()->Close();
	}
}

//---------------------------------------------------------------------
void 
CanvasPanel::createToolbar()
{
	this->toolbar = new wxToolBar(this,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);

	this->toolbar->SetMargins(2, 2);
	this->toolbar->SetToolBitmapSize(wxSize(16,16));
	this->toolbar->AddSeparator();
	this->toolbar->AddTool(wxID_ANY, _("Select"), 
		wxBitmap( wxT("./res/pointer.gif"), wxBITMAP_TYPE_GIF), _("Select"), wxITEM_RADIO);
	this->toolbar->AddTool(wxID_ANY, _("Move"), 
		wxBitmap( wxT("./res/bullet_black.png"), wxBITMAP_TYPE_PNG), _("Move"), wxITEM_RADIO);
	this->toolbar->AddTool(wxID_ANY, _("Rotate"), 
		wxBitmap( wxT("./res/bullet_black.png"), wxBITMAP_TYPE_PNG), _("Rotate"), wxITEM_RADIO);
	this->toolbar->AddTool(wxID_ANY, _("Scale"), 
		wxBitmap( wxT("./res/bullet_black.png"), wxBITMAP_TYPE_PNG), _("Scale"), wxITEM_RADIO);
	//mToolbar->ToggleTool(wxID_ANY, true);
	this->toolbar->AddSeparator();

	//mToolbar->AddTool(ID_TOOLS_POLYMODE, _("PolyMode"), 
	//	wxBitmap( wxT("./icons/bullet_black.png"), wxBITMAP_TYPE_PNG), _("Polygon Mode"));
	//mToolbar->SetToolDropDown(ID_TOOLS_POLYMODE, true);

	this->toolbar->Realize();
}

//---------------------------------------------------------------------
void 
CanvasPanel::OnSize(wxSizeEvent& e)
{
	wxSize sz = GetClientSize();

	// manually resize the toolbar
	//this->toolbar->SetSize(sz.x, 25);

	if (GetEditor()->IsOpen())
	{
		GetEditor()->GetWindowMessageHandler()->OnRestored();
	}
}

//---------------------------------------------------------------------
void 
CanvasPanel::OnPaint(wxPaintEvent& e)
{
	// Keep wxWidgets happy
	wxPaintDC dc(this);

	if (GetEditor()->IsOpen())
	{
		GetEditor()->GetWindowMessageHandler()->OnPaint();
		GetEditor()->UpdateOneFrame();
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnEraseBackground(wxEraseEvent& e)
{
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnRenderTimer(wxTimerEvent& event)
{
	if (GetEditor()->IsOpen())
	{
		MainFrame* mainFrame = ((EditorApp*)wxTheApp)->GetMainFrame();
		//BaseGameFeature::EnvQueryManager* envQueryManager = BaseGameFeature::EnvQueryManager::Instance();
		//n_assert(mainFrame);
		//n_assert(envQueryManager);

		//// entity under mouse
		//Util::String text("no selection");
		//Game::Entity* entity = envQueryManager->GetEntityUnderMouse();
		//if (entity)
		//{
		//	text = entity->GetString(Attr::_ID);
		//}
		//mainFrame->SetStatusText(text.AsCharPtr(), 0);

		//// mouse world position
		//Math::point mousePos = envQueryManager->GetMousePos3d();
		//text.Format("%.2f, %.2f, %.2f", mousePos.x(), mousePos.y(), mousePos.z());	
		//mainFrame->SetStatusText(text.AsCharPtr(), 1);
		
		// update the frame
		GetEditor()->UpdateOneFrame();
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnLeftDown(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_LBUTTONDOWN, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnLeftUp(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_LBUTTONUP, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnMiddleDown(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_MBUTTONDOWN, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnMiddleUp(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_MBUTTONUP, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void CanvasPanel::OnRightDown(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_RBUTTONDOWN, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnRightUp(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseButton(WM_RBUTTONUP, e.GetX(), e.GetY());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnMotion(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseMove(e.GetX(), e.GetY(), e.Dragging());
	}
}
//---------------------------------------------------------------------
void CanvasPanel::OnKeyDown(wxKeyEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		if (e.GetKeyCode() == WXK_ESCAPE)
		{
			GetEditor()->SetActiveTool(NULL);
		}

		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnKeyDown(e.GetRawKeyCode());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnKeyUp(wxKeyEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnKeyUp(e.GetRawKeyCode());
	}
}
//---------------------------------------------------------------------
void CanvasPanel::OnChar(wxKeyEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnChar(e.GetRawKeyCode());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnMouseWheel(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen() && this->mouseInClient)
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnMouseWheel(e.GetWheelRotation());
	}
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnEnterWindow(wxMouseEvent& e)
{
	SetFocus();

	if (GetEditor()->IsOpen())
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnSetFocus();
	}

	 this->mouseInClient = true;
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnLeaveWindow(wxMouseEvent& e)
{
	if (GetEditor()->IsOpen())
	{
		WindowMessageHandler* msgHandler = GetEditor()->GetWindowMessageHandler();
		msgHandler->OnKillFocus();
	}

	this->mouseInClient = false;
}

//---------------------------------------------------------------------
void 
CanvasPanel::OnToolsSolid(wxCommandEvent& e)
{
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnToolsWireframe(wxCommandEvent& e)
{
}
//---------------------------------------------------------------------
void 
CanvasPanel::OnToolsPoints(wxCommandEvent& e)
{
}

}; // namespace Tools