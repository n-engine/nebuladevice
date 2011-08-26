#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::TerrainPanel

	地形相关的操作

	(C) 2011 xiongyouyi
*/
#include "wx/scrolwin.h"



//------------------------------------------------------------------------------
namespace Editor
{
/*!
 * TerrainPanel class declaration
 */
class TerrainPanel: public wxScrolledWindow
{    
    DECLARE_DYNAMIC_CLASS( TerrainPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    TerrainPanel();
    TerrainPanel( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, 
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL );

    /// Destructor
    ~TerrainPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

};

} // namespace Editor
