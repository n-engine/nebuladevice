//------------------------------------------------------------------------------
//  terrainrendererbase.cc
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "terrain/base/terrainrendererbase.h"


namespace Terrain
{
__ImplementAbstractClass(Terrain::TerrainRendererBase, 'TERB', Core::RefCounted);


//------------------------------------------------------------------------------
/**
*/
TerrainRendererBase::TerrainRendererBase() :
	isValid(false)
{
}

//------------------------------------------------------------------------------
/**
*/
TerrainRendererBase::~TerrainRendererBase()
{
	if (IsValid())
	{
		this->Discard();
	}
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainRendererBase::Setup()
{
	n_assert(!this->IsValid());
	this->isValid = true;
}

//------------------------------------------------------------------------------
/**
*/
void 
TerrainRendererBase::Discard()
{
	n_assert(this->IsValid());
	this->isValid = false;
}

} // namespace Base