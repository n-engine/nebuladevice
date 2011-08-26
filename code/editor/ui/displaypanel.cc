//------------------------------------------------------------------------------
//  displaypanel.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "displaypanel.h"
#include "wx/wx.h"



namespace Editor
{

/*!
 * DisplayPanel type definition
 */
IMPLEMENT_DYNAMIC_CLASS( DisplayPanel, wxScrolledWindow )


/*!
 * DisplayPanel event table definition
 */
BEGIN_EVENT_TABLE( DisplayPanel, wxScrolledWindow )


END_EVENT_TABLE()


/*!
 * DisplayPanel constructors
 */
DisplayPanel::DisplayPanel()
{
    Init();
}

DisplayPanel::DisplayPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}


/*!
 * DisplayPanel creator
 */
bool DisplayPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
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
 * DisplayPanel destructor
 */
DisplayPanel::~DisplayPanel()
{
}


/*!
 * Member initialisation
 */
void DisplayPanel::Init()
{
}


/*!
 * Control creation for DisplayPanel
 */
void DisplayPanel::CreateControls()
{    
    DisplayPanel* itemScrolledWindow1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemScrolledWindow1->SetSizer(itemBoxSizer2);

}


} // namespace Editor