#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::EditorApp

	main gui application

	(C) 2011 xiongyouyi
*/
#include "wx/wx.h"
#include "mainframe.h"



//------------------------------------------------------------------------------
namespace Editor
{
class EditorApp: public wxApp
{    
    DECLARE_CLASS( EditorApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    EditorApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

	MainFrame* GetMainFrame();

private:
	MainFrame* mainFrame;
};

// Application instance declaration 
DECLARE_APP(EditorApp)

}// namespace Editor