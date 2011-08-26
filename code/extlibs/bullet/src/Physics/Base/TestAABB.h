/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2008 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __TESTAABB_H__
#define __TESTAABB_H__

///////////////////////////////////////////////////////////////////////////////
// AABB

inline bool testAABB(TrbState &stateA,TrbState &stateB)
{
	if(fabs(stateA.center[0]-stateB.center[0]) > (stateA.half[0]+stateB.half[0])) return false;
	if(fabs(stateA.center[1]-stateB.center[1]) > (stateA.half[1]+stateB.half[1])) return false;
	if(fabs(stateA.center[2]-stateB.center[2]) > (stateA.half[2]+stateB.half[2])) return false;
	return true;
}

inline bool testAABB16(PfxBroadphaseProxy &aabbA,PfxBroadphaseProxy &aabbB)
{
#ifdef TRY_SIMD
	vec_ushort8 vecAabbA = (vec_ushort8)aabbA.vdata[0];
	vec_ushort8 vecAabbB = (vec_ushort8)aabbB.vdata[0];
	vec_uint4 ptn_mask0 = {0x02031213,0x06071617,0x0A0B1A1B,0x80808080};
	vec_uint4 ptn_mask1 = {0x10110001,0x14150405,0x18190809,0x80808080};
	vec_ushort8 vecMin = spu_shuffle(vecAabbA,vecAabbB,(vec_uchar16)ptn_mask1);
	vec_ushort8 vecMax = spu_shuffle(vecAabbA,vecAabbB,(vec_uchar16)ptn_mask0);
	vec_ushort8 isGt = spu_cmpgt(vecMin,vecMax);
	return spu_extract(spu_gather(isGt),0)==0;
#else
	if(XMax(aabbA) < XMin(aabbB) || XMin(aabbA) > XMax(aabbB)) return false;
	if(YMax(aabbA) < YMin(aabbB) || YMin(aabbA) > YMax(aabbB)) return false;
	if(ZMax(aabbA) < ZMin(aabbB) || ZMin(aabbA) > ZMax(aabbB)) return false;
	return true;
#endif
}

#endif /* __TESTAABB_H__ */
