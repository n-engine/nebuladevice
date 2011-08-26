//------------------------------------------------------------------------------
//  TerrainNodeinstance.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrainnodeInstance.h"
#include "terrain/terrainrenderer.h"
#include "coregraphics/renderdevice.h"
#include "models/nodes/transformnode.h"


namespace Terrain
{
__ImplementClass(Terrain::TerrainNodeInstance, 'TENI', Models::StateNodeInstance);


using namespace Models;
using namespace CoreGraphics;


//------------------------------------------------------------------------------
/**
*/
TerrainNodeInstance::TerrainNodeInstance()
{
 
}

//------------------------------------------------------------------------------
/**
*/
TerrainNodeInstance::~TerrainNodeInstance()
{

}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNodeInstance::OnVisibilityResolve(IndexT resolveIndex, float distanceToViewer)
{
	// check if node is inside lod distances or if no lod is used
	const Ptr<TransformNode>& transformNode = this->modelNode.downcast<TransformNode>();
	if (transformNode->CheckLodDistance(distanceToViewer))
	{
		this->modelNode->AddVisibleNodeInstance(resolveIndex, this);
		ModelNodeInstance::OnVisibilityResolve(resolveIndex, distanceToViewer);
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNodeInstance::Render()
{
	StateNodeInstance::Render();
	RenderDevice::Instance()->Draw();
}

//------------------------------------------------------------------------------
/**
*/
//void 
//TerrainNodeInstance::Setup(const Ptr<Models::ModelInstance>& inst, const Ptr<Models::ModelNode>& node, const Ptr<Models::ModelNodeInstance>& parentNodeInst)
//{
//
//}

//------------------------------------------------------------------------------
/**
*/
//void 
//TerrainNodeInstance::Discard()
//{
//
//}

//------------------------------------------------------------------------------
/**
*/
//void
//TerrainNodeInstance::RenderDebug()
//{
//
//}

} // namespace Terrain