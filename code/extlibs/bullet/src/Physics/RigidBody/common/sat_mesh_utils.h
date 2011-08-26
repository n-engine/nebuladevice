/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SAT_MESH_UTILS_H__
#define __SAT_MESH_UTILS_H__

struct Plane {
	Vector3 N; // normal
	Vector3 Q; // a point on plane

	Plane(const Vector3 &n,const Vector3 &q) {
		N = n;
		Q = q;
	}
	
	float onPlane(const Vector3 &p) const {
		return dot((p-Q),N);
	}
};

///////////////////////////////////////////////////////////////////////////////
// 指定された面グループの頂点を集める

static __attribute__((always_inline)) inline 
void gatherVerts(
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selVerts,
	uint8_t &numSelVerts
)
{
	numSelVerts = 0;

	uint32_t vertBitflags[(NUMMESHVERTICES+31)/32] = {0};

#ifdef _TRY_SIMD
	vec_uint4 v_numSelVerts = spu_splats((unsigned int)0);

	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];

		vec_uint4 v_index = {facet.vertIndices[0],facet.vertIndices[1],facet.vertIndices[2],0};
		vec_uint4 v_bflagIndex = spu_rlmask(v_index,5);
		vec_uint4 v_mask = spu_sl((vec_uint4){1,1,1,0},spu_and(v_index,(vec_uint4){31,31,31,0}));
		vec_uint4 v_bflag = {
			vertBitflags[spu_extract(v_bflagIndex,0)],
			vertBitflags[spu_extract(v_bflagIndex,1)],
			vertBitflags[spu_extract(v_bflagIndex,2)],
			0};

		vec_uint4 v_result = spu_and(v_bflag,v_mask);

		vertBitflags[spu_extract(v_bflagIndex,0)] |= spu_extract(v_mask,0);
		vertBitflags[spu_extract(v_bflagIndex,1)] |= spu_extract(v_mask,1);
		vertBitflags[spu_extract(v_bflagIndex,2)] |= spu_extract(v_mask,2);

		selVerts[spu_extract(v_numSelVerts, 0)] = spu_extract(v_index,0);
		v_numSelVerts = spu_sel(v_numSelVerts+spu_splats(1), v_numSelVerts,spu_splats(spu_extract(v_result,0)));
		selVerts[spu_extract(v_numSelVerts, 0)] = spu_extract(v_index,1);
		v_numSelVerts = spu_sel(v_numSelVerts+spu_splats(1), v_numSelVerts,spu_splats(spu_extract(v_result,1)));
		selVerts[spu_extract(v_numSelVerts, 0)] = spu_extract(v_index,2);
		v_numSelVerts = spu_sel(v_numSelVerts+spu_splats(1), v_numSelVerts,spu_splats(spu_extract(v_result,2)));
	}

	numSelVerts = spu_extract(v_numSelVerts, 0);
#else
	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];

		for(int i=0;i<3;i++) {
			uint32_t mask,index;

			index = facet.vertIndices[i];
			mask = 1 << (index & 31);
			if((vertBitflags[index>>5] & mask) == 0) {
				vertBitflags[index>>5] |= mask;
				selVerts[numSelVerts++] = index;
			}
		}
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// 面に属するエッジを集める

