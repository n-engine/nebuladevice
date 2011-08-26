#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainNodeInstance

	表示一个地形块实例

	(C) 2011 xiongyouyi
*/
#include "models/nodes/statenodeinstance.h"


//------------------------------------------------------------------------------
namespace Terrain
{
class TerrainNodeInstance : public Models::StateNodeInstance
{
	__DeclareClass(TerrainNodeInstance);
public:
	/// constructor
	TerrainNodeInstance();
	/// destructor
	virtual ~TerrainNodeInstance();

	/// called during visibility resolve
	virtual void OnVisibilityResolve(IndexT resolveIndex, float distanceToViewer);
	/// perform rendering
	virtual void Render();

protected:
	/// called when attached to ModelInstance
	//virtual void Setup(const Ptr<Models::ModelInstance>& inst, const Ptr<Models::ModelNode>& node, const Ptr<Models::ModelNodeInstance>& parentNodeInst);
	/// called when removed from ModelInstance
	//virtual void Discard();
	/// render node specific debug shape
	//virtual void RenderDebug();
private:
};

} // namespace Terrain