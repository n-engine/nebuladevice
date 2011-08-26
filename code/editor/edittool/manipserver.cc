//------------------------------------------------------------------------------
//  manipserver.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "manipserver.h"
#include "input/keyboard.h"
#include "input/inputserver.h"
#include "selectentitymanip.h"
#include "moveentitymanip.h"
#include "rotateentitymanip.h"
#include "createentitymanip.h"



namespace Editor
{
__ImplementClass(Editor::ManipServer, 'EACS', Core::RefCounted);
__ImplementSingleton(Editor::ManipServer);

using namespace Input;

//------------------------------------------------------------------------------
/**
*/
ManipServer::ManipServer():
isOpen(false),
activeManip(0)
{
	__ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
ManipServer::~ManipServer()
{
	n_assert(!this->isOpen);
	__DestructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
bool
ManipServer::Open()
{
	n_assert(!this->isOpen);
	this->isOpen = true;

	//RegisterManips();

	return true;
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::Close()
{
	n_assert(this->isOpen);
	while (!this->manipRegistry.IsEmpty())
	{
		this->UnregisterManip(this->manipRegistry.KeyAtIndex(0));
	}
	this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::OnBeginFrame()
{
	const Ptr<InputServer>& inputServer = InputServer::Instance();
	const Ptr<Keyboard>& keyboard = inputServer->GetDefaultKeyboard();

	if (keyboard.isvalid())
	{
		if (keyboard->KeyDown(Key::Escape))
		{
			this->SetActiveManip("selectentitymanip");
		} 
		else if (keyboard->KeyDown(Key::M))
		{
			this->SetActiveManip("moveentitymanip");
		}
		else if (keyboard->KeyDown(Key::R))
		{
			this->SetActiveManip("rotateentitymanip");
		}
	}

	if (this->activeManip.isvalid())
	{
		this->activeManip->OnBeginFrame();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::OnEndFrame()
{
	if (this->activeManip.isvalid())
	{
		this->activeManip->OnEndFrame();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::RegisterManip(const Util::String& name, const Ptr<Manip>& Manip)
{
	n_assert(this->isOpen);
	n_assert(name.IsValid());
	n_assert(!this->manipRegistry.Contains(name));
	n_assert(Manip.isvalid());

	this->manipRegistry.Add(name, Manip);
	Manip->SetName(name);
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::UnregisterManip(const Util::String& name)
{
	n_assert(this->isOpen);
	n_assert(name.IsValid());
	n_assert(this->manipRegistry.Contains(name));

	this->manipRegistry.Erase(name);
}

//------------------------------------------------------------------------------
/**
*/
bool
ManipServer::HasManip(const Util::String& name) const
{
	return this->manipRegistry.Contains(name);
}

//------------------------------------------------------------------------------
/**
*/
Ptr<Manip>
ManipServer::GetManip(const Util::String& name)
{
	return this->manipRegistry[name];
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::SetActiveManip(const Util::String& name)
{
	n_assert(this->isOpen);

	if (!this->manipRegistry.Contains(name))
	{
		if (this->activeManip.isvalid())
		{
			this->activeManip->OnDeactivate();
		}

		this->activeManip = 0;
	}
	else if (this->activeManip != this->manipRegistry[name])
	{
		if (this->activeManip.isvalid())
		{
			this->activeManip->OnDeactivate();
		}

		this->activeManip = this->manipRegistry[name];
		this->activeManip->OnActivate();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
ManipServer::SetActiveManip(Ptr<Manip> Manip)
{
	n_assert(this->isOpen);

	if (!Manip.isvalid())
	{
		if (this->activeManip.isvalid())
		{
			this->activeManip->OnDeactivate();
		}

		this->activeManip = 0;
	}
	else if (this->activeManip != Manip)
	{
		if (this->activeManip.isvalid())
		{
			this->activeManip->OnDeactivate();
		}

		this->activeManip = Manip;
		this->activeManip->OnActivate();
	}
}

//------------------------------------------------------------------------------
/**
	register manips
*/
void 
ManipServer::RegisterManips()
{
	this->RegisterManip("selectentitymanip", SelectEntityManip::Create());
	this->RegisterManip("moveentitymanip",   MoveEntityManip::Create());
	this->RegisterManip("rotateentitymanip", RotateEntityManip::Create());
	this->RegisterManip("createentitymanip", CreateEntityManip::Create());

	this->SetActiveManip("selectentitymanip");
}

} // namespace Editor