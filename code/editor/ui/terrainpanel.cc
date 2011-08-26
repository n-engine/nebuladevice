//------------------------------------------------------------------------------
//  terrainpanel.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrainpanel.h"
#include "wx/wx.h"



namespace Editor
{

/*!
 * TerrainPanel type definition
 */
IMPLEMENT_DYNAMIC_CLASS( TerrainPanel, wxScrolledWindow )


/*!
 * TerrainPanel event table definition
 */
BEGIN_EVENT_TABLE( TerrainPanel, wxScrolledWindow )


END_EVENT_TABLE()


/*!
 * TerrainPanel constructors
 */
TerrainPanel::TerrainPanel()
{
    Init();
}

TerrainPanel::TerrainPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*!
 * TerrainPanel creator
 */
bool TerrainPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
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
 * TerrainPanel destructor
 */
TerrainPanel::~TerrainPanel()
{

}


/*!
 * Member initialisation
 */
void TerrainPanel::Init()
{

}


/*!
 * Control creation for TerrainPanel
 */
void TerrainPanel::CreateControls()
{    
    TerrainPanel* itemScrolledWindow1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow1->SetSizer(itemBoxSizer2);

}

} // namespace Editor