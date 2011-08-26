#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::EditTool

	操作基类，操作就是编辑器里触发的动作，如创建修改实体、编辑地形等。

	(C) 2011 xiongyouyi
*/
#include "core/refcounted.h"


//------------------------------------------------------------------------------
namespace Editor
{
class EditTool : public Core::RefCounted
{
	__DeclareClass(EditTool);
public:
	EditTool();
	virtual ~EditTool();

	virtual void OnActivate();
	virtual void OnDeactivate();

	virtual void OnUpdate();

	/// 取名字
	const Util::String& GetName() const;

protected:
	friend class ManipServer;

	/// 注册时设置名字
	void SetName(const Util::String& n);

private:
	Util::String name;
};

//------------------------------------------------------------------------------
/**
*/
inline
void
EditTool::SetName(const Util::String& n)
{
	this->name = n;
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::String&
EditTool::GetName() const
{
	return this->name;
}

} // namespace Editor