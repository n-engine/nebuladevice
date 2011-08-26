/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __ORDER_H_INCLUDED__
#define __ORDER_H_INCLUDED__

#include <spu_intrinsics.h>

#define IF0(_x)	if(__builtin_expect((_x),0))
#define IF1(_x)	if(__builtin_expect((_x),1))
#define WHILE0(_x)	while(__builtin_expect((_x),0))
#define WHILE1(_x)	while(__builtin_expect((_x),1))

template<class VECTOR_4B>
static inline 	__attribute__((always_inline))
void Order8by8same(VECTOR_4B t1,VECTOR_4B t2,vector unsigned short& rt)
{
	vector unsigned char x=(vector unsigned char)(0x02,0x03,0x06,0x07,0x0A,0x0B,0x0E,0x0F,
																								0x12,0x13,0x16,0x17,0x1A,0x1B,0x1E,0x1F);



	VECTOR_4B t1_0,t1_1,t1_2,t1_3;
	VECTOR_4B t2_0,t2_1,t2_2,t2_3;
	t1_0=t1;t1_1=spu_rlqwbyte(t1,4);t1_2=spu_rlqwbyte(t1,8);t1_3=spu_rlqwbyte(t1,12);
	t2_0=t2;t2_1=spu_rlqwbyte(t2,4);t2_2=spu_rlqwbyte(t2,8);t2_3=spu_rlqwbyte(t2,12);

	vector unsigned short cr_t1_10,cr_t1_20,cr_t1_30;
	vector unsigned short cr_t2_10,cr_t2_20,cr_t2_30;
	
	vector unsigned short cr_t1_10_t,cr_t1_20_t,cr_t1_30_t;
	vector unsigned short cr_t1_10_f,cr_t1_20_f,cr_t1_30_f;
	vector unsigned short cr_t2_10_t,cr_t2_20_t,cr_t2_30_t;
	vector unsigned short cr_t2_10_f,cr_t2_20_f,cr_t2_30_f;

	cr_t1_10=(vector unsigned short)spu_cmpgt(t1_0,t1_1);
	cr_t1_20=(vector unsigned short)spu_cmpgt(t1_0,t1_2);
	cr_t1_30=(vector unsigned short)spu_cmpgt(t1_0,t1_3);

	cr_t1_10_t=spu_shuffle(cr_t1_10,cr_t1_30,(vector unsigned char)(0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x10,0x11,0x12,0x13));
	cr_t1_20_t=spu_shuffle(cr_t1_20,cr_t1_20,(vector unsigned char)(0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07));
	cr_t1_30_t=spu_shuffle(cr_t1_10,cr_t1_30,(vector unsigned char)(0x10,0x11,0x12,0x13,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B));

	cr_t1_10_f=spu_xor(cr_t1_10_t,spu_maskh(0x03));
	cr_t1_20_f=spu_xor(cr_t1_20_t,spu_maskh(0x0F));
	cr_t1_30_f=spu_xor(cr_t1_30_t,spu_maskh(0x3F));

	cr_t2_10=(vector unsigned short)spu_cmpgt(t2_0,t2_1);
	cr_t2_20=(vector unsigned short)spu_cmpgt(t2_0,t2_2);
	cr_t2_30=(vector unsigned short)spu_cmpgt(t2_0,t2_3);

	cr_t2_10_t=spu_shuffle(cr_t2_10,cr_t2_30,(vector unsigned char)(0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x10,0x11,0x12,0x13));
	cr_t2_20_t=spu_shuffle(cr_t2_20,cr_t2_20,(vector unsigned char)(0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07));
	cr_t2_30_t=spu_shuffle(cr_t2_10,cr_t2_30,(vector unsigned char)(0x10,0x11,0x12,0x13,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B));

	cr_t2_10_f=spu_xor(cr_t2_10_t,spu_maskh(0x03));
	cr_t2_20_f=spu_xor(cr_t2_20_t,spu_maskh(0x0F));
	cr_t2_30_f=spu_xor(cr_t2_30_t,spu_maskh(0x3F));
	
	vector unsigned short cr_t21_00,cr_t21_10,cr_t21_20,cr_t21_30;
	vector unsigned short cr_t21_00_t,cr_t21_10_t,cr_t21_20_t,cr_t21_30_t;
	vector unsigned short cr_t21_00_f,cr_t21_10_f,cr_t21_20_f,cr_t21_30_f;
		
	cr_t21_00=(vector unsigned short)spu_cmpgt(t1_0,t2_0);
	cr_t21_10=(vector unsigned short)spu_cmpgt(t1_0,t2_1);
	cr_t21_20=(vector unsigned short)spu_cmpgt(t1_0,t2_2);
	cr_t21_30=(vector unsigned short)spu_cmpgt(t1_0,t2_3);
	
	cr_t21_00_t=cr_t21_00;
	cr_t21_10_t=spu_rlqwbyte(cr_t21_10,12);
	cr_t21_20_t=spu_rlqwbyte(cr_t21_20,8);
	cr_t21_30_t=spu_rlqwbyte(cr_t21_30,4);


	cr_t21_00_f=spu_xor(cr_t21_00_t,(vector unsigned short)(0xFFFF));
	cr_t21_10_f=spu_xor(cr_t21_10_t,(vector unsigned short)(0xFFFF));
	cr_t21_20_f=spu_xor(cr_t21_20_t,(vector unsigned short)(0xFFFF));
	cr_t21_30_f=spu_xor(cr_t21_30_t,(vector unsigned short)(0xFFFF));

	vector unsigned short cr_r1_1,cr_r1_2,cr_r1_3;
	vector unsigned short cr_r2_0,cr_r2_1,cr_r2_2,cr_r2_3;

	cr_r1_1=spu_shuffle(cr_t1_10_f,cr_t2_10_f,x);
	cr_r1_2=spu_shuffle(cr_t1_20_f,cr_t2_20_f,x);
	cr_r1_3=spu_shuffle(cr_t1_30_f,cr_t2_30_f,x);
	
	cr_r2_0=spu_shuffle(cr_t21_00,cr_t21_00_f,x);
	cr_r2_1=spu_shuffle(cr_t21_10,cr_t21_10_f,x);
	cr_r2_2=spu_shuffle(cr_t21_20,cr_t21_20_f,x);
	cr_r2_3=spu_shuffle(cr_t21_30,cr_t21_30_f,x);

	rt=spu_sub((vector unsigned short)(0), spu_add(spu_add(spu_add(cr_r1_1,cr_r1_2),cr_r1_3), spu_add(spu_add(cr_r2_0,cr_r2_1),spu_add(cr_r2_2,cr_r2_3))));
}

