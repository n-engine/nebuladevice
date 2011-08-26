//------------------------------------------------------------------------------
//  selectentitymanip.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "entitypicktool.h"
#include "input/inputserver.h"
#include "input/mouse.h"
#include "basegamefeature/managers/entitymanager.h"
#include "basegamefeature/managers/factorymanager.h"
#include "basegamefeature/managers/envquerymanager.h"
#include "basegamefeature/managers/focusmanager.h"
#include "basegameattr/basegameattributes.h"
#include "graphicsattr/graphicsattributes.h"
#include "physicsattr/physicsattributes.h"
#include "basegamefeature/basegameprotocol.h"



namespace Editor
{
__ImplementClass(Editor::EntityPickTool, 'ESMP', Editor::EditTool);


using namespace Input;
using namespace Game;
using namespace BaseGameFeature;

//------------------------------------------------------------------------------
/**
*/
EntityPickTool::EntityPickTool()
: entity(0)
{

}

//------------------------------------------------------------------------------
/**
*/
EntityPickTool::~EntityPickTool()
{

}

//------------------------------------------------------------------------------
/**
*/
void 
EntityPickTool::OnActivate()
{
	FocusManager::Instance()->SetInputFocusType(FocusManager::Select);
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityPickTool::OnDeactivate()
{
	if (this->entity)
	{
		this->entity = 0;
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityPickTool::OnUpdate()
{
	InputServer* inputServer = InputServer::Instance();
	const Ptr<Mouse>& mouse = inputServer->GetDefaultMouse();

	if (mouse->ButtonDown(MouseButton::LeftButton))
	{
		Entity* ent = EnvQueryManager::Instance()->GetEntityUnderMouse();

		if (ent != this->entity)
		{
			this->entity = ent;
			FocusManager::Instance()->SetInputFocusEntity(this->entity);
		}
	} 
}


} // namespace Editor