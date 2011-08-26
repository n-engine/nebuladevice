//------------------------------------------------------------------------------
//  editorapplication.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "editorapplication.h"
#include "basegamefeature/statehandlers/gamestatehandler.h"
#include "basegamefeature/basegamefeatureunit.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "appgame/statehandler.h"
#include "game/entity.h"
#include "attr/attribute.h"
#include "properties/mayacameraproperty.h"
#include "debugrender/debugrender.h"



namespace Editor
{
using namespace BaseGameFeature;
using namespace Graphics;
using namespace Math;
using namespace Util;
using namespace Resources;
using namespace Timing;
using namespace GraphicsFeature;


__ImplementSingleton(EditorApplication);   
//------------------------------------------------------------------------------
/**
*/
EditorApplication::EditorApplication()
: graphicsFeature(0)
, baseGameFeature(0)
, windowMsgHandler(0)
, activeEditTool(0)
{
    __ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
EditorApplication::~EditorApplication()
{
    if (this->IsOpen())
    {
        this->Close();
    }
	__DestructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void 
EditorApplication::SetupStateHandlers()
{
    // create our standard gamestatehandler
    Ptr<GameStateHandler> gameState = GameStateHandler::Create();
    gameState->SetSetupMode(GameStateHandler::NewGame);
    gameState->SetName("GameState");
    gameState->SetLevelName("testlevel");
    
    this->AddStateHandler(gameState.get());

    this->SetState("GameState");
}

//------------------------------------------------------------------------------
/**
*/
void
EditorApplication::SetupGameFeatures()
{
    GameApplication::SetupGameFeatures();

    // create and attach default graphic features
    this->graphicsFeature = GraphicsFeature::GraphicsFeatureUnit::Create();
    this->graphicsFeature->SetCmdLineArgs(this->GetCmdLineArgs());
    this->graphicsFeature->SetRenderDebug(true);
    this->gameServer->AttachGameFeature(this->graphicsFeature.cast<Game::FeatureUnit>());

    // game features
    this->baseGameFeature = BaseGameFeature::BaseGameFeatureUnit::Create();
	this->baseGameFeature->SetRenderDebug(true);
    this->gameServer->AttachGameFeature(this->baseGameFeature.upcast<Game::FeatureUnit>());

#if __USE_PHYSICS__
	// create and attach core features
	this->physicsFeature = PhysicsFeature::PhysicsFeatureUnit::Create();    
	this->gameServer->AttachGameFeature(this->physicsFeature.upcast<Game::FeatureUnit>());
#endif	
}

//------------------------------------------------------------------------------
/**
    Cleanup all added game features
*/
void
EditorApplication::CleanupGameFeatures()
{    
    this->gameServer->RemoveGameFeature(this->baseGameFeature.upcast<Game::FeatureUnit>());  
    this->baseGameFeature = 0;
    this->gameServer->RemoveGameFeature(this->graphicsFeature.upcast<Game::FeatureUnit>());
    this->graphicsFeature = 0;

#if __USE_PHYSICS__
	this->gameServer->RemoveGameFeature(this->physicsFeature.upcast<Game::FeatureUnit>());
	this->physicsFeature = 0;
#endif

    GameApplication::CleanupGameFeatures();
}

//------------------------------------------------------------------------------
/**
*/
bool 
EditorApplication::Open()
{
	n_assert(this->GetCmdLineArgs().HasArg("-externalwindow"));

    bool ret = App::GameApplication::Open();

	HWND hwnd = (HWND)(this->GetCmdLineArgs().GetInt("-externalwindow"));
	this->windowMsgHandler = new WindowMessageHandler(hwnd);

    return ret;
}

//------------------------------------------------------------------------------
/**
*/
void 
EditorApplication::Close()
{
	App::GameApplication::Close();
}

//------------------------------------------------------------------------------
/**
	begin update
*/
void
EditorApplication::BeginUpdate()
{
	GraphicsInterface::Instance()->EnterLockStepMode();
}

//------------------------------------------------------------------------------
/**
	update one frame
*/
void 
EditorApplication::UpdateOneFrame()
{
	if (this->GetCurrentState() != "Exit")
	{
		_start_timer(GameApplicationFrameTimeAll);

#if __NEBULA3_HTTP__
		this->httpServerProxy->HandlePendingRequests(); 
		this->remoteControlProxy->HandlePendingCommands();
#endif

		this->coreServer->Trigger();

		if (this->activeEditTool != NULL)
		{
			this->activeEditTool->OnUpdate();
		}

		// first trigger our game server, which triggers all game features
		this->gameServer->OnFrame();

		String curState = this->GetCurrentState();
		Ptr<App::StateHandler> curStateHandler;
		String newState;
		if (curState.IsValid())
		{                                               
			// call the current state handler
			curStateHandler = this->FindStateHandlerByName(curState);
			n_assert(curStateHandler);
			newState = curStateHandler->OnFrame(); 
		}

		// call the app's Run() method
		Application::Run();

		// a requested state always overrides the returned state
		if (this->requestedState.IsValid())
		{
			this->SetState(this->requestedState);
		}
		else if (newState.IsValid() && newState != curStateHandler->GetName())
		{
			// a normal state transition
			this->SetState(newState);
		}

		_stop_timer(GameApplicationFrameTimeAll);
	}
}

//------------------------------------------------------------------------------
/**
	end update
*/
void
EditorApplication::EndUpdate()
{
	GraphicsInterface::Instance()->LeaveLockStepMode();
	this->SetState("Exit");
}

//------------------------------------------------------------------------------
/**
*/
Ptr<EditTool>
EditorApplication::GetEditTool(const Util::String& className)
{
	Ptr<EditTool> tool = NULL;

	String name(className);
	if (className.FindStringIndex("Editor::", 0) == InvalidIndex)
	{
		name = "Editor::" + name;
	}

	if (Core::Factory::Instance()->ClassExists(name))
	{
		tool = (EditTool*)Core::Factory::Instance()->Create(name);
	}

	return tool;
}

//------------------------------------------------------------------------------
/**
*/
void
EditorApplication::SetActiveTool(const Ptr<EditTool>& tool)
{
	if (this->activeEditTool == tool)
	{
		return;
	}

	if (this->activeEditTool != NULL)
	{
		this->activeEditTool->OnDeactivate();
	}

	this->activeEditTool = tool;

	if (this->activeEditTool != NULL)
	{
		this->activeEditTool->OnActivate();
	}
}

} // namespace Tools
