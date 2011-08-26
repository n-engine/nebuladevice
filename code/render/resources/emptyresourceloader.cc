//------------------------------------------------------------------------------
//  emptyresourceloader.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "emptyresourceloader.h"

namespace Resources
{
__ImplementClass(Resources::EmptyResourceLoader, 'EMRL', Resources::ResourceLoader);

//------------------------------------------------------------------------------
/**    
*/
bool
EmptyResourceLoader::OnLoadRequested()
{
    return true;
}

} // end Resources