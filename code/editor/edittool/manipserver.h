#pragma once
//------------------------------------------------------------------------------
/**
	@class Editor::ManipServer

	Manip子系统的核心控制类。

	(C) 2011 xiongyouyi
*/
#include "core/singleton.h"
#include "manip.h"

//------------------------------------------------------------------------------
namespace Editor
{
class ManipServer : public Core::RefCounted
{
	__DeclareClass(ManipServer);
	__DeclareSingleton(ManipServer);
public:
	ManipServer();
	virtual ~ManipServer();

	/// 打开子系统
	virtual bool Open();
	/// 关闭子系统
	virtual void Close();
	// 子系统是否已打开
	bool IsOpen() const;

	/// 帧渲染前调用
	void OnBeginFrame();
	/// 帧渲染后调用
	void OnEndFrame();

	/// 注册Manip
	virtual void RegisterManip(const Util::String& name, const Ptr<Manip>& Manip);
	/// 注销Manip
	virtual void UnregisterManip(const Util::String& name);

	/// Manip是否存在
	bool HasManip(const Util::String& name) const;
	/// 通过名字取得Manip
	Ptr<Manip> GetManip(const Util::String& name);

	/// 设置当前Manip
	void SetActiveManip(const Util::String& name);
	void SetActiveManip(Ptr<Manip> Manip);
	/// 取得当前Manip
	Ptr<Manip> GetActiveManip();

protected:
	/// register manips
	void RegisterManips();

private:
	bool			isOpen;
	Ptr<Manip>		activeManip;
	Util::Dictionary<Util::String, Ptr<Manip> > manipRegistry;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
ManipServer::IsOpen() const
{
	return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
inline
Ptr<Manip>
ManipServer::GetActiveManip()
{
	return this->activeManip;
}

} // namespace Editor