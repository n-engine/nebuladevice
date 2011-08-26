//------------------------------------------------------------------------------
//  rotateentitymanip.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "entityrotatetool.h"
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
__ImplementClass(Editor::EntityRotateTool, 'REMP', Editor::EditTool);


using namespace Input;
using namespace Game;
using namespace BaseGameFeature;

//------------------------------------------------------------------------------
/**
*/
EntityRotateTool::EntityRotateTool()
: entity(0)
{

}

//------------------------------------------------------------------------------
/**
*/
EntityRotateTool::~EntityRotateTool()
{

}

//------------------------------------------------------------------------------
/**
	操作被置为当前
*/
void 
EntityRotateTool::OnActivate()
{
	FocusManager::Instance()->SetInputFocusType(FocusManager::Rotate);
}

//------------------------------------------------------------------------------
/**
	操作被置换
*/
void 
EntityRotateTool::OnDeactivate()
{
	if (this->entity)
	{
		this->entity = 0;
	}
}

//------------------------------------------------------------------------------
/**
	帧渲染前调用
*/
void 
EntityRotateTool::OnUpdate()
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