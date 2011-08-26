//------------------------------------------------------------------------------
//  moveentitymanip.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "entitymovetool.h"
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
__ImplementClass(Editor::EntityMoveTool, 'MEMP', Editor::EditTool);


using namespace Math;
using namespace Input;
using namespace Game;
using namespace BaseGameFeature;

//------------------------------------------------------------------------------
/**
*/
EntityMoveTool::EntityMoveTool()
: entity(0)
{

}

//------------------------------------------------------------------------------
/**
*/
EntityMoveTool::~EntityMoveTool()
{

}

//------------------------------------------------------------------------------
/**
*/
void 
EntityMoveTool::OnActivate()
{
	FocusManager::Instance()->SetInputFocusType(FocusManager::Move);
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityMoveTool::OnDeactivate()
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
EntityMoveTool::OnUpdate()
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

	if (mouse->Dragging() && this->entity)
	{
		point pos = EnvQueryManager::Instance()->GetMousePos3d();
		matrix44 entityTransform = matrix44::translation(pos);

		Ptr<BaseGameFeature::SetTransform> msg = BaseGameFeature::SetTransform::Create();
		msg->SetMatrix(entityTransform);
		this->entity->SendSync(msg.cast<Messaging::Message>());
	}
}


} // namespace Editor