static __attribute__((always_inline)) inline 
void gatherEdges(
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selEdges,
	uint8_t &numSelEdges
	)
{
	uint32_t edgeBitflags[(NUMMESHEDGES+31)/32] = {0};
	numSelEdges = 0;

#ifdef _TRY_SIMD
	vec_uint4 v_numSelEdges = spu_splats((uint32_t)0);

	for(uint8_t f=0;f<numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];

		vec_uint4 v_index = {facet.edgeIndices[0],facet.edgeIndices[1],facet.edgeIndices[2],0};
		vec_uint4 v_bflagIndex = spu_rlmask(v_index,5);
		vec_uint4 v_mask = spu_sl((vec_uint4){1,1,1,0},spu_and(v_index,(vec_uint4){31,31,31,0}));
		vec_uint4 v_bflag = {
			edgeBitflags[spu_extract(v_bflagIndex,0)],
			edgeBitflags[spu_extract(v_bflagIndex,1)],
			edgeBitflags[spu_extract(v_bflagIndex,2)],
			0};
		vec_uint4 v_convex = {
			mesh->edges[spu_extract(v_index,0)].angle,
			mesh->edges[spu_extract(v_index,1)].angle,
			mesh->edges[spu_extract(v_index,2)].angle,
			0};

		vec_uint4 v_result = spu_sel((vec_uint4){1,1,1,1},spu_and(v_bflag,v_mask),spu_cmpeq(v_convex,EDGE_CONVEX));

		edgeBitflags[spu_extract(v_bflagIndex,0)] |= spu_extract(v_mask,0);
		edgeBitflags[spu_extract(v_bflagIndex,1)] |= spu_extract(v_mask,1);
		edgeBitflags[spu_extract(v_bflagIndex,2)] |= spu_extract(v_mask,2);

		selEdges[spu_extract(v_numSelEdges, 0)] = spu_extract(v_index,0);
		v_numSelEdges = spu_sel(v_numSelEdges+spu_splats(1), v_numSelEdges,spu_splats(spu_extract(v_result,0)));
		selEdges[spu_extract(v_numSelEdges, 0)] = spu_extract(v_index,1);
		v_numSelEdges = spu_sel(v_numSelEdges+spu_splats(1), v_numSelEdges,spu_splats(spu_extract(v_result,1)));
		selEdges[spu_extract(v_numSelEdges, 0)] = spu_extract(v_index,2);
		v_numSelEdges = spu_sel(v_numSelEdges+spu_splats(1), v_numSelEdges,spu_splats(spu_extract(v_result,2)));
	}
	numSelEdges = spu_extract(v_numSelEdges, 0);
#else
	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];
		for(int i=0;i<3;i++) {
			uint32_t mask,index;
			index = facet.edgeIndices[i];
			if(mesh->edges[index].angle == EDGE_CONVEX) {
				mask = 1 << (index & 31);
				if((edgeBitflags[index>>5] & mask) == 0) {
					edgeBitflags[index>>5] |= mask;
					selEdges[numSelEdges++] = index;
				}
			}
		}
	}
#endif
}

static __attribute__((always_inline)) inline 
void gatherEdges2(
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selEdges,
	uint8_t &numSelEdges
	)
{
	uint32_t edgeGroup[(NUMMESHEDGES+31)/32] = {0};
	uint32_t edgeBitflags[(NUMMESHEDGES+31)/32] = {0};
	numSelEdges = 0;

	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];

		for(int i=0;i<3;i++) {
			uint32_t mask,groupId,edgeId;

			edgeId = facet.edgeIndices[i];
			MeshEdge edge = mesh->edges[edgeId];

			if(edge.angle != EDGE_CONVEX) continue;

			mask = 1 << (edgeId & 31);
			if((edgeBitflags[edgeId>>5] & mask) != 0) continue;
			edgeBitflags[edgeId>>5] |= mask;

			groupId = edge.dirGroup;
			mask = 1 << (groupId & 31);
			if((edgeGroup[groupId>>5] & mask) != 0) continue;
			edgeGroup[groupId>>5] |= mask;

			selEdges[numSelEdges++] = edgeId;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// AABBに交差している面を集める

static __attribute__((always_inline)) inline 
void gatherFacets(
	const TriMesh *mesh,
	const float *aabbHalf,
	const Vector3 &offsetPos,
	const Matrix3 &offsetRot,
	uint8_t *selFacets,
	uint8_t &numSelFacets
	)
{
	Matrix3 absOffsetRot = absPerElem(offsetRot);

#ifdef TRY_SIMD
	Vector3 v_aabbHalf(read_Vector3(aabbHalf));
	vec_uint4 v_numSelFacets = spu_splats((unsigned int)0);
	int f = 0;
	for(;f<(int)mesh->numFacets-4;f+=4) {
		const MeshFacet &facet0 = mesh->facets[f];
		const MeshFacet &facet1 = mesh->facets[f+1];
		const MeshFacet &facet2 = mesh->facets[f+2];
		const MeshFacet &facet3 = mesh->facets[f+3];

		Vector3 facetCenter0 = absPerElem(offsetPos + offsetRot * read_Vector3(facet0.center));
		Vector3 facetCenter1 = absPerElem(offsetPos + offsetRot * read_Vector3(facet1.center));
		Vector3 facetCenter2 = absPerElem(offsetPos + offsetRot * read_Vector3(facet2.center));
		Vector3 facetCenter3 = absPerElem(offsetPos + offsetRot * read_Vector3(facet3.center));

		Vector3 half0      = absOffsetRot * read_Vector3(facet0.half);
		Vector3 half1      = absOffsetRot * read_Vector3(facet1.half);
		Vector3 half2      = absOffsetRot * read_Vector3(facet2.half);
		Vector3 half3      = absOffsetRot * read_Vector3(facet3.half);

		// ConvexBのAABBとチェック
		uint32_t isCheck0 = !cmpgtAny( facetCenter0, half0 + v_aabbHalf);
		uint32_t isCheck1 = !cmpgtAny( facetCenter1, half1 + v_aabbHalf);
		uint32_t isCheck2 = !cmpgtAny( facetCenter2, half2 + v_aabbHalf);
		uint32_t isCheck3 = !cmpgtAny( facetCenter3, half3 + v_aabbHalf);
		
		// この面は判定.
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+0);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck0), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+1);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck1), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+2);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck2), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+3);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck3), 0));
	}
	for(;f<mesh->numFacets;f++) {
		const MeshFacet &facet = mesh->facets[f];
		Vector3 facetCenter = absPerElem(offsetPos + offsetRot * read_Vector3(facet.center));
		Vector3 facetHalf   = absOffsetRot * read_Vector3(facet.half);

		// capsuleBのAABBとチェック.
		uint32_t isCheck = !cmpgtAny( facetCenter, facetHalf + v_aabbHalf);

		// この面は判定.
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)f;
		v_numSelFacets = spu_sel(v_numSelFacets,v_numSelFacets + spu_splats(1),  spu_cmpgt(spu_splats(isCheck), 0));
	}
	numSelFacets = spu_extract(v_numSelFacets, 0);
