#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::CreateEntityManip

	创建实体操作

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
class EntityCreateTool : public EditTool
{
	__DeclareClass(EntityCreateTool);
public:
	EntityCreateTool();
	~EntityCreateTool();

	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnUpdate();

	/// 设置资源ID
	void SetResourceId(const Util::String& name);
protected:
private:
	Util::String		resourceId;
	Game::Entity*		entity;
};


//------------------------------------------------------------------------------
/**
*/
inline
void
EntityCreateTool::SetResourceId(const Util::String& name)
{
	this->resourceId = name;
}

} // namespace Editor