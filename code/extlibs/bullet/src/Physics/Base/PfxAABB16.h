/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __PFX_AABB16_H__
#define __PFX_AABB16_H__

#include "Physics/Base/PhysicsCommon.h"

#ifdef __SPU__

typedef vec_uint4 PfxAABB16;

inline static void setXMin(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,0);}
inline static void setXMax(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,1);}
inline static void setYMin(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,2);}
inline static void setYMax(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,3);}
inline static void setZMin(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,4);}
inline static void setZMax(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,5);}
inline static void setData16_0(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,6);}
inline static void setData16_1(PfxAABB16& s,uint16_t i) {s = (vec_uint4)spu_insert(i,(vec_ushort8)s,7);}
inline static void setData32(PfxAABB16& s,uint32_t i) {s = (vec_uint4)spu_insert(i,(vec_uint4)s,3);}

inline static uint16_t XMin(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,0);}
inline static uint16_t XMax(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,1);}
inline static uint16_t YMin(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,2);}
inline static uint16_t YMax(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,3);}
inline static uint16_t ZMin(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,4);}
inline static uint16_t ZMax(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,5);}
inline static uint16_t Data16_0(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,6);}
inline static uint16_t Data16_1(const PfxAABB16& s) {return spu_extract((vec_ushort8)s,7);}
inline static uint32_t Data32(const PfxAABB16& s) {return spu_extract((vec_uint4)s,3);}

inline bool testAABB(const PfxAABB16 &aabbA,const PfxAABB16 &aabbB)
{
	vec_ushort8 vecAabbA = (vec_ushort8)aabbA;
	vec_ushort8 vecAabbB = (vec_ushort8)aabbB;
	vec_uint4 ptn_mask0 = {0x02031213,0x06071617,0x0A0B1A1B,0x80808080};
	vec_uint4 ptn_mask1 = {0x10110001,0x14150405,0x18190809,0x80808080};
	vec_ushort8 vecMin = spu_shuffle(vecAabbA,vecAabbB,(vec_uchar16)ptn_mask1);
	vec_ushort8 vecMax = spu_shuffle(vecAabbA,vecAabbB,(vec_uchar16)ptn_mask0);
	vec_ushort8 isGt = spu_cmpgt(vecMin,vecMax);
	return spu_extract(spu_gather(isGt),0)==0;
}

#else

struct PfxAABB16
{
	uint32_t data[4];
} __attribute__ ((aligned(16)));

inline static void setXMin(PfxAABB16& s,uint16_t i) {s.data[0]&=0x0000ffff;s.data[0]|=i << 16;}
inline static void setXMax(PfxAABB16& s,uint16_t i) {s.data[0]&=0xffff0000;s.data[0]|=i;}
inline static void setYMin(PfxAABB16& s,uint16_t i) {s.data[1]&=0x0000ffff;s.data[1]|=i << 16;}
inline static void setYMax(PfxAABB16& s,uint16_t i) {s.data[1]&=0xffff0000;s.data[1]|=i;}
inline static void setZMin(PfxAABB16& s,uint16_t i) {s.data[2]&=0x0000ffff;s.data[2]|=i << 16;}
inline static void setZMax(PfxAABB16& s,uint16_t i) {s.data[2]&=0xffff0000;s.data[2]|=i;}
inline static void setData16_0(PfxAABB16& s,uint16_t i) {s.data[3]&=0x0000ffff;s.data[3]|=i << 16;}
inline static void setData16_1(PfxAABB16& s,uint16_t i) {s.data[3]&=0xffff0000;s.data[3]|=i;}
inline static void setData32(PfxAABB16& s,uint32_t i) {s.data[3]=i;}

inline static uint16_t XMin(const PfxAABB16& s) {return ((uint16_t)(s.data[0] >> 16));}
inline static uint16_t XMax(const PfxAABB16& s) {return ((uint16_t)(s.data[0] & 0x0000ffff));}
inline static uint16_t YMin(const PfxAABB16& s) {return ((uint16_t)(s.data[1] >> 16));}
inline static uint16_t YMax(const PfxAABB16& s) {return ((uint16_t)(s.data[1] & 0x0000ffff));}
inline static uint16_t ZMin(const PfxAABB16& s) {return ((uint16_t)(s.data[2] >> 16));}
inline static uint16_t ZMax(const PfxAABB16& s) {return ((uint16_t)(s.data[2] & 0x0000ffff));}
inline static uint16_t Data16_0(const PfxAABB16& s) {return ((uint16_t)(s.data[3] >> 16));}
inline static uint16_t Data16_1(const PfxAABB16& s) {return ((uint16_t)(s.data[3] & 0x0000ffff));}
inline static uint32_t Data32(const PfxAABB16& s) {return s.data[3];}

inline bool testAABB(const PfxAABB16 &aabbA,const PfxAABB16 &aabbB)
{
	if(XMax(aabbA) < XMin(aabbB) || XMin(aabbA) > XMax(aabbB)) return false;
	if(YMax(aabbA) < YMin(aabbB) || YMin(aabbA) > YMax(aabbB)) return false;
	if(ZMax(aabbA) < ZMin(aabbB) || ZMin(aabbA) > ZMax(aabbB)) return false;
	return true;
}

inline PfxAABB16 mergeAABB(const PfxAABB16 &aabbA,const PfxAABB16 &aabbB)
{
	PfxAABB16 aabb;
	setXMin(aabb,PFX_MIN(XMin(aabbA),XMin(aabbB)));
	setXMax(aabb,PFX_MAX(XMax(aabbA),XMax(aabbB)));
	setYMin(aabb,PFX_MIN(YMin(aabbA),YMin(aabbB)));
	setYMax(aabb,PFX_MAX(YMax(aabbA),YMax(aabbB)));
	setZMin(aabb,PFX_MIN(ZMin(aabbA),ZMin(aabbB)));
	setZMax(aabb,PFX_MAX(ZMax(aabbA),ZMax(aabbB)));
	return aabb;
}

#endif

#endif /* __PFX_AABB16_H__ */
