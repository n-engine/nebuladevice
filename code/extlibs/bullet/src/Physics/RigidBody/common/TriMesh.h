/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TRIMESH_H__
#define __TRIMESH_H__

#include <float.h>

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PfxAABB16.h"
#include "Physics/Base/VecInt3.h"
#include "Physics/Base/SimdFunc.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#define NUMMESHFACETS		64
#define NUMMESHEDGES		192
#define NUMMESHVERTICES		128

// ラージメッシュの最大サイズ
#define LARGEMESH_SIZE		1000.0f

#define EDGE_FLAT    0
#define EDGE_CONVEX  1
#define EDGE_CONCAVE 2

///////////////////////////////////////////////////////////////////////////////
// エッジ

struct MeshEdge
{
	uint8_t vertIndex[2];
	uint8_t angle;
	uint8_t dirGroup; // 同じ方向を持つエッジを同グループとする（SAT判定の高速化のため）

	bool operator ==(const MeshEdge &in)
	{
	    return (in.vertIndex[0] == vertIndex[0] && in.vertIndex[1] == vertIndex[1]) || 
	    	(in.vertIndex[1] == vertIndex[0] && in.vertIndex[0] == vertIndex[1]);
	}
};

///////////////////////////////////////////////////////////////////////////////
// 面

struct MeshFacet
{
	float   normal[3];
	float   thickness;
	uint8_t dirGroup;
	uint8_t vertIndices[3];
	uint8_t edgeIndices[3];
	float   half[3];	// 面のAABB
	float   center[3];	// 面の中心座標
};

///////////////////////////////////////////////////////////////////////////////
// メッシュ

struct TriMesh
{
	uint8_t numVerts;
	uint8_t numEdges;
	uint8_t numFacets;
	uint8_t reserved;
	float   half[3];
	MeshFacet facets[NUMMESHFACETS];
	MeshEdge  edges[NUMMESHEDGES];
	Vector3   verts[NUMMESHVERTICES];
	
	TriMesh()
	{
		numVerts = numEdges = numFacets = 0;
	}
	
	bool isEdgeUnique(MeshEdge &edge,uint8_t &id)
	{
		for(uint8_t i=0;i<numEdges;i++) {
			if(edges[i] == edge) {
				id = i;
				return false;
			}
		}
		return true;
	}
	
	void updateAABB()
	{
		Vector3 halfMax(0);
		
		for(uint8_t i=0;i<numFacets;i++) {
			Vector3 pnts[6] = {
				verts[facets[i].vertIndices[0]],
				verts[facets[i].vertIndices[1]],
				verts[facets[i].vertIndices[2]],
				verts[facets[i].vertIndices[0]]-facets[i].thickness*read_Vector3(facets[i].normal),
				verts[facets[i].vertIndices[1]]-facets[i].thickness*read_Vector3(facets[i].normal),
				verts[facets[i].vertIndices[2]]-facets[i].thickness*read_Vector3(facets[i].normal)
			};
			
			Vector3 facetAABBmin,facetAABBmax,facetHalf,facetCenter;
			facetAABBmin = minPerElem(pnts[5],minPerElem(pnts[4],minPerElem(pnts[3],minPerElem(pnts[2],minPerElem(pnts[0],pnts[1])))));
			facetAABBmax = maxPerElem(pnts[5],maxPerElem(pnts[4],maxPerElem(pnts[3],maxPerElem(pnts[2],maxPerElem(pnts[0],pnts[1])))));
			facetHalf = 0.5f * (facetAABBmax - facetAABBmin);
			facetCenter = 0.5f * (facetAABBmax + facetAABBmin);
			store_Vector3(facetHalf,facets[i].half);
			store_Vector3(facetCenter,facets[i].center);
			halfMax = maxPerElem(facetCenter+facetHalf,halfMax);
		}

		store_Vector3(halfMax,half);
	}

	void updateIslandAABB(Vector3 &aabbMin,Vector3 &aabbMax)
	{
		aabbMin = Vector3(FLT_MAX);
		aabbMax = Vector3(-FLT_MAX);
		
		for(uint32_t i=0;i<numFacets;i++) {
			aabbMin = minPerElem(aabbMin,read_Vector3(facets[i].center)-read_Vector3(facets[i].half));
			aabbMax = maxPerElem(aabbMax,read_Vector3(facets[i].center)+read_Vector3(facets[i].half));
		}
	}