#else
	for(int f=0;f<(int)mesh->numFacets;f++) {
		const MeshFacet &facet = mesh->facets[f];

		Vector3 facetCenter = absPerElem(offsetPos + offsetRot * read_Vector3(facet.center));
		Vector3 halfBA = absOffsetRot * read_Vector3(facet.half);

		// ConvexBのAABBとチェック
		if(facetCenter[0] > (halfBA[0]+aabbHalf[0])) continue;
		if(facetCenter[1] > (halfBA[1]+aabbHalf[1])) continue;
		if(facetCenter[2] > (halfBA[2]+aabbHalf[2])) continue;
		
		// この面は判定
		selFacets[numSelFacets++] = (uint8_t)f;
	}
#endif
}

static __attribute__((always_inline)) inline 
void gatherFacets(
	const TriMesh *mesh,
	const float *aabbHalf,
	const Vector3 &offsetPos,
	const Matrix3 &offsetRot,
	uint8_t *selFacets,
	uint8_t &numSelFacets,
	uint8_t *selVerts,
	uint8_t &numSelVerts
	)
{
	uint32_t vertBitflags[(NUMMESHVERTICES+31)/32] = {0};
	Matrix3 absOffsetRot = absPerElem(offsetRot);

//#ifdef TRY_SIMD
#ifdef __SPU__
	Vector3 v_aabbHalf(read_Vector3(aabbHalf));
	vec_uint4 v_numSelFacets = spu_splats((unsigned int)0);
	int f = 0;
	for(;f<(int)mesh->numFacets-4;f+=4) {
		const MeshFacet &facet0 = mesh->facets[f];
		const MeshFacet &facet1 = mesh->facets[f+1];
		const MeshFacet &facet2 = mesh->facets[f+2];
		const MeshFacet &facet3 = mesh->facets[f+3];

		Vector3 facetCenter0 = absPerElem(offsetPos + offsetRot * read_Vector3(facet0.center));
		Vector3 facetCenter1 = absPerElem(offsetPos + offsetRot * read_Vector3(facet1.center));
		Vector3 facetCenter2 = absPerElem(offsetPos + offsetRot * read_Vector3(facet2.center));
		Vector3 facetCenter3 = absPerElem(offsetPos + offsetRot * read_Vector3(facet3.center));

		Vector3 half0      = absOffsetRot * read_Vector3(facet0.half);
		Vector3 half1      = absOffsetRot * read_Vector3(facet1.half);
		Vector3 half2      = absOffsetRot * read_Vector3(facet2.half);
		Vector3 half3      = absOffsetRot * read_Vector3(facet3.half);

		// ConvexBのAABBとチェック
		uint32_t isCheck0 = !cmpgtAny( facetCenter0, half0 + v_aabbHalf);
		uint32_t isCheck1 = !cmpgtAny( facetCenter1, half1 + v_aabbHalf);
		uint32_t isCheck2 = !cmpgtAny( facetCenter2, half2 + v_aabbHalf);
		uint32_t isCheck3 = !cmpgtAny( facetCenter3, half3 + v_aabbHalf);
		
		// この面は判定.
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+0);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck0), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+1);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck1), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+2);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck2), 0));
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)(f+3);
		v_numSelFacets = spu_sel(v_numSelFacets, v_numSelFacets+spu_splats(1),	spu_cmpgt(spu_splats(isCheck3), 0));
	}
	for(;f<(int)mesh->numFacets;f++) {
		const MeshFacet &facet = mesh->facets[f];
		Vector3 facetCenter = absPerElem(offsetPos + offsetRot * read_Vector3(facet.center));
		Vector3 facetHalf   = absOffsetRot * read_Vector3(facet.half);

		// capsuleBのAABBとチェック.
		uint32_t isCheck = !cmpgtAny( facetCenter, facetHalf + v_aabbHalf);

		// この面は判定.
		selFacets[spu_extract(v_numSelFacets, 0)] = (uint8_t)f;
		v_numSelFacets = spu_sel(v_numSelFacets,v_numSelFacets + spu_splats(1),  spu_cmpgt(spu_splats(isCheck), 0));
	}
	numSelFacets = spu_extract(v_numSelFacets, 0);

	for(f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];
		
		// この面に属する頂点を保存する
		for(int i=0;i<3;i++) {
			uint32_t mask,index;

			index = facet.vertIndices[i];
			mask = 1 << (index & 31);
			if((vertBitflags[index>>5] & mask) == 0) {
				vertBitflags[index>>5] |= mask;
				selVerts[numSelVerts++] = index;
			}
		}
	}
