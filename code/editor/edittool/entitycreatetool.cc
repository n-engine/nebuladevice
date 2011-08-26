//------------------------------------------------------------------------------
//  createentitymanip.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "entitycreatetool.h"
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
__ImplementClass(Editor::EntityCreateTool, 'CEMP', Editor::EditTool);

using namespace Math;
using namespace Input;
using namespace Game;
using namespace BaseGameFeature;

//------------------------------------------------------------------------------
/**
*/
EntityCreateTool::EntityCreateTool()
: resourceId("")
, entity(0)
{
}

//------------------------------------------------------------------------------
/**
*/
EntityCreateTool::~EntityCreateTool()
{
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityCreateTool::OnActivate()
{
	FocusManager::Instance()->SetInputFocusType(FocusManager::Select);
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityCreateTool::OnDeactivate()
{
	if (this->entity)
	{
		// 取消添加实体
		FocusManager::Instance()->SetInputFocusEntity(0);
		EntityManager::Instance()->DeleteEntity(this->entity);
		this->entity = 0;
		this->resourceId.Clear();
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
EntityCreateTool::OnUpdate()
{
	InputServer* inputServer = InputServer::Instance();
	const Ptr<Mouse>& mouse = inputServer->GetDefaultMouse();

	// 创建实体
	if (this->resourceId.IsValid())
	{
		EntityManager* entityManager = EntityManager::Instance();
		FactoryManager* factoryManager = FactoryManager::Instance();

		this->entity = factoryManager->CreateEntityByTemplate("Simple", "tiger");

		this->entity->SetString(Attr::_ID, this->resourceId);
		this->entity->SetString(Attr::_Level, "testlevel");
		this->entity->SetString(Attr::Graphics, this->resourceId);
		//this->entity->SetString(Attr::Physics, this->resourceId);

		entityManager->AttachEntity(this->entity);
		this->resourceId.Clear();
		//FocusManager::Instance()->SetInputFocusEntity(this->entity);
	}

	if (this->entity)
	{
		if (mouse->ButtonDown(MouseButton::LeftButton))
		{
			this->entity = 0;
		} 
		else
		{
			// 让实体跟随鼠标
			//point pos = EnvQueryManager::Instance()->GetMousePos3d();
			//matrix44 entityTransform = matrix44::translation(pos);

			//Ptr<BaseGameFeature::SetTransform> msg = BaseGameFeature::SetTransform::Create();
			//msg->SetMatrix(entityTransform);
			//this->entity->SendSync(msg.cast<Messaging::Message>());
		}
	}
}

} // namespace Editor