#pragma once
//------------------------------------------------------------------------------
/**
    @class Editor::EditorApplication
    
    editor application

    (C) 2011 xiongyouyi
*/
#include "appgame/gameapplication.h"
#include "basegamefeature/basegamefeatureunit.h"
#include "foundation/framesync/framesynctimer.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "../util/windowmessagehandler.h"
#include "../edittool/edittool.h"


#if __USE_PHYSICS__
#include "physicsfeature/physicsfeatureunit.h"
#include "stateobjectfeature/stateobjectfeatureunit.h"
#endif


//------------------------------------------------------------------------------
namespace Editor
{
#define GetEditor() (EditorApplication::Instance())

class EditorApplication : public App::GameApplication
{
    __DeclareSingleton(EditorApplication);   
public:
    /// constructor
    EditorApplication();
    /// destructor
    virtual ~EditorApplication();
    
    /// open the application
    virtual bool Open();
	/// close the application
	virtual void Close();

	// begin update
	void BeginUpdate();
	
	// update one frame
	void UpdateOneFrame();

	// end update
	void EndUpdate();

	Ptr<EditTool> GetEditTool(const Util::String& className);

	void SetActiveTool(const Ptr<EditTool>& tool);

	Ptr<EditTool> GetActiveTool();

	// get window message handler
	WindowMessageHandler* GetWindowMessageHandler();

protected:
    /// setup application state handlers
    virtual void SetupStateHandlers();
    /// setup game features
    virtual void SetupGameFeatures();
    /// cleanup game features
    virtual void CleanupGameFeatures();        

private: 
#if __USE_PHYSICS__    
	Ptr<PhysicsFeature::PhysicsFeatureUnit>	  physicsFeature;
#endif  

    Ptr<GraphicsFeature::GraphicsFeatureUnit> graphicsFeature;
    Ptr<BaseGameFeature::BaseGameFeatureUnit> baseGameFeature;
	WindowMessageHandler*					  windowMsgHandler;

	Util::Dictionary<Util::String, Ptr<EditTool> > editToolRegistry;
	Ptr<EditTool>	activeEditTool;
};

//------------------------------------------------------------------------------
/**
	get window message handler
*/
inline WindowMessageHandler*
EditorApplication::GetWindowMessageHandler()
{
	return this->windowMsgHandler;
}

//------------------------------------------------------------------------------
/**
*/
inline Ptr<EditTool>
EditorApplication::GetActiveTool()
{
	return this->activeEditTool;
}

} // namespace Test
//------------------------------------------------------------------------------