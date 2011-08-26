/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SPU_UTIL_H__
#define __SPU_UTIL_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#ifdef __SPU__

#include <spu_intrinsics.h>

static inline
vec_float4 vec_min(vec_float4 a, vec_float4 b)
{
	return spu_sel(a, b, spu_cmpgt(a, b));
}

static inline
vec_float4 vec_max(vec_float4 a, vec_float4 b)
{
	return spu_sel(b, a, spu_cmpgt(a, b));
}

static inline
uint32_t cmpgtAny(const Vector3 &a, const Vector3 &b)
{
	vec_float4 va = a.get128();
	vec_float4 vb = b.get128();
	vec_uint4 cmp = spu_insert(0, spu_cmpgt(va, vb), 3);
	return spu_extract(spu_gather(cmp), 0);
}

static inline vec_uchar16 move_left(vec_uchar16 a, int move_bytes)
{
	return spu_slqwbyte(a, move_bytes);
}

static inline vec_uchar16 move_right(vec_uchar16 a, int move_bytes)
{
	if(move_bytes < 0){
		return move_left(a, -move_bytes);
	}else{
		return spu_rlmaskqwbyte(a, -move_bytes);
	}
}

static inline vec_uchar16 rotate_left(vec_uchar16 a, int move_bytes)
{
	return spu_rlqwbyte(a, move_bytes);
}

static inline vec_uchar16 rotate_right(vec_uchar16 a, int move_bytes)
{
	return spu_rlqwbyte(a, - move_bytes);
}

static inline vec_float4 read_vec_float4(const float* p)
{
	qword up = si_from_ptr(p);
	qword offset = si_andi( up, 0xf);
	vec_float4 v1 = (vec_float4)si_lqd(up, 0);
	vec_float4 v2 = (vec_float4)si_lqd(up, 16);
	vec_uint4 mask = spu_splats(0xffffffff);
	vec_uchar16 ret = spu_sel(rotate_left((vec_uchar16)v2, si_to_uint(offset)),
							  rotate_left((vec_uchar16)v1, si_to_uint(offset)), 
							  move_left((vec_uchar16)mask, si_to_uint(offset)));
	return (vec_float4)ret;
}

static inline Vector3 read_Vector3(const float* p)
{
	return Vector3(read_vec_float4(p));
}

static inline Quat read_Quat(const float* p)
{
	return Quat(read_vec_float4(p));
}

static inline void store_Vector3(const Vector3 &src, float* p)
{
	qword v_src = (qword)src.get128();
	qword up = si_from_ptr(p);
	qword offset_1 = si_andi( up, 0xf);
	qword offset_2 = si_sfi( offset_1, 16);

	qword v1 = si_lqd(up, 0);
	qword v2 = si_lqd(up, 16);
	const qword mask = (qword){0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00};

	v1 = si_selb( v1, si_rotqmby(v_src,-offset_1), si_rotqmby(mask,-offset_1));
	v2 = si_selb( v2, si_rotqby(v_src,offset_2), si_shlqby(mask,offset_2));
	si_stqd(v1, up, 0);
	si_stqd(v2, up, 16);
}

static inline void store_Quat(const Quat &src, float* p)
{
	qword v_src = (qword)src.get128();
	qword up = si_from_ptr(p);
	qword offset_1 = si_andi( up, 0xf);
	qword offset_2 = si_sfi( offset_1, 16);

	qword v1 = si_lqd(up, 0);
	qword v2 = si_lqd(up, 16);
	const qword mask = (qword)spu_splats(0xffffffff);

	v1 = si_selb( v1, si_rotqmby(v_src,-offset_1), si_rotqmby(mask,-offset_1));
	v2 = si_selb( v2, si_rotqby(v_src,offset_2), si_shlqby(mask,offset_2));
	si_stqd(v1, up, 0);
	si_stqd(v2, up, 16);
}

static inline vec_float4 vec_dot3( vec_float4 vec0, vec_float4 vec1 )
{
    vec_float4 result;
    result = spu_mul( vec0, vec1 );
    result = spu_madd( spu_rlqwbyte( vec0, 4 ), spu_rlqwbyte( vec1, 4 ), result );
    return spu_madd( spu_rlqwbyte( vec0, 8 ), spu_rlqwbyte( vec1, 8 ), result );
}

#else

static inline Vector3 read_Vector3(const float* p)
{
	return Vector3(p[0],p[1],p[2]);
}

static inline Quat read_Quat(const float* p)
{
	return Quat(p[0],p[1],p[2],p[3]);
}

static inline void store_Vector3(const Vector3 &src, float* p)
{
	p[0] = src[0];
	p[1] = src[1];
	p[2] = src[2];
}

static inline void store_Quat(const Quat &src, float* p)
{
	p[0] = src[0];
	p[1] = src[1];
	p[2] = src[2];
	p[3] = src[3];
}

#endif

#endif /* __SPU_UTIL_H__ */
