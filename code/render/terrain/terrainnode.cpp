//------------------------------------------------------------------------------
//  TerrainNode.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrainnode.h"
#include "terrainnodeinstance.h"
#include "terrainrenderer.h"
#include "coregraphics/renderdevice.h"
#include "resources/resourceloader.h"
#include "resources/resourcemanager.h"
#include "resources/emptyresourceloader.h"
#include "coregraphics/memoryvertexbufferloader.h"
#include "models/model.h"


namespace Terrain
{
__ImplementClass(Terrain::TerrainNode, 'TERN', Models::StateNode);


using namespace Util;
using namespace Math;
using namespace CoreGraphics;
using namespace Resources;
using namespace Models;

//------------------------------------------------------------------------------
/**
*/
TerrainNode::TerrainNode() :
	xTile(0),
	zTile(0),
	xChunk(0),
	zChunk(0),
	numTextures(0),
	//xbase(0.0),
	//ybase(0.0),
	//zbase(0.0),
	vertics(0),
	blendMap(0)
{

}

//------------------------------------------------------------------------------
/**
*/
TerrainNode::~TerrainNode()
{

}

//------------------------------------------------------------------------------
/**
*/
Ptr<Models::ModelNodeInstance>
TerrainNode::CreateNodeInstance() const
{
	return TerrainNodeInstance::Create();
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNode::BeginParseDataTags()
{
	// create temporary buffer to hold the vertics and blend maps
	TerrainRenderer* renderer = TerrainRenderer::Instance();
	SizeT vertexBufferSize = TerrainRenderer::NumChunkNodeVertices * renderer->GetVertexLayout()->GetVertexByteSize();

	this->vertics = new TerrainVertex[TerrainRenderer::NumChunkNodeVertices];
	this->blendMap = new ubyte[64*64*4];
}

//------------------------------------------------------------------------------
/**
*/
bool 
TerrainNode::ParseDataTag(const Util::FourCC& fourCC, const Ptr<IO::BinaryReader>& reader)
{
	n_assert(this->vertics);
	n_assert(this->blendMap);

	bool retval = true;
	
	if (FourCC('TETN') == fourCC)
	{
		// texture number
		this->numTextures = reader->ReadInt();
	}
	else if (FourCC('TEBI') == fourCC)
	{
		// base info
		this->xTile  = reader->ReadUChar();
		this->zTile  = reader->ReadUChar();
		this->xChunk = reader->ReadUChar();
		this->zChunk = reader->ReadUChar();
	}
	else if (FourCC('TEHT') == fourCC)
	{
		// height map
		float x, z, u, v, h;
		TerrainVertex* pVerts = this->vertics;
		
		for (int i = 0; i < 17; ++i)
		{
			for (int j = 0; j < ((i%2)?8:9); ++j)
			{
				h = reader->ReadFloat();

				u = (float)j;
				v = (8.0f - i * 0.5f);
				x = UNITSIZE * j;
				z = UNITSIZE * i * 0.5f;
				if (i % 2)
				{
					x += UNITSIZE * 0.5f;
					u += 0.5f;
				}

				pVerts->position[0] = x;
				pVerts->position[1] = h;
				pVerts->position[2] = z;
				pVerts->position[3] = 1.0;
				pVerts->uv[0] = u;
				pVerts->uv[1] = v;
				pVerts++;
			}
		}
	}
	else if (FourCC('TENL') == fourCC)
	{
		// normal
		TerrainVertex* pVerts = this->vertics;

		for (int i = 0; i < 17; ++i)
		{
			for (int j = 0; j < ((i%2)?8:9); ++j)
			{
				pVerts->normal[0] = reader->ReadFloat();
				pVerts->normal[1] = reader->ReadFloat();
				pVerts->normal[2] = reader->ReadFloat();
				++pVerts;
			}
		}
	}
	else if (FourCC('TESM') == fourCC)
	{
		// shadow map
		for (int i = 0; i < 64*64; ++i)
		{
			this->blendMap[i*4] = reader->ReadUChar();
		}
	}
	else if (FourCC('TEBM') == fourCC)
	{
		// blend map
		for (int i = 0; i < 64*64; ++i)
		{
			this->blendMap[i*4+1] = reader->ReadUChar();
			this->blendMap[i*4+2] = reader->ReadUChar();
			this->blendMap[i*4+3] = reader->ReadUChar();
		}
	}
	else
	{
		retval = StateNode::ParseDataTag(fourCC, reader);
	}

	return retval;
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNode::EndParseDataTags()
{
	// update bounding box
	float minH = 1.0E10;
	float maxH = -1.0E10;
	for (IndexT i = 0; i < TerrainRenderer::NumChunkNodeVertices; ++i)
	{
		minH = min(minH, this->vertics[i].position[1]);
		maxH = max(maxH, this->vertics[i].position[1]);
	}

	Ptr<TransformNode> parentNode = this->GetParent().cast<TransformNode>();
	point base = parentNode->GetPosition() + this->GetPosition();
	point center(base.x() + CHUNKSIZE / 2.0f, base.y() + (maxH - minH)/2.0f, base.z() + CHUNKSIZE / 2.0f);
	vector extends(CHUNKSIZE / 2.0f, (maxH - minH)/2.0f, CHUNKSIZE / 2.0f);
	this->SetBoundingBox(bbox(center, extends));
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNode::ApplySharedState(IndexT frameIndex)
{
	StateNode::ApplySharedState(frameIndex);

	RenderDevice* renderDevice = RenderDevice::Instance();
	TerrainRenderer* terrainRenderer = TerrainRenderer::Instance();

	if (this->vertexBuffer.isvalid())
	{
		renderDevice->SetStreamSource(0, this->vertexBuffer, 0);
		renderDevice->SetVertexLayout(this->vertexBuffer->GetVertexLayout());
	}

	renderDevice->SetIndexBuffer(terrainRenderer->GetIndexBuffer(true));
	renderDevice->SetPrimitiveGroup(terrainRenderer->GetPrimitiveGroup(true));
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNode::LoadResources()
{
	n_assert(this->vertics);
	n_assert(this->blendMap);

	StateNode::LoadResources();

	// create vertex buffer
	TerrainRenderer* terrainRenderer = TerrainRenderer::Instance();
	Ptr<MemoryVertexBufferLoader> memVBLoader = MemoryVertexBufferLoader::Create();
	SizeT vertexBufferSize = TerrainRenderer::NumChunkNodeVertices * terrainRenderer->GetVertexLayout()->GetVertexByteSize();
	memVBLoader->Setup(terrainRenderer->GetVertexLayout()->GetVertexComponents(), TerrainRenderer::NumChunkNodeVertices, 
		this->vertics, vertexBufferSize, VertexBuffer::UsageImmutable, VertexBuffer::AccessNone);

	this->vertexBuffer = VertexBuffer::Create();
	this->vertexBuffer->SetLoader(memVBLoader.cast<ResourceLoader>());
	this->vertexBuffer->Load();
	this->vertexBuffer->SetLoader(0);

	delete [] this->vertics;
	this->vertics = 0;

	// create blend map
	IDirect3DDevice9* d3d9Dev = RenderDevice::Instance()->GetDirect3DDevice();
	n_assert(0 != d3d9Dev);
	IDirect3DTexture9* d3dTex = NULL;
	HRESULT hr = d3d9Dev->CreateTexture(64, 64, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &d3dTex, 0);
	n_assert(SUCCEEDED(hr));

	D3DLOCKED_RECT rect;
	hr = d3dTex->LockRect(0, &rect, NULL, 0);
	n_assert(SUCCEEDED(hr));
	memcpy(rect.pBits, this->blendMap, 64*64*4);
	d3dTex->UnlockRect(0);

	String texResId;
	texResId.Format("tex:blendmap_%d_%d_%d_%d", this->xTile, this->zTile, this->xChunk, this->zChunk);

	Ptr<EmptyResourceLoader> emptyResLoader = EmptyResourceLoader::Create();
	emptyResLoader->SetState(Resource::Loaded);

	Ptr<ManagedTexture> managedTexture = ResourceManager::Instance()->CreateManagedResource(Texture::RTTI, texResId, emptyResLoader.cast<ResourceLoader>()).downcast<ManagedTexture>();
	managedTexture->GetTexture()->SetupFromD3D9Texture(d3dTex);

	n_assert(this->shaderInstance);
	const Ptr<ShaderVariable>& var = this->shaderInstance->GetVariableBySemantic("BlendMap");
	this->managedTextureVariables.Append(ManagedTextureVariable(managedTexture, var));

	delete [] this->blendMap;
	this->blendMap = 0;
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainNode::UnloadResources()
{
	n_assert(this->vertexBuffer.isvalid());

	this->vertexBuffer->Unload();
	this->vertexBuffer->SetLoader(0);
	this->vertexBuffer = 0;

	StateNode::UnloadResources();
}

} // namespace Terrain