template<class VECTOR_4B>
static inline 	__attribute__((always_inline))
void Order8by8(VECTOR_4B t1,VECTOR_4B t2,VECTOR_4B d1,VECTOR_4B d2,vector unsigned short& rt,vector unsigned short& rd)
{
	VECTOR_4B d1_0,d1_1,d1_2,d1_3;
	VECTOR_4B d2_0,d2_1,d2_2,d2_3;
	vector unsigned short ct_11_0,ct_11_1,ct_11_2,ct_11_3;
	vector unsigned short ct_12_0,ct_12_1,ct_12_2,ct_12_3;
	vector unsigned short ct_21_0,ct_21_1,ct_21_2,ct_21_3;
	vector unsigned short ct_22_0,ct_22_1,ct_22_2,ct_22_3;

	vector unsigned short ct_1_0,ct_1_1,ct_1_2,ct_1_3;
	vector unsigned short ct_2_0,ct_2_1,ct_2_2,ct_2_3;

	vector unsigned short cd_1_0,cd_1_1,cd_1_2,cd_1_3;
	vector unsigned short cd_2_0,cd_2_1,cd_2_2,cd_2_3;
	
	vector unsigned char x_0=(vector unsigned char)(0x02,0x03,0x06,0x07,0x0A,0x0B,0x0E,0x0F,
																								0x12,0x13,0x16,0x17,0x1A,0x1B,0x1E,0x1F);
	vector unsigned char x_3=(vector unsigned char)(0x0E,0x0F,0x02,0x03,0x06,0x07,0x0A,0x0B,
																								0x1E,0x1F,0x12,0x13,0x16,0x17,0x1A,0x1B);
	vector unsigned char x_2=(vector unsigned char)(0x0A,0x0B,0x0E,0x0F,0x02,0x03,0x06,0x07,
																								0x1A,0x1B,0x1E,0x1F,0x12,0x13,0x16,0x17);
	vector unsigned char x_1=(vector unsigned char)(0x06,0x07,0x0A,0x0B,0x0E,0x0F,0x02,0x03,
																								0x16,0x17,0x1A,0x1B,0x1E,0x1F,0x12,0x13);
	


	d1_0=d1;
	d1_1=spu_rlqwbyte(d1,4);
	d1_2=spu_rlqwbyte(d1,8);
	d1_3=spu_rlqwbyte(d1,12);
	d2_0=d2;
	d2_1=spu_rlqwbyte(d2,4);
	d2_2=spu_rlqwbyte(d2,8);
	d2_3=spu_rlqwbyte(d2,12);
	
	ct_11_0=(vector unsigned short)spu_cmpgt(t1,d1_0);
	ct_11_1=(vector unsigned short)spu_cmpgt(t1,d1_1);
	ct_11_2=(vector unsigned short)spu_cmpgt(t1,d1_2);
	ct_11_3=(vector unsigned short)spu_cmpgt(t1,d1_3);
	ct_12_0=(vector unsigned short)spu_cmpgt(t1,d2_0);
	ct_12_1=(vector unsigned short)spu_cmpgt(t1,d2_1);
	ct_12_2=(vector unsigned short)spu_cmpgt(t1,d2_2);
	ct_12_3=(vector unsigned short)spu_cmpgt(t1,d2_3);
	ct_21_0=(vector unsigned short)spu_cmpgt(t2,d1_0);
	ct_21_1=(vector unsigned short)spu_cmpgt(t2,d1_1);
	ct_21_2=(vector unsigned short)spu_cmpgt(t2,d1_2);
	ct_21_3=(vector unsigned short)spu_cmpgt(t2,d1_3);
	ct_22_0=(vector unsigned short)spu_cmpgt(t2,d2_0);
	ct_22_1=(vector unsigned short)spu_cmpgt(t2,d2_1);
	ct_22_2=(vector unsigned short)spu_cmpgt(t2,d2_2);
	ct_22_3=(vector unsigned short)spu_cmpgt(t2,d2_3);
	
	ct_1_0=spu_shuffle(ct_11_0,ct_21_0,x_0);
	ct_1_1=spu_shuffle(ct_11_1,ct_21_1,x_0);
	ct_1_2=spu_shuffle(ct_11_2,ct_21_2,x_0);
	ct_1_3=spu_shuffle(ct_11_3,ct_21_3,x_0);
	ct_2_0=spu_shuffle(ct_12_0,ct_22_0,x_0);
	ct_2_1=spu_shuffle(ct_12_1,ct_22_1,x_0);
	ct_2_2=spu_shuffle(ct_12_2,ct_22_2,x_0);
	ct_2_3=spu_shuffle(ct_12_3,ct_22_3,x_0);

	cd_1_0=spu_shuffle(ct_11_0,ct_12_0,x_0);
	cd_1_1=spu_shuffle(ct_11_1,ct_12_1,x_3);
	cd_1_2=spu_shuffle(ct_11_2,ct_12_2,x_2);
	cd_1_3=spu_shuffle(ct_11_3,ct_12_3,x_1);
	cd_2_0=spu_shuffle(ct_21_0,ct_22_0,x_0);
	cd_2_1=spu_shuffle(ct_21_1,ct_22_1,x_3);
	cd_2_2=spu_shuffle(ct_21_2,ct_22_2,x_2);
	cd_2_3=spu_shuffle(ct_21_3,ct_22_3,x_1);
	

	rt=spu_sub((unsigned short)0
						 ,spu_add(spu_add(spu_add(ct_1_0,ct_2_0)
															,spu_add(ct_1_1,ct_2_1))
											,spu_add(spu_add(ct_1_2,ct_2_2)
															,spu_add(ct_1_3,ct_2_3))));
	rd=spu_add(spu_add(spu_add(spu_add(cd_1_0,cd_2_0)
															,spu_add(cd_1_1,cd_2_1))
											,spu_add(spu_add(cd_1_2,cd_2_2)
															,spu_add(cd_1_3,cd_2_3)))
						 ,(unsigned short)8);

}

template<class VECTOR_4B>
void Order(const VECTOR_4B* data,vector unsigned short* order,int num)
// num must be 8 x X.
{
	int i,j;
	vector unsigned short rv1,rv2;
	{
		const VECTOR_4B* i_data;
		vector unsigned short* i_order;
		i_data=data;
		i_order=order;
		for(i=0;i<num;i+=8)
		{
			Order8by8same(i_data[0],i_data[1],i_order[0]);
			i_data+=2;
			i_order++;
		}
	}
	{
		i=0;j=8;
		const VECTOR_4B* i_data;
		const VECTOR_4B* j_data;
		vector unsigned short* i_order;
		vector unsigned short* j_order;
		i_data=data;
		j_data=data+2;
		i_order=order;
		j_order=order+1;
		IF1(num>8)
		{
			do{
				Order8by8(i_data[0],i_data[1],j_data[0],j_data[1],rv1,rv2);
				i_order[0]=spu_add(i_order[0],rv1);
				j_order[0]=spu_add(j_order[0],rv2);
				j=j+8;
				i      =(j<num)?i:i+8;
				i_data =(j<num)?i_data:i_data+2;
				i_order=(j<num)?i_order:i_order+1;
				j_data =(j<num)?j_data+2:i_data+2;
				j_order=(j<num)?j_order+1:i_order+1;
				j=(j<num)?j:i+8;
			}while(i<num-8);
		}
	}
}


#endif  //__ORDER_H_INCLUDED__
