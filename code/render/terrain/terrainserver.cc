//------------------------------------------------------------------------------
//  terrainserver.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrainserver.h"


namespace Terrain
{
__ImplementClass(Terrain::TerrainServer, 'TERS', Core::RefCounted);
__ImplementSingleton(Terrain::TerrainServer);

//------------------------------------------------------------------------------
/**
*/
TerrainServer::TerrainServer():
	isOpen(false)
{
	__ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
TerrainServer::~TerrainServer()
{
	if (this->IsOpen())
	{
		this->Close();
	}

	 __DestructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
TerrainServer::Open()
{
	n_assert(!this->IsOpen())
	this->isOpen = true;

	this->terrainRenderer = TerrainRenderer::Create();
	this->terrainRenderer->Setup();
}

//------------------------------------------------------------------------------
/**
*/
void
TerrainServer::Close()
{
	n_assert(this->IsOpen());

	this->terrainRenderer->Discard();
	this->terrainRenderer = 0;

	this->isOpen = false;
}

} // namespace Terrain
