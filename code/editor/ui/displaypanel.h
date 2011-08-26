#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::DisplayPanel

	øÿ÷∆≥°æ∞œ‘ æ

	(C) 2011 xiongyouyi
*/
#include "wx/scrolwin.h"



//------------------------------------------------------------------------------
namespace Editor
{
/*!
 * Control identifiers
 */

/*!
 * DisplayPanel class declaration
 */

class DisplayPanel: public wxScrolledWindow
{    
    DECLARE_DYNAMIC_CLASS( DisplayPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    DisplayPanel();
    DisplayPanel( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL );

    /// Destructor
    ~DisplayPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

};

} // namespace Editor
