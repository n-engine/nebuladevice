#pragma once
//------------------------------------------------------------------------------
/**
	@class Terrain::TerrainServer
	
	类似于魔兽世界的地形，底层实现地形块的渲染，逻辑层实现地形的加载卸载策略。
	TerrainTile = 16 * 16 TerrainChunk，TerrainTile是最小的加载卸载单元，
	TerrainChunk表示最小的渲染单元，一个TerrainTile存储为一个n3模型文件，
	包含一个TransformNode父节点(表示整个Tile的包围框，用于裁剪)，16*16个地形块节点。

	(C) 2011 xiongyouyi
*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "terrain/terrainrenderer.h"


//------------------------------------------------------------------------------
namespace Terrain
{
class TerrainServer : public Core::RefCounted
{
	__DeclareClass(TerrainServer);
	__DeclareSingleton(TerrainServer);
public:
	/// constructor
	TerrainServer();
	/// destructor
	virtual ~TerrainServer();

	/// open the terrain server
	void Open();
	/// close the terrain server
	void Close();
	/// return true if terrain server is open
	bool IsOpen() const;

private:
	bool isOpen;
	Ptr<TerrainRenderer> terrainRenderer;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
TerrainServer::IsOpen() const
{
	return this->isOpen;
}

} // namespace Terrain
