#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::EntityPickTool

	选择对象操作

	(C) 2011 xiongyouyi
*/
#include "edittool.h"

namespace Game
{
	class Entity;
};


//------------------------------------------------------------------------------
namespace Editor
{
class EntityPickTool : public EditTool
{
	__DeclareClass(EntityPickTool);
public:
	EntityPickTool();
	~EntityPickTool();

	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnUpdate();

protected:
	Game::Entity*	entity;
};


} // namespace Editor