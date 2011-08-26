#pragma once
//------------------------------------------------------------------------------
/**
	@class Resources::EmptyResourceLoader


	(C) 2008 Radon Labs GmbH
*/
#include "resources\resourceloader.h"

namespace Resources 
{
    
class EmptyResourceLoader : public Resources::ResourceLoader
{
    __DeclareClass(EmptyResourceLoader)
public:
    /// set resource state
    void SetState(Resources::Resource::State state);
    /// called by resource when a load is requested
    virtual bool OnLoadRequested();
};
//------------------------------------------------------------------------------
/**
*/
inline void 
EmptyResourceLoader::SetState(Resources::Resource::State state)
{
    this->state  = state; 
}

}