#else
	for(int f=0;f<(int)mesh->numFacets;f++) {
		const MeshFacet &facet = mesh->facets[f];

		Vector3 facetCenter = absPerElem(offsetPos + offsetRot * Vector3(facet.center[0],facet.center[1],facet.center[2]));
		Vector3 halfBA = absOffsetRot * Vector3(facet.half[0],facet.half[1],facet.half[2]);

		// ConvexBのAABBとチェック
		if(facetCenter[0] > (halfBA[0]+aabbHalf[0])) continue;
		if(facetCenter[1] > (halfBA[1]+aabbHalf[1])) continue;
		if(facetCenter[2] > (halfBA[2]+aabbHalf[2])) continue;
		
		// この面は判定
		selFacets[numSelFacets++] = (uint8_t)f;
		
		// この面に属する頂点を保存する
		for(int i=0;i<3;i++) {
			uint32_t mask,index;

			index = facet.vertIndices[i];
			mask = 1 << (index & 31);
			if((vertBitflags[index>>5] & mask) == 0) {
				vertBitflags[index>>5] |= mask;
				selVerts[numSelVerts++] = index;
			}
		}
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// 指定された面グループと同じ面を集める

static __attribute__((always_inline)) inline 
void gatherFacetsFromFacetGroup(
	uint8_t groupId,
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selGpFacets,
	uint8_t &numSelGpFacets
)
{
#ifdef TRY_SIMD
	vec_uint4 v_numSelGpFacets = {0,0,0,0};
	vec_uint4 v_groupId = spu_splats((unsigned int)groupId);

	int f=0;
	for(;f<(int)numSelFacets-4;f+=4) {
		vec_uint4 v_curindex = {selFacets[f],selFacets[f+1],selFacets[f+2],selFacets[f+3]};

		const MeshFacet &f0 = mesh->facets[spu_extract(v_curindex,0)];
		const MeshFacet &f1 = mesh->facets[spu_extract(v_curindex,1)];
		const MeshFacet &f2 = mesh->facets[spu_extract(v_curindex,2)];
		const MeshFacet &f3 = mesh->facets[spu_extract(v_curindex,3)];

		vec_uint4 v_curgroup = {f0.dirGroup,f1.dirGroup,f2.dirGroup,f3.dirGroup};
		vec_uint4 v_result = spu_cmpeq(v_curgroup,v_groupId);

		selGpFacets[spu_extract(v_numSelGpFacets, 0)] = spu_extract(v_curindex,0);
		v_numSelGpFacets = spu_sel(v_numSelGpFacets, v_numSelGpFacets+spu_splats(1),spu_splats(spu_extract(v_result,0)));
		selGpFacets[spu_extract(v_numSelGpFacets, 0)] = spu_extract(v_curindex,1);
		v_numSelGpFacets = spu_sel(v_numSelGpFacets, v_numSelGpFacets+spu_splats(1),spu_splats(spu_extract(v_result,1)));
		selGpFacets[spu_extract(v_numSelGpFacets, 0)] = spu_extract(v_curindex,2);
		v_numSelGpFacets = spu_sel(v_numSelGpFacets, v_numSelGpFacets+spu_splats(1),spu_splats(spu_extract(v_result,2)));
		selGpFacets[spu_extract(v_numSelGpFacets, 0)] = spu_extract(v_curindex,3);
		v_numSelGpFacets = spu_sel(v_numSelGpFacets, v_numSelGpFacets+spu_splats(1),spu_splats(spu_extract(v_result,3)));
	}
	for(;f<(int)numSelFacets;f++) {
		vec_uint4 v_curindex = {selFacets[f],0,0,0};

		const MeshFacet &facet = mesh->facets[spu_extract(v_curindex,0)];

		vec_uint4 v_curgroup = {facet.dirGroup,0,0,0};
		vec_uint4 v_result = spu_cmpeq(v_curgroup,v_groupId);

		selGpFacets[spu_extract(v_numSelGpFacets, 0)] = spu_extract(v_curindex,0);
		v_numSelGpFacets = spu_sel(v_numSelGpFacets, v_numSelGpFacets+spu_splats(1),spu_splats(spu_extract(v_result,0)));
	}
	numSelGpFacets = spu_extract(v_numSelGpFacets,0);
#else
	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];
		if(groupId == facet.dirGroup) {
			selGpFacets[numSelGpFacets++] = selFacets[f];
		}
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// 指定された頂点を含む面を集める

static __attribute__((always_inline)) inline 
void gatherFacetsFromVertId(
	uint8_t vertId,
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selGpFacets,
	uint8_t &numSelGpFacets
)
{
	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];
		if(vertId == facet.vertIndices[0] || vertId == facet.vertIndices[1] || vertId == facet.vertIndices[2]) {
			selGpFacets[numSelGpFacets++] = selFacets[f];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// エッジを集める

static __attribute__((always_inline)) inline 
void gatherEdgesFromGroup(
	uint8_t groupId,
	const TriMesh *mesh,
	const uint8_t *selFacets,
	uint8_t numSelFacets,
	uint8_t *selEdges,
	uint8_t &numSelEdges
)
{
	uint32_t edgeBitflags[(NUMMESHEDGES+31)/32] = {0};

	for(int f=0;f<(int)numSelFacets;f++) {
		const MeshFacet &facet = mesh->facets[selFacets[f]];
		for(int i=0;i<3;i++) {
			uint32_t mask,index;
			index = facet.edgeIndices[i];
			if(mesh->edges[index].dirGroup == groupId && mesh->edges[index].angle == EDGE_CONVEX) {
				mask = 1 << (index & 31);
				if((edgeBitflags[index>>5] & mask) == 0) {
					edgeBitflags[index>>5] |= mask;
					selEdges[numSelEdges++] = index;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// 面と頂点の範囲を取得

static inline void getProjPlane(
	const Vector3 *verts,const uint8_t *vertIds,uint8_t numVerts,const Plane &plane,
	float &distMin)
{
//#ifdef TRY_SIMD
#ifdef __SPU__
	vec_float4 v_distMin = {FLT_MAX,0,0,0};
	int v=0;
	for(;v<(int)numVerts-4;v+=4) {
		vec_float4 p0 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v]]));
		vec_float4 p1 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+1]]));
		vec_float4 p2 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+2]]));
		vec_float4 p3 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+3]]));

		vec_float4 pmin = vec_min(vec_min(p0,p1),vec_min(p2,p3));
		v_distMin = vec_min(v_distMin,pmin);
	}
	for(;v<(int)numVerts;v++) {
		vec_float4 p = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v]]));
		v_distMin = vec_min(v_distMin,p);
	}
	distMin = spu_extract(v_distMin,0);
