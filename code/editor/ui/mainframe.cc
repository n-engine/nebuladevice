//------------------------------------------------------------------------------
//  mainframe.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "mainframe.h"
#include "wx/wx.h"
#include "wx/aui/aui.h"
#include "createpanel.h"
#include "terrainpanel.h"
#include "displaypanel.h"
#include "CanvasPanel.h"
#include "../app/editorapplication.h"


namespace Editor
{
////@begin control identifiers
#define ID_FILE_NEW 10004
#define ID_FILE_OPEN 10006
#define ID_FILE_SAVE 10007
#define ID_FILE_SAVEAS 10008
#define ID_FILE_EXIT 10009
#define ID_EDIT_UNDO 10005
#define ID_EDIT_REDO 10010
#define ID_EDIT_DELETE 10011



////@end control identifiers

/*!
 * MainFrame type definition
 */
IMPLEMENT_CLASS( MainFrame, wxFrame )


/*!
 * MainFrame event table definition
 */
BEGIN_EVENT_TABLE( MainFrame, wxFrame )


END_EVENT_TABLE()


/*!
 * MainFrame constructors
 */
MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
	wxFrame::Create( parent, id, caption, pos, size, style );

	CreateControls();
	SetIcon(wxIcon(_T("NebulaIcon")));
	Centre();
}

/*!
 * MainFrame destructor
 */
MainFrame::~MainFrame()
{
    GetAuiManager().UnInit();
}


/*!
 * Member initialisation
 */
void MainFrame::Init()
{
}


/*!
 * Control creation for MainFrame
 */
void MainFrame::CreateControls()
{    
    GetAuiManager().SetManagedWindow(this);

	// Create menubar
    wxMenuBar* menuBar = new wxMenuBar;

	// file menu
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_FILE_NEW, _("New"), _T(""), wxITEM_NORMAL);
    fileMenu->Append(ID_FILE_OPEN, _("Open"), _T(""), wxITEM_NORMAL);
    fileMenu->Append(ID_FILE_SAVE, _("Save"), _T(""), wxITEM_NORMAL);
    fileMenu->Append(ID_FILE_SAVEAS, _("SaveAs"), _T(""), wxITEM_NORMAL);
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_FILE_EXIT, _("Exit"), _T(""), wxITEM_NORMAL);
    menuBar->Append(fileMenu, _("File"));

	// edit menu
    wxMenu* editMenu = new wxMenu;
    editMenu->Append(ID_EDIT_UNDO, _("Undo"), _T(""), wxITEM_NORMAL);
    editMenu->Append(ID_EDIT_REDO, _("Redo"), _T(""), wxITEM_NORMAL);
    editMenu->AppendSeparator();
    editMenu->Append(ID_EDIT_DELETE, _("Delete"), _T(""), wxITEM_NORMAL);
    menuBar->Append(editMenu, _("Edit"));

    this->SetMenuBar(menuBar);

	// Create main toolbar
    wxToolBar* mainToolbar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER, wxID_ANY );

	mainToolbar->AddTool(ID_FILE_NEW, _T("New"), 
		wxBitmap( wxT("./res/page_world.png"), wxBITMAP_TYPE_PNG), 
		wxEmptyString);
    mainToolbar->AddTool(ID_FILE_OPEN, _T("Open"), 
		wxBitmap( wxT("./res/folder_page.png"), wxBITMAP_TYPE_PNG), 
		wxEmptyString);
	mainToolbar->AddTool(ID_FILE_SAVE, _T("Save"), 
		wxBitmap( wxT("./res/arrow_join.png"), wxBITMAP_TYPE_PNG), 
		wxEmptyString);
	mainToolbar->AddTool(ID_EDIT_UNDO, _T("Undo"), 
		wxBitmap( wxT("./res/arrow_turn_left.png"), wxBITMAP_TYPE_PNG), 
		wxEmptyString);
	mainToolbar->AddTool(ID_EDIT_REDO, _T("Redo"), 
		wxBitmap( wxT("./res/arrow_turn_right.png"), wxBITMAP_TYPE_PNG), 
		wxEmptyString);

    mainToolbar->Realize();
    this->SetToolBar(mainToolbar);


	// Create statusbar
	int fieldsWidth[3]={140, 200, -1};
    wxStatusBar* statusBar = new wxStatusBar( this, wxID_ANY, wxST_SIZEGRIP|wxNO_BORDER );
    statusBar->SetFieldsCount(3, fieldsWidth);
    this->SetStatusBar(statusBar);

	// Create main canvas panel
    this->canvasPanel = new CanvasPanel( this );
    GetAuiManager().AddPane(this->canvasPanel, wxAuiPaneInfo().Centre().CaptionVisible(false).
		CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

	// Create command panel
    wxFlatNotebook* notebook = new wxFlatNotebook( this, wxID_ANY, wxDefaultPosition, wxSize(240, -1), 
		wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG | wxFNB_FF2 | wxFNB_CUSTOM_DLG );
	notebook->SetCustomizeOptions( wxFNB_CUSTOM_TAB_LOOK | wxFNB_CUSTOM_ORIENTATION | wxFNB_CUSTOM_LOCAL_DRAG );
	notebook->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));

	this->bookImageList.Add( wxBitmap(wxT("./res/chart_organisation.png"), wxBITMAP_TYPE_PNG) );
	this->bookImageList.Add( wxBitmap(wxT("./res/shape_square_edit.png"), wxBITMAP_TYPE_PNG) );
	this->bookImageList.Add( wxBitmap(wxT("./res/page_lightning.png"), wxBITMAP_TYPE_PNG) );

	notebook->SetImageList(&this->bookImageList);

	notebook->AddPage(new CreatePanel(notebook, wxID_ANY), "Create", true, 0);
	notebook->AddPage(new TerrainPanel(notebook, wxID_ANY), "Terrain", false, 1);
	notebook->AddPage(new DisplayPanel(notebook, wxID_ANY), "Display", false, 2);
	notebook->Layout();

    GetAuiManager().AddPane(notebook, wxAuiPaneInfo().Right());

	// Set auimanager options
	GetAuiManager().SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG);

    GetAuiManager().Update();
}

//------------------------------------------------------------------------------
/**
*/
void MainFrame::InitNebula()
{
	Util::String cmdline;
	cmdline.Format("-externalwindow %d", ((HWND)this->canvasPanel->GetHWND()));
	Util::CommandLineArgs args(cmdline);

	GetEditor()->SetCmdLineArgs(args);
	GetEditor()->Open();
	GetEditor()->BeginUpdate();
}

//------------------------------------------------------------------------------
/**
*/
CanvasPanel* MainFrame::GetCanvas()
{
	return this->canvasPanel;
}

}