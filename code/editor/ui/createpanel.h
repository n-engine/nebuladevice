#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::CreatePanel

	实体的创建修改

	(C) 2011 xiongyouyi
*/
#include "wx/scrolwin.h"
#include "wx/treectrl.h"


//------------------------------------------------------------------------------
namespace Editor
{

/*!
 * CreatePanel class declaration
 */

class CreatePanel: public wxScrolledWindow
{    
    DECLARE_DYNAMIC_CLASS( CreatePanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CreatePanel();
    CreatePanel( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, 
		long style = wxTAB_TRAVERSAL );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, 
		long style = wxTAB_TRAVERSAL );

    /// Destructor
    ~CreatePanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void CreateObjectType();

	void CreateBrowser();

	void OnButtonModel(wxCommandEvent& e);
	void OnTreeItemActivated(wxTreeEvent& e);
	void OnBeginDrag(wxTreeEvent& e);
	void OnEndDrag(wxTreeEvent& e);

private:

	wxSizer*	objectTypeSizer;
	wxSizer*	browserSizer;

	wxTreeCtrl*		browserTree;
	wxTreeItemId	draggedItem;
};


} // namespace Editor