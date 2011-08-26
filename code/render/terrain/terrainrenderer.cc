//------------------------------------------------------------------------------
//  terrainrenderer.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrain/terrainrenderer.h"


namespace Terrain
{
__ImplementClass(Terrain::TerrainRenderer, 'TERR', Core::RefCounted);
__ImplementSingleton(Terrain::TerrainRenderer);


//------------------------------------------------------------------------------
/**
*/
TerrainRenderer::TerrainRenderer()
{
	__ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
TerrainRenderer::~TerrainRenderer()
{
	__DestructSingleton;
}

} // namespace Terrain