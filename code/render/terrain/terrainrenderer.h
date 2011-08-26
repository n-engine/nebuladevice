#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainRenderer

	(C) 2011 xiongyouyi
*/
#if __WIN32__
#include "terrain/d3d9/d3d9terrainrenderer.h"

namespace Terrain
{
class TerrainRenderer : public Direct3D9::D3D9TerrainRenderer
{
	__DeclareClass(TerrainRenderer);
	__DeclareSingleton(TerrainRenderer);
public:
	/// constructor
	TerrainRenderer();
	/// destructor
	virtual ~TerrainRenderer();
};
}
#endif