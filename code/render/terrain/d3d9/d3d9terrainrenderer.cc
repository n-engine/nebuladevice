//------------------------------------------------------------------------------
//  d3d9terrainrenderer.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrain/d3d9/d3d9terrainrenderer.h"
#include "coregraphics/vertexlayoutserver.h"
#include "coregraphics/memoryindexbufferloader.h"



namespace Direct3D9
{
__ImplementClass(Direct3D9::D3D9TerrainRenderer, 'D9TE', Terrain::TerrainRendererBase);
__ImplementSingleton(Direct3D9::D3D9TerrainRenderer);


using namespace Util;
using namespace CoreGraphics;
using namespace Resources;


//------------------------------------------------------------------------------
/**
*/
D3D9TerrainRenderer::D3D9TerrainRenderer()
{
	__ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
D3D9TerrainRenderer::~D3D9TerrainRenderer()
{
	__DestructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void 
D3D9TerrainRenderer::Setup()
{
	n_assert(!this->IsValid());
	n_assert(!this->vertexLayout.isvalid());
	n_assert(!this->lowLodIndexBuffer.isvalid());
	n_assert(!this->highLodIndexBuffer.isvalid());

	Terrain::TerrainRendererBase::Setup();

	// setup a common vertex layout
	Array<VertexComponent> verComponents;
	verComponents.Append(VertexComponent(VertexComponent::Position, 0, VertexComponent::Float4, 0));
	verComponents.Append(VertexComponent(VertexComponent::Normal, 0, VertexComponent::Float3, 0));
	verComponents.Append(VertexComponent(VertexComponent::TexCoord, 0, VertexComponent::Float2, 0));

	this->vertexLayout = VertexLayoutServer::Instance()->CreateSharedVertexLayout(verComponents);

	// create shared index buffer
	ushort* lowStrip = new ushort[LowLodStripSize];
	ushort* highStrip = new ushort[HighLodStripSize];

	Stripify(lowStrip, highStrip);

	Ptr<MemoryIndexBufferLoader> lowIBLoader = MemoryIndexBufferLoader::Create();
	Ptr<MemoryIndexBufferLoader> highIBLoader = MemoryIndexBufferLoader::Create();
	lowIBLoader->Setup(IndexType::Index16, LowLodStripSize, lowStrip, sizeof(ushort) * LowLodStripSize, IndexBuffer::UsageImmutable, IndexBuffer::AccessNone);
	highIBLoader->Setup(IndexType::Index16, HighLodStripSize, highStrip, sizeof(ushort) * HighLodStripSize, IndexBuffer::UsageImmutable, IndexBuffer::AccessNone);

	this->lowLodIndexBuffer = IndexBuffer::Create();
	this->lowLodIndexBuffer->SetLoader(lowIBLoader.upcast<ResourceLoader>());
	this->lowLodIndexBuffer->SetAsyncEnabled(false);
	this->lowLodIndexBuffer->Load();
	if (!this->lowLodIndexBuffer->IsLoaded())
	{
		n_error("D3D9TerrainRenderer: failed to setup low resolution index buffer!");
	}
	this->lowLodIndexBuffer->SetLoader(0);

	this->highLodIndexBuffer = IndexBuffer::Create();
	this->highLodIndexBuffer->SetLoader(highIBLoader.upcast<ResourceLoader>());
	this->highLodIndexBuffer->SetAsyncEnabled(false);
	this->highLodIndexBuffer->Load();
	if (!this->highLodIndexBuffer->IsLoaded())
	{
		n_error("D3D9TerrainRenderer: failed to setup high resolution index buffer!");
	}
	this->highLodIndexBuffer->SetLoader(0);

	delete [] lowStrip;
	delete [] highStrip;

	// setup the primitive group
	this->lowLodPrimitiveGroup.SetBaseVertex(0);
	this->lowLodPrimitiveGroup.SetNumVertices(NumChunkNodeVertices);
	this->lowLodPrimitiveGroup.SetBaseIndex(0);
	this->lowLodPrimitiveGroup.SetNumIndices(LowLodStripSize);
	this->lowLodPrimitiveGroup.SetPrimitiveTopology(PrimitiveTopology::TriangleStrip);

	this->highLodPrimitiveGroup.SetBaseVertex(0);
	this->highLodPrimitiveGroup.SetNumVertices(NumChunkNodeVertices);
	this->highLodPrimitiveGroup.SetBaseIndex(0);
	this->highLodPrimitiveGroup.SetNumIndices(HighLodStripSize);
	this->highLodPrimitiveGroup.SetPrimitiveTopology(PrimitiveTopology::TriangleStrip);
}

//------------------------------------------------------------------------------
/**
*/
void 
D3D9TerrainRenderer::Discard()
{
	n_assert(this->IsValid());

	this->lowLodIndexBuffer->Unload();
	this->lowLodIndexBuffer->SetLoader(0);
	this->lowLodIndexBuffer = 0;

	this->highLodIndexBuffer->Unload();
	this->highLodIndexBuffer->SetLoader(0);
	this->highLodIndexBuffer = 0;

	this->vertexLayout = 0;

	Terrain::TerrainRendererBase::Discard();
}

//------------------------------------------------------------------------------
/**
	generate the triangle strips, the code is from wowmapview

	@param lowStrip [out] low resolution strips
	@param highStrip [out] high resolution strips
*/
void 
D3D9TerrainRenderer::Stripify(ushort* lowStrip, ushort* highStrip)
{
#define IndexMap(x, y) (((y+1)/2)*9 + (y/2)*8 + x)

	// low
	int i, row, col;
	ushort* defstrip = new ushort[LowLodStripSize];
	for (i = 0; i < LowLodStripSize; ++i)
	{
		defstrip[i] = i;
	}

	for (row = 0; row < 8; ++row) 
	{
		ushort *thisrow = &defstrip[IndexMap(0, row*2)];
		ushort *nextrow = &defstrip[IndexMap(0, (row+1)*2)];

		if (row > 0) 
		{
			*lowStrip++ = thisrow[0];
		}

		for (col = 0; col < 9; ++col) 
		{
			*lowStrip++ = thisrow[col];
			*lowStrip++ = nextrow[col];
		}

		if (row < 7)
		{
			*lowStrip++ = nextrow[8];
		}
	}

	delete [] defstrip;

	// high
	defstrip = new ushort[HighLodStripSize];
	for (i = 0; i < HighLodStripSize; ++i)
	{
		defstrip[i] = i;
	}

	for (row = 0; row < 8; ++row)
	{ 
		ushort *thisrow = &defstrip[IndexMap(0,row*2)];
		ushort *nextrow = &defstrip[IndexMap(0,row*2+1)];
		ushort *overrow = &defstrip[IndexMap(0,(row+1)*2)];

		if (row>0) 
		{
			*highStrip++ = thisrow[0];// jump end
		}

		for (col = 0; col < 8; ++col) 
		{
			*highStrip++ = thisrow[col];
			*highStrip++ = nextrow[col];
		}

		*highStrip++ = thisrow[8];
		*highStrip++ = overrow[8];
		*highStrip++ = overrow[8];// jump start
		*highStrip++ = thisrow[0];// jump end
		*highStrip++ = thisrow[0];

		for (col = 0; col < 8; ++col)
		{
			*highStrip++ = overrow[col];
			*highStrip++ = nextrow[col];
		}

		if (row<8) 
		{
			*highStrip++ = overrow[8];
		}

		if (row<7)
		{
			*highStrip++ = overrow[8];// jump start
		}
	}

	delete [] defstrip;
}

} // namespace Direct3D9