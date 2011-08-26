#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainRenderer

	(C) 2011 xiongyouyi
*/
#include "terrain/base/terrainrendererbase.h"
#include "coregraphics/indexbuffer.h"
#include "coregraphics/vertexlayout.h"
#include "coregraphics/primitivegroup.h"


//------------------------------------------------------------------------------
namespace Direct3D9
{
class D3D9TerrainRenderer : public Terrain::TerrainRendererBase
{
	__DeclareClass(D3D9TerrainRenderer);
	__DeclareSingleton(D3D9TerrainRenderer);
public:
	/// constructor
	D3D9TerrainRenderer();
	/// destructor
	virtual ~D3D9TerrainRenderer();

	/// setup the terrain renderer
	virtual void Setup();
	/// discard the terrain renderer
	virtual void Discard();

	/// get vertex layout
	const Ptr<CoreGraphics::VertexLayout>&	GetVertexLayout() const;

	/// get shared index buffer for low and high resolution
	const Ptr<CoreGraphics::IndexBuffer>&	GetIndexBuffer(bool lowLod) const;

	/// get the primintive group
	const CoreGraphics::PrimitiveGroup& GetPrimitiveGroup(bool lowLod) const;

private:
	/// generate the triangle strips
	void Stripify(ushort* lowStrip, ushort* highStrip);

	Ptr<CoreGraphics::VertexLayout> vertexLayout;
	Ptr<CoreGraphics::IndexBuffer>	lowLodIndexBuffer;
	Ptr<CoreGraphics::IndexBuffer>	highLodIndexBuffer;
	CoreGraphics::PrimitiveGroup	lowLodPrimitiveGroup;
	CoreGraphics::PrimitiveGroup	highLodPrimitiveGroup;
};

//------------------------------------------------------------------------------
/**
*/
inline const Ptr<CoreGraphics::VertexLayout>& 
D3D9TerrainRenderer::GetVertexLayout() const
{
	return this->vertexLayout;
}

//------------------------------------------------------------------------------
/**
	get shared index buffer

	@param lowLod [in] ture low resolution, - false high resolution
*/
inline const Ptr<CoreGraphics::IndexBuffer>&	
D3D9TerrainRenderer::GetIndexBuffer(bool lowLod) const
{
	return (lowLod ? this->lowLodIndexBuffer : this->highLodIndexBuffer);
}

//------------------------------------------------------------------------------
/**
	get the primintive group

	@param lowLod [in] ture low resolution, - false high resolution
*/
inline const CoreGraphics::PrimitiveGroup& 
D3D9TerrainRenderer::GetPrimitiveGroup(bool lowLod) const
{
	return (lowLod ? this->lowLodPrimitiveGroup : this->highLodPrimitiveGroup);
}

} // namespace Direct3D9