#else
	distMin = FLT_MAX;
	for(int v=0;v<(int)numVerts;v++) {
		float p = plane.onPlane(verts[vertIds[v]]);
		if(p < distMin) {
			distMin = p;
		}
	}
#endif
}

static inline void getProjPlane(
	const Vector3 *verts,const uint8_t *vertIds,uint8_t numVerts,const Plane &plane,
	float &distMin,float &distMax)
{
//#ifdef TRY_SIMD
#ifdef __SPU__
	vec_float4 v_distMin = {FLT_MAX,0,0,0};
	vec_float4 v_distMax = {-FLT_MAX,0,0,0};
	int v=0;
	for(;v<(int)numVerts-4;v+=4) {
		vec_float4 p0 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v]]));
		vec_float4 p1 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+1]]));
		vec_float4 p2 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+2]]));
		vec_float4 p3 = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v+3]]));

		vec_float4 pmin = vec_min(vec_min(p0,p1),vec_min(p2,p3));
		v_distMin = vec_min(v_distMin,pmin);

		vec_float4 pmax = vec_max(vec_max(p0,p1),vec_max(p2,p3));
		v_distMax = vec_max(v_distMax,pmax);
	}
	for(;v<(int)numVerts;v++) {
		vec_float4 p = (vec_float4)(qword)si_from_float(plane.onPlane(verts[vertIds[v]]));
		v_distMin = vec_min(v_distMin,p);
		v_distMax = vec_max(v_distMax,p);
	}
	distMin = spu_extract(v_distMin,0);
	distMax = spu_extract(v_distMax,0);
