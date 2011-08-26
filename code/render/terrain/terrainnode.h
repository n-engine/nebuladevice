#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainNode

	表示一个Terrain chunk，地形的最小渲染单元，有9*9 + 8*8个顶点组成，两级静态LOD。

	(C) 2011 xiongyouyi
*/
#include "models/nodes/statenode.h"
#include "coregraphics/vertexbuffer.h"


//------------------------------------------------------------------------------
namespace Terrain
{
class TerrainNode : public Models::StateNode
{
	__DeclareClass(TerrainNode);
public:
	/// constructor
	TerrainNode();
	/// destructor
	virtual ~TerrainNode();

	/// create a model node instance
	virtual Ptr<Models::ModelNodeInstance> CreateNodeInstance() const;

	/// begin parsing data tags
	virtual void BeginParseDataTags();
	/// parse data tag (called by loader code)
	virtual bool ParseDataTag(const Util::FourCC& fourCC, const Ptr<IO::BinaryReader>& reader);
	/// finish parsing data tags
	virtual void EndParseDataTags();

	/// apply state shared by all my ModelNodeInstances
	virtual void ApplySharedState(IndexT frameIndex);
	
	/// called when resources should be loaded
	virtual void LoadResources();
	/// called when resources should be unloaded
	virtual void UnloadResources();

protected:
	Ptr<CoreGraphics::VertexBuffer> vertexBuffer;
	IndexT	xTile, zTile;		// tile base coordinate index
	IndexT	xChunk, zChunk;		// chunk base coordinate index
	IndexT	numTextures;		// num of textures
	
	struct TerrainVertex 
	{
		float position[4];
		float normal[3];
		float uv[2];
	};
	TerrainVertex*	vertics;			// temporary vertex buffer, it will deleted after LoadResources
	ubyte*	blendMap;
};

} // namespace Terrain