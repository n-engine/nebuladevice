/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_GJK_SOLVER_H__
#define __PFX_GJK_SOLVER_H__

#include <float.h>

#include "Physics/Base/PhysicsCommon.h"
#include "PfxSimplexSolver.h"

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#include "Physics/Base/SimdFunc.h"

#define PFX_GJK_EPSILON			1e-04f
#define PFX_GJK_MARGIN			0.05f
#define PFX_GJK_ITERATION_MAX	10
#define PFX_EPA_ITERATION_MAX	10

/*
	Memo
	pool 13280
	stack 5232 sizeof(PfxGJKSolver) 13856
	*/

///////////////////////////////////////////////////////////////////////////////
// Support Function

typedef void (*GetSupportVertexFunc)(void *shape,Vector3 seperatingAxis,Vector3 &supportVertex);

///////////////////////////////////////////////////////////////////////////////
// GJK

class PfxSimplexSolver;

class PfxGJKSolver
{
private:
	PfxGJKSolver() {}
	
	static const int   MAX_VERTS = 128;
	static const int   MAX_EDGES = 128;
	static const int   MAX_FACETS = 64;
	
	PfxSimplexSolver mSimplex;
	
	// 面
	struct PfxGJKFacet {
		Vector3 normal;			// 面の法線
		Vector3 closest;		// 原点からの最短ベクトル
#ifdef __SPU__
		vec_uint4  obsolete;
		vec_float4 distSqr;
		vec_int4   v;
		vec_int4   j;
		PfxGJKFacet *adj[3];
#else
		uint32_t obsolete;		// 廃棄面判定
		float distSqr;			// 原点からの距離
		int v[3];				// 頂点
		int j[3];				// 隣接面から見たIndex
		PfxGJKFacet *adj[3];	// 隣接面
#endif
	};
	
	// エッジ
	struct PfxGJKEdge {
		PfxGJKFacet *f;
		int i;
		PfxGJKEdge() {}
		PfxGJKEdge(PfxGJKFacet *f_,int i_)
		{
			f = f_;
			i= i_;
		}
	};
	
	#ifndef __SPU__
	Vector3 g_vertsP[MAX_VERTS];
	Vector3 g_vertsQ[MAX_VERTS];
	Vector3 g_vertsW[MAX_VERTS];
	PfxGJKFacet g_facets[MAX_FACETS];
	PfxGJKFacet *g_facetsHead[MAX_FACETS];
	PfxGJKEdge  g_edges[MAX_EDGES];
	#endif

	Vector3 *vertsP __attribute__ ((aligned(16)));
	Vector3 *vertsQ __attribute__ ((aligned(16)));
	Vector3 *vertsW __attribute__ ((aligned(16)));
	PfxGJKFacet *facets __attribute__ ((aligned(16)));
	PfxGJKFacet **facetsHead __attribute__ ((aligned(16)));
	PfxGJKEdge  *edges __attribute__ ((aligned(16)));
	
	int numVerts;
	int numEdges;
	int numFacets;
	int numFacetsHead;
	
#ifdef __SPU__
	inline PfxGJKFacet *addFacet(vec_int4 v);
#else
	inline PfxGJKFacet *addFacet(int v1,int v2,int v3);
#endif

	inline void linkFacets(PfxGJKFacet *f1,int e1,PfxGJKFacet *f2,int e2);
	void silhouette(PfxGJKFacet *facet,int i,Vector3 w);

	inline bool originInTetrahedron(const Vector3& p0,const Vector3& p1,const Vector3& p2,const Vector3& p3);

	float detectPenetrationDepth(
		const Transform3 &transformA,const Transform3 &transformB,
		Vector3 &pA,Vector3 &pB,Vector3 &normal);

	void *shapeA;
	void *shapeB;
	GetSupportVertexFunc getSupportVertexShapeA;
	GetSupportVertexFunc getSupportVertexShapeB;

public:
	PfxGJKSolver(void *sA,void *sB,GetSupportVertexFunc fA,GetSupportVertexFunc fB);
	~PfxGJKSolver();
	
	float collide( Vector3& normal, Point3 &pointA, Point3 &pointB,
					const Transform3 & transformA,
					const Transform3 & transformB,
					float distanceThreshold = FLT_MAX);
};

inline
#ifdef __SPU__
PfxGJKSolver::PfxGJKFacet *PfxGJKSolver::addFacet(vec_int4 v)
#else
PfxGJKSolver::PfxGJKFacet *PfxGJKSolver::addFacet(int v1,int v2,int v3)
#endif
{
	if(PFX_UNLIKELY(numFacets == MAX_FACETS))
		return NULL;

	PfxGJKFacet &facet = facets[numFacets];
#ifdef __SPU__
	Vector3 V1 = vertsW[spu_extract(v,0)];
	Vector3 V2 = vertsW[spu_extract(v,1)];
	Vector3 V3 = vertsW[spu_extract(v,2)];
	facet.obsolete = spu_insert(0,facet.obsolete,0);
	facet.v = v;
#else
	Vector3 V1 = vertsW[v1];
	Vector3 V2 = vertsW[v2];
	Vector3 V3 = vertsW[v3];
	facet.obsolete = 0;
	facet.v[0] = v1;
	facet.v[1] = v2;
	facet.v[2] = v3;
#endif

	Vector3 normal = cross(V3-V1,V2-V1);
	
	float l = lengthSqr(normal);

	if(l < PFX_GJK_EPSILON * PFX_GJK_EPSILON) {
		return NULL;
	}

	normal /= sqrtf(l);
	facet.closest = dot(V1,normal)*normal;
	facet.normal =normal;

#ifdef __SPU__
	facet.distSqr = spu_insert(lengthSqr(facet.closest),facet.distSqr,0);
#else
	facet.distSqr = lengthSqr(facet.closest);
#endif

	facetsHead[numFacetsHead++] = &facet;
	numFacets++;

	return &facet;
}

inline
void PfxGJKSolver::linkFacets(PfxGJKFacet *f1,int e1,PfxGJKFacet *f2,int e2)
{
	f1->adj[e1] = f2;
	f2->adj[e2] = f1;
	f1->j[e1] = e2;
	f2->j[e2] = e1;
}

inline
bool PfxGJKSolver::originInTetrahedron(const Vector3& p0,const Vector3& p1,const Vector3& p2,const Vector3& p3)
{
    Vector3 n0 = cross((p1-p0),(p2-p0));
    Vector3 n1 = cross((p2-p1),(p3-p1));
    Vector3 n2 = cross((p3-p2),(p0-p2));
    Vector3 n3 = cross((p0-p3),(p1-p3));
    
#ifdef __SPU__
	const vec_uchar16 vmask1 = {0x00,0x01,0x02,0x03,0x10,0x11,0x12,0x13,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};
	const vec_uchar16 vmask2 = {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x01,0x02,0x03,0x10,0x11,0x12,0x13};
	vec_float4 v0 = vec_dot3(n0.get128(),p0.get128());
	vec_float4 v1 = vec_dot3(n1.get128(),p1.get128());
	vec_float4 v2 = vec_dot3(n2.get128(),p2.get128());
	vec_float4 v3 = vec_dot3(n3.get128(),p3.get128());
	vec_float4 v4 = vec_dot3(n0.get128(),(p3-p0).get128());
	vec_float4 v5 = vec_dot3(n1.get128(),(p0-p1).get128());
	vec_float4 v6 = vec_dot3(n2.get128(),(p1-p2).get128());
	vec_float4 v7 = vec_dot3(n3.get128(),(p2-p3).get128());
	vec_float4 va = spu_or(spu_shuffle(v0,v1,vmask1),spu_shuffle(v2,v3,vmask2));
	vec_float4 vb = spu_or(spu_shuffle(v4,v5,vmask1),spu_shuffle(v6,v7,vmask2));
	return spu_extract(spu_gather(spu_cmpgt(spu_splats(0.0f),spu_mul(va,vb))),0) != 0;
#else
    return 
		dot(n0,p0) * dot(n0,p3-p0) < 0.0f &&
		dot(n1,p1) * dot(n1,p0-p1) < 0.0f &&
		dot(n2,p2) * dot(n2,p1-p2) < 0.0f &&
		dot(n3,p3) * dot(n3,p2-p3) < 0.0f;
#endif
}

#endif /* __PFX_GJK_SOLVER_H__ */