	Vector3 getAABB(const Matrix3& rotation)
	{
		return absPerElem(rotation) * read_Vector3(half);
	}
} __attribute__ ((aligned(16)));

///////////////////////////////////////////////////////////////////////////////
// 凸メッシュ

struct ConvexMesh
{
	uint8_t numVerts;
	uint8_t numIndices;
	float   half[3];
	uint16_t  indices[NUMMESHFACETS*3];
	Vector3   verts[NUMMESHVERTICES];
	
	ConvexMesh()
	{
		numVerts = numIndices = 0;
	}
	
	void updateAABB()
	{
		Vector3 halfMax(0);
		for(uint8_t i=0;i<numVerts;i++) {
			halfMax = maxPerElem(absPerElem(verts[i]),halfMax);
		}
		store_Vector3(halfMax,half);
	}

	Vector3 getAABB(const Matrix3& rotation)
	{
		return absPerElem(rotation) * read_Vector3(half);
	}
} __attribute__ ((aligned(16)));

///////////////////////////////////////////////////////////////////////////////
// ラージメッシュ

struct LargeTriMesh
{
	// 含まれるメッシュの総数
	uint8_t numIslands;
	uint8_t maxIslands;

	// アイランドのワールドAABB配列
	PfxAABB16 *aabbList;

	// アイランドのポインタ配列
	TriMesh *islands;

	LargeTriMesh()
	{
		numIslands = maxIslands = 0;
		islands = NULL;
		aabbList = NULL;
	}

	bool testAABB(int islandIndex,const Vector3 &center,const Vector3 &half) const 
	{
		VecInt3 aabbMinL = getLocalPosition(center-half);
		VecInt3 aabbMaxL = getLocalPosition(center+half);
		
		if(aabbMaxL.getX() < XMin(aabbList[islandIndex]) || aabbMinL.getX() > XMax(aabbList[islandIndex])) return false;
		if(aabbMaxL.getY() < YMin(aabbList[islandIndex]) || aabbMinL.getY() > YMax(aabbList[islandIndex])) return false;
		if(aabbMaxL.getZ() < ZMin(aabbList[islandIndex]) || aabbMinL.getZ() > ZMax(aabbList[islandIndex])) return false;
		
		return true;
	}
	
	VecInt3 getLocalPosition(const Vector3 &worldPos) const 
	{
		Vector3 lmhalf(LARGEMESH_SIZE*0.5f);
		Vector3 sz(65535.0f);
		Vector3 tmp = divPerElem(worldPos+lmhalf,2.0f*lmhalf);
		tmp = mulPerElem(sz,minPerElem(maxPerElem(tmp,Vector3(0.0f)),Vector3(1.0f))); // clamp 0.0 - 1.0
		return VecInt3(tmp);
	}
	
	VecInt3 getLocalPositionFloor(const Vector3 &worldPos) const 
	{
		Vector3 lmhalf(LARGEMESH_SIZE*0.5f);
		Vector3 sz(65535.0f);
		Vector3 tmp = divPerElem(worldPos+lmhalf,2.0f*lmhalf);
		tmp = mulPerElem(sz,minPerElem(maxPerElem(tmp,Vector3(0.0f)),Vector3(1.0f))); // clamp 0.0 - 1.0
		return VecInt3(floorf(tmp[0]),floorf(tmp[1]),floorf(tmp[2]));
	}
	
	VecInt3 getLocalPositionCeil(const Vector3 &worldPos) const 
	{
		Vector3 lmhalf(LARGEMESH_SIZE*0.5f);
		Vector3 sz(65535.0f);
		Vector3 tmp = divPerElem(worldPos+lmhalf,2.0f*lmhalf);
		tmp = mulPerElem(sz,minPerElem(maxPerElem(tmp,Vector3(0.0f)),Vector3(1.0f))); // clamp 0.0 - 1.0
		return VecInt3(ceilf(tmp[0]),ceilf(tmp[1]),ceilf(tmp[2]));
	}
	
	Vector3 getWorldPosition(const VecInt3 &localPos) const 
	{
		Vector3 lmhalf(LARGEMESH_SIZE*0.5f);
		Vector3 sz(65535.0f);
		Vector3 tmp = divPerElem((Vector3)localPos,sz);
		return mulPerElem(tmp,2.0f*lmhalf) - lmhalf;
	}
} __attribute__ ((aligned(16)));

#endif /* TRIMESH */
