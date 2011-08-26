//------------------------------------------------------------------------------
//  createpanel.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "createpanel.h"
#include "editorapp.h"
#include "canvaspanel.h"
#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "util/string.h"
#include "util/array.h"
#include "io/ioserver.h"
#include "../edittool/entitycreatetool.h"
#include "../app/editorapplication.h"



namespace Editor
{
using namespace IO;
using namespace Util;
using namespace Editor;


// control identifiers
const long ID_CREATE_MODEL = wxNewId();
const long ID_BROWSER_TREE = wxNewId();

/*!
 * CreatePanel type definition
 */
IMPLEMENT_DYNAMIC_CLASS( CreatePanel, wxScrolledWindow )


/*!
 * CreatePanel event table definition
 */
BEGIN_EVENT_TABLE( CreatePanel, wxScrolledWindow )
EVT_TOGGLEBUTTON(ID_CREATE_MODEL, CreatePanel::OnButtonModel)
EVT_TREE_ITEM_ACTIVATED(ID_BROWSER_TREE, CreatePanel::OnTreeItemActivated)
EVT_TREE_BEGIN_DRAG(ID_BROWSER_TREE, CreatePanel::OnBeginDrag)
EVT_TREE_END_DRAG(ID_BROWSER_TREE, CreatePanel::OnEndDrag)
END_EVENT_TABLE()


/*!
 * CreatePanel constructors
 */
CreatePanel::CreatePanel()
{
    Init();
}

CreatePanel::CreatePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*!
 * CreatePanel creator
 */
bool CreatePanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    wxScrolledWindow::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();

	return true;
}


/*!
 * CreatePanel destructor
 */
CreatePanel::~CreatePanel()
{
}


/*!
 * Member initialisation
 */
void CreatePanel::Init()
{
}


/*!
 * Control creation for CreatePanel
 */
void CreatePanel::CreateControls()
{    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);

	CreateObjectType();

	CreateBrowser();

	mainSizer->Layout();
}

void CreatePanel::CreateObjectType()
{
	wxSizer* mainSizer = GetSizer();

	wxStaticBox* stbox = new wxStaticBox(this, wxID_ANY, _("Object Type"));
	this->objectTypeSizer = new wxStaticBoxSizer(stbox, wxVERTICAL);
	mainSizer->Add(this->objectTypeSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxGridSizer* gridSizer = new wxGridSizer(3, 2, 0, 0);
	objectTypeSizer->Add(gridSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxToggleButton* modelBtn = new wxToggleButton( this, ID_CREATE_MODEL, _("Model"), wxDefaultPosition, wxSize(95, -1), 0 );
	gridSizer->Add(modelBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxToggleButton* lightBtn = new wxToggleButton( this, wxID_ANY, _("Light"), wxDefaultPosition, wxSize(95, -1), wxNO_BORDER);
	gridSizer->Add(lightBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxToggleButton* cameraBtn = new wxToggleButton( this, wxID_ANY, _("Camera"), wxDefaultPosition, wxSize(95, -1) );
	gridSizer->Add(cameraBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxToggleButton* waterBtn = new wxToggleButton( this, wxID_ANY, _("Water"), wxDefaultPosition, wxSize(95, -1) );
	gridSizer->Add(waterBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxToggleButton* aiBtn = new wxToggleButton( this, wxID_ANY, _("AI"), wxDefaultPosition, wxSize(95, -1) );
	gridSizer->Add(aiBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxToggleButton* particleBtn = new wxToggleButton( this, wxID_ANY, _("Particle"), wxDefaultPosition, wxSize(95, -1) );
	gridSizer->Add(particleBtn, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
}

void CreatePanel::CreateBrowser()
{
	wxSizer* mainSizer = GetSizer();

	wxStaticBox* stbox = new wxStaticBox(this, wxID_ANY, _("Browser"));
	this->browserSizer = new wxStaticBoxSizer(stbox, wxVERTICAL);
	mainSizer->Add(this->browserSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	this->browserTree = new wxTreeCtrl( this, ID_BROWSER_TREE, wxDefaultPosition, wxSize(200, 350), wxTR_NO_BUTTONS|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_SINGLE );
	this->browserSizer->Add(this->browserTree, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* filterSizer = new wxBoxSizer(wxHORIZONTAL);
	this->browserSizer->Add(filterSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* filterStatic = new wxStaticText( this, wxID_ANY, _("Filter:"), wxDefaultPosition, wxDefaultSize, 0 );
	filterSizer->Add(filterStatic, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* filterText = new wxTextCtrl( this, wxID_ANY, _T(""), wxDefaultPosition, wxSize(145, -1), 0 );
	filterSizer->Add(filterText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxBitmap( wxT("./res/folder_page.png"), wxBITMAP_TYPE_PNG));
	imglist->Add(wxBitmap( wxT("./res/page_lightning.png"), wxBITMAP_TYPE_PNG));
	this->browserTree->AssignImageList(imglist);

	this->browserTree->AddRoot("root");

	this->browserSizer->Show(false);
}

void CreatePanel::OnButtonModel(wxCommandEvent& event)
{
	wxTreeItemId root = this->browserTree->GetRootItem();
	Array<String> dirs = IO::IoServer::Instance()->ListDirectories("export:models", "*");

	for (int i = 0; i < dirs.Size(); ++i)
	{
		wxTreeItemId itemId = this->browserTree->AppendItem(root, dirs[i].AsCharPtr(), 0);
		Array<String> files = IO::IoServer::Instance()->ListFiles("export:models/" + dirs[i], "*.n3");

		for (int j = 0; j < files.Size(); ++j)
		{
			this->browserTree->AppendItem(itemId, files[j].AsCharPtr(), 1);
		}
	}

	this->browserSizer->Show(event.IsChecked());
	this->GetSizer()->Layout();
}

void CreatePanel::OnTreeItemActivated(wxTreeEvent& e)
{
	if (this->browserTree->ItemHasChildren(e.GetItem()))
	{
		if (this->browserTree->IsExpanded(e.GetItem()))
		{
			this->browserTree->Collapse(e.GetItem());
		} 
		else
		{
			this->browserTree->Expand(e.GetItem());
		}
	}
}

void CreatePanel::OnBeginDrag(wxTreeEvent& e)
{
	if (!this->browserTree->ItemHasChildren(e.GetItem()))
	{
		this->draggedItem = e.GetItem();
		e.Allow();
	}
}

void CreatePanel::OnEndDrag(wxTreeEvent& e)
{
	if (!this->draggedItem.IsOk())
	{
		return;
	}

	CanvasPanel* canvas = ((EditorApp*)wxTheApp)->GetMainFrame()->GetCanvas();

	int x = 0, y = 0;
	wxGetMousePosition(&x, &y);
	wxPoint pt = canvas->ScreenToClient(wxPoint(x, y));
	
	wxTreeItemId parentId = this->browserTree->GetItemParent(this->draggedItem);	
	if (parentId.IsOk())
	{
		Util::String resName;
		wxString parentText = this->browserTree->GetItemText(parentId);
		wxString itemText = this->browserTree->GetItemText(this->draggedItem);

		resName.Format("%s/%s", parentText.mb_str(), itemText.mb_str());
		resName.TrimRight(".n3");

		Ptr<EntityCreateTool> tool = GetEditor()->GetEditTool("EntityCreateTool").cast<EntityCreateTool>();
		tool->SetResourceId(resName);
		GetEditor()->SetActiveTool(tool.cast<EditTool>());
	}
}

} // namespace Editor