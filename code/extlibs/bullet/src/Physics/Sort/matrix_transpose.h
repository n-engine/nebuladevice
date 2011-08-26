/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __MATRIX_TRANSPOSE__INCLUDED__
#define __MATRIX_TRANSPOSE__INCLUDED__

#include <spu_intrinsics.h>

static inline void MatrixTransposeBase(vector unsigned int i1,
																		vector unsigned int i2,
																		vector unsigned int i3,
																		vector unsigned int i4,
																		vector unsigned int& o1,
																		vector unsigned int& o2,
																		vector unsigned int& o3,
																		vector unsigned int& o4)
{
	vector unsigned int t1,t2,t3,t4;
	static vector unsigned char shuffle_param1=(vector unsigned char)( 0, 1, 2, 3, 8, 9,10,11,16,17,18,19,24,25,26,27);
	static vector unsigned char shuffle_param2=(vector unsigned char)( 4, 5, 6, 7,12,13,14,15,20,21,22,23,28,29,30,31);

	t1=spu_shuffle(i1,i2,shuffle_param1);
	t2=spu_shuffle(i1,i2,shuffle_param2);
	t3=spu_shuffle(i3,i4,shuffle_param1);
	t4=spu_shuffle(i3,i4,shuffle_param2);
	o1=spu_shuffle(t1,t3,shuffle_param1);
	o3=spu_shuffle(t1,t3,shuffle_param2);
	o2=spu_shuffle(t2,t4,shuffle_param1);
	o4=spu_shuffle(t2,t4,shuffle_param2);
}

template <class Vec4B>
static inline void MatrixTranspose(Vec4B i1,Vec4B i2,Vec4B i3,Vec4B i4,Vec4B& o1,Vec4B& o2,Vec4B& o3,Vec4B& o4)
{
	vector unsigned int t1,t2,t3,t4;
	MatrixTransposeBase((vector unsigned int)i1,
									 (vector unsigned int)i2,
									 (vector unsigned int)i3,
									 (vector unsigned int)i4,
									 t1,t2,t3,t4);
	o1=(Vec4B)t1;
	o2=(Vec4B)t2;
	o3=(Vec4B)t3;
	o4=(Vec4B)t4;
}

#endif //__MATRIX_TRANSPOSE__INCLUDED__

/*
 * Local Variables:
 * mode:C++
 * c-file-style: "stroustrup"
 * tab-width:4
 * End:
 * vim:ts=4:sw=4:
 */