#else
	distMin = FLT_MAX;
	distMax = -FLT_MAX;
	for(int v=0;v<(int)numVerts;v++) {
		float p = plane.onPlane(verts[vertIds[v]]);
		if(p < distMin) distMin = p;
		if(p > distMax) distMax = p;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// ベクトルに投影された頂点の範囲を取得

static inline void getProjAxis(
	const Vector3 *verts,const uint8_t *vertIds,uint8_t numVerts,const Vector3 &axis,
	float &distMin,float &distMax)
{
#ifdef TRY_SIMD
	vec_float4 v_distMin = {FLT_MAX,0,0,0};
	vec_float4 v_distMax = {-FLT_MAX,0,0,0};
	int v=0;
	for(;v<(int)numVerts-4;v+=4) {
		vec_float4 p0 = (vec_float4)(qword)si_from_float(dot(axis,verts[vertIds[v]]));
		vec_float4 p1 = (vec_float4)(qword)si_from_float(dot(axis,verts[vertIds[v+1]]));
		vec_float4 p2 = (vec_float4)(qword)si_from_float(dot(axis,verts[vertIds[v+2]]));
		vec_float4 p3 = (vec_float4)(qword)si_from_float(dot(axis,verts[vertIds[v+3]]));

		vec_float4 pmin = vec_min(vec_min(p0,p1),vec_min(p2,p3));
		v_distMin = vec_min(v_distMin,pmin);

		vec_float4 pmax = vec_max(vec_max(p0,p1),vec_max(p2,p3));
		v_distMax = vec_max(v_distMax,pmax);
	}
	for(;v<(int)numVerts;v++) {
		vec_float4 p = (vec_float4)(qword)si_from_float(dot(axis,verts[vertIds[v]]));
		v_distMin = vec_min(v_distMin,p);
		v_distMax = vec_max(v_distMax,p);
	}
	distMin = spu_extract(v_distMin,0);
	distMax = spu_extract(v_distMax,0);
#else
	distMin = FLT_MAX;
	distMax = -FLT_MAX;
	for(int v=0;v<(int)numVerts;v++) {
		float p = dot(axis,verts[vertIds[v]]);
		if(p < distMin) {
			distMin = p;
		}
		if(p > distMax) {
			distMax = p;
		}
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// ベクトルに投影された頂点x3の範囲を取得

static inline void getProjAxisPnts6(
	const Vector3 *verts,const Vector3 &axis,
	float &distMin,float &distMax)
{
#ifdef __SPU__
	vec_float4 p0 = (vec_float4)(qword)si_from_float(dot(axis,verts[0]));
	vec_float4 p1 = (vec_float4)(qword)si_from_float(dot(axis,verts[1]));
	vec_float4 p2 = (vec_float4)(qword)si_from_float(dot(axis,verts[2]));
	vec_float4 p3 = (vec_float4)(qword)si_from_float(dot(axis,verts[3]));
	vec_float4 p4 = (vec_float4)(qword)si_from_float(dot(axis,verts[4]));
	vec_float4 p5 = (vec_float4)(qword)si_from_float(dot(axis,verts[5]));

	vec_float4 v_distMin = vec_min(vec_min(vec_min(vec_min(vec_min(p0,p1),p2),p3),p4),p5);
	vec_float4 v_distMax = vec_max(vec_max(vec_max(vec_max(vec_max(p0,p1),p2),p3),p4),p5);

	distMin = spu_extract(v_distMin,0);
	distMax = spu_extract(v_distMax,0);
#else
	float p0 = dot(axis, verts[0]);
	float p1 = dot(axis, verts[1]);
	float p2 = dot(axis, verts[2]);
	float p3 = dot(axis, verts[3]);
	float p4 = dot(axis, verts[4]);
	float p5 = dot(axis, verts[5]);
	distMin = PFX_MIN(p5,PFX_MIN(p4,PFX_MIN(p3,PFX_MIN(p2,PFX_MIN(p0,p1)))));
	distMax = PFX_MAX(p5,PFX_MAX(p4,PFX_MAX(p3,PFX_MAX(p2,PFX_MAX(p0,p1)))));
#endif
}

static inline void getProjAxisPnts3(
	const Vector3 *verts,const Vector3 &axis,
	float &distMin,float &distMax)
{
//#ifdef TRY_SIMD
#ifdef __SPU__
	vec_float4 p0 = (vec_float4)(qword)si_from_float(dot(axis,verts[0]));
	vec_float4 p1 = (vec_float4)(qword)si_from_float(dot(axis,verts[1]));
	vec_float4 p2 = (vec_float4)(qword)si_from_float(dot(axis,verts[2]));

	vec_float4 v_distMin = vec_min(vec_min(p0,p1),p2);
	vec_float4 v_distMax = vec_max(vec_max(p0,p1),p2);

	distMin = spu_extract(v_distMin,0);
	distMax = spu_extract(v_distMax,0);
#else
	float p0 = dot(axis, verts[0]);
	float p1 = dot(axis, verts[1]);
	float p2 = dot(axis, verts[2]);
	distMin = PFX_MIN(p2,PFX_MIN(p0,p1));
	distMax = PFX_MAX(p2,PFX_MAX(p0,p1));
#endif
}

static inline void getProjAxisPnts2(
	const Vector3 *verts,const Vector3 &axis,
	float &distMin,float &distMax)
{
//#ifdef TRY_SIMD
#ifdef __SPU__
	vec_float4 p0 = (vec_float4)(qword)si_from_float(dot(axis,verts[0]));
	vec_float4 p1 = (vec_float4)(qword)si_from_float(dot(axis,verts[1]));

	vec_float4 v_distMin = vec_min(p0,p1);
	vec_float4 v_distMax = vec_max(p0,p1);

	distMin = spu_extract(v_distMin,0);
	distMax = spu_extract(v_distMax,0);
#else
	float p0 = dot(axis, verts[0]);
	float p1 = dot(axis, verts[1]);
	distMin = PFX_MIN(p0,p1);
	distMax = PFX_MAX(p0,p1);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// 面への最近接頂点のインデックスを取得

static inline uint8_t getClosestPointProjPlane(
	const Vector3 *verts,const uint8_t *vertIds,uint8_t numVerts,const Plane &plane)
{
	uint8_t minId = 0;
	float distMin = FLT_MAX;
	for(int v=0;v<(int)numVerts;v++) {
		float p = plane.onPlane(verts[vertIds[v]]);
		if(p < distMin) {
			distMin = p;
			minId = vertIds[v];
		}
	}
	return minId;
}

///////////////////////////////////////////////////////////////////////////////
// ２つのベクトルの向きをチェック

static inline bool isSameDirection(const Vector3 &vecA,const Vector3 &vecB)
{
#ifdef TRY_SIMD
	vec_float4 vec0 = vecA.get128();
	vec_float4 vec1 = vecB.get128();
	vec_float4 tmp;
	tmp = spu_mul(vec0,vec1);
	tmp = spu_madd(spu_rlqwbyte(vec0,4),spu_rlqwbyte(vec1,4),tmp);
	tmp = spu_madd(spu_rlqwbyte(vec0,8),spu_rlqwbyte(vec1,8),tmp);
	vec_uint4 result = spu_cmpgt(fabsf4(tmp),spu_splats(0.9999f));
	return spu_extract(result,0) > 0;
#else
	return fabsf(dot(vecA,vecB)) > 0.9999f;
#endif
}

#endif /* __SAT_MESH_UTILS_H__ */
