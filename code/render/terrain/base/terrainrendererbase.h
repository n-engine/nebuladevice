#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainRendererBase

	(C) 2011 xiongyouyi
*/
#include "core/refcounted.h"
#include "core/singleton.h"



//------------------------------------------------------------------------------
namespace Terrain
{

#define TILESIZE  (533.33333f)
#define CHUNKSIZE ((TILESIZE) / 16.0f)
#define UNITSIZE  (CHUNKSIZE / 8.0f)

class TerrainRendererBase : public Core::RefCounted
{
	__DeclareAbstractClass(TerrainRendererBase);
public:
	/// the size of the low and high resolution triangle strip
	static const SizeT LowLodStripSize  = 8*18 + 7*2;
	static const SizeT HighLodStripSize = 16*18 + 7*2 + 8*2;

	/// the number of TerrainNode vertices
	static const SizeT NumChunkNodeVertices = 9*9 + 8*8;

	/// constructor
	TerrainRendererBase();
	/// destructor
	virtual ~TerrainRendererBase();

	/// setup the terrain renderer
	virtual void Setup();
	/// discard the terrain renderer
	virtual void Discard();
	/// return true if renderer is valid
	bool IsValid() const;

protected:
	bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
TerrainRendererBase::IsValid() const
{
	return this->isValid;
}

} // namespace Base