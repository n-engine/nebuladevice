//------------------------------------------------------------------------------
//  editorapp.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "editorapp.h"
#include "../app/editorapplication.h"

namespace Editor
{
/*!
 * Application instance implementation
 */
IMPLEMENT_APP( EditorApp )


/*!
 * EditorApp type definition
 */
IMPLEMENT_CLASS( EditorApp, wxApp )


/*!
 * EditorApp event table definition
 */
BEGIN_EVENT_TABLE( EditorApp, wxApp )

END_EVENT_TABLE()


/*!
 * Constructor for EditorApp
 */
EditorApp::EditorApp()
: mainFrame(0)
{
    Init();
}


/*!
 * Member initialisation
 */
void EditorApp::Init()
{
	new Editor::EditorApplication();
	GetEditor()->SetAppTitle("Nebula3 Editor");
}

/*!
 * Initialisation for EditorApp
 */
bool EditorApp::OnInit()
{    

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif

	this->mainFrame = new MainFrame( NULL );
	this->mainFrame->Show(true);

	this->mainFrame->InitNebula();

    return true;
}


/*!
 * Cleanup for EditorApp
 */
int EditorApp::OnExit()
{

	GetEditor()->Exit();
	delete GetEditor();

	return wxApp::OnExit();
}

MainFrame* EditorApp::GetMainFrame()
{
	return this->mainFrame;
}

} // namespace Editor