#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::MainFrame

	main frame

	(C) 2011 xiongyouyi
*/
#include "wx/aui/framemanager.h"
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/notebook.h"
#include "wx/flatnotebook/wxFlatNotebook.h"


//------------------------------------------------------------------------------
namespace Editor
{

class CanvasPanel;

/*!
 * MainFrame class declaration
 */

class MainFrame: public wxFrame
{    
    DECLARE_CLASS( MainFrame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxString& caption = _("Nebula3 Editor"), 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxSize(1024, 768), 
		long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX );

    /// Destructor
    ~MainFrame();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Returns the AUI manager object
    wxAuiManager& GetAuiManager() { return this->auiManager; }

	void InitNebula();

	CanvasPanel* GetCanvas();

private :
    wxAuiManager auiManager;
	wxFlatNotebookImageList	 bookImageList;
	CanvasPanel* canvasPanel;
};


} // namespace Editor
