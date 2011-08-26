/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __OE_MERGESORT_H_INCLUDED__
#define __OE_MERGESORT_H_INCLUDED__

template <class VectorizedKey>
void OddEvenMergeSort(VectorizedKey* key,vector unsigned int* data,int num);

//////////////////////////////////////////////////////////////////////////////////////

#include <spu_intrinsics.h>
#include "spuvectortable.h"
#include <limits>

template <class VectorizedKey>
static void OddEvenMergeSortSub_diff2and1Odd(VectorizedKey* key,vector unsigned int* data,int num,int pass_cyc)
{
	VectorizedKey ek_now,ek_next;
	vector unsigned int ed_now,ed_next;
	ek_now=key[0];
	ed_now=data[0];
	vector unsigned char mask_diff2=(vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0,0,0);
	vector unsigned char mask_diff1=(vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0,0,0,0);
	pass_cyc=(pass_cyc+1)/4;
	int pass=pass_cyc;
	for(int i=0;i<num/8;i++)
	{
		vector unsigned int data1,data2,dt1,dt2;
		VectorizedKey v_key1,v_key2,kt1,kt2;
		vector unsigned char comp;
		pass--;
		vector unsigned char mask_now_diff2=(pass)?(vector unsigned char)(0xFF):mask_diff2;
		vector unsigned char mask_now_diff1=(pass)?(vector unsigned char)(0xFF):mask_diff1;
		pass=(pass)?pass:pass_cyc;
		
		ek_next=key[i*2+2];
		ed_next=data[i*2+2];
		kt2=key[i*2+1];
		dt2=data[i*2+1];
		
		v_key1=spu_shuffle(ek_now ,kt2,(vector unsigned char)( 8, 9,10,11,12,13,14,15,24,25,26,27,28,29,30,31));
		v_key2=spu_shuffle(ek_next,kt2,(vector unsigned char)(16,17,18,19,20,21,22,23, 0, 1, 2, 3, 4, 5, 6, 7));
		data1=spu_shuffle(ed_now ,dt2, (vector unsigned char)( 8, 9,10,11,12,13,14,15,24,25,26,27,28,29,30,31));
		data2=spu_shuffle(ed_next,dt2, (vector unsigned char)(16,17,18,19,20,21,22,23, 0, 1, 2, 3, 4, 5, 6, 7));
		comp=(vector unsigned char)spu_cmpgt(v_key1,v_key2);
		comp=spu_and(mask_now_diff2,comp);
		kt1=spu_sel(v_key1,v_key2,comp);
		kt2=spu_sel(v_key2,v_key1,comp);
		dt1=spu_sel(data1,data2,comp);
		dt2=spu_sel(data2,data1,comp);
		
		v_key1 =spu_shuffle(ek_now ,kt2,(vector unsigned char)( 4, 5, 6, 7, 0, 0, 0, 0,20,21,22,23, 0, 0, 0, 0));
		v_key2 =spu_shuffle(kt1    ,kt2,(vector unsigned char)( 0, 1, 2, 3,16,17,18,19, 8, 9,10,11,24,25,26,27));
		v_key1 =spu_sel(v_key1,kt1,(vector unsigned char)(0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF));
		ek_next=spu_shuffle(ek_next,kt2,(vector unsigned char)( 0, 0, 0, 0,28,29,30,31, 8, 9,10,11,12,13,14,15));
		
		data1  =spu_shuffle(ed_now ,dt2,(vector unsigned char)( 4, 5, 6, 7, 0, 0, 0, 0,20,21,22,23, 0, 0, 0, 0));
		data2  =spu_shuffle(dt1    ,dt2,(vector unsigned char)( 0, 1, 2, 3,16,17,18,19, 8, 9,10,11,24,25,26,27));
		data1 =spu_sel(data1,dt1,(vector unsigned char)(0,0,0,0,0xFF,0xFF,0xFF,0xFF,0,0,0,0,0xFF,0xFF,0xFF,0xFF));
		ed_next=spu_shuffle(ed_next,dt2,(vector unsigned char)( 0, 0, 0, 0,28,29,30,31, 8, 9,10,11,12,13,14,15));
		
		comp=(vector unsigned char)spu_cmpgt(v_key1,v_key2);
		comp=spu_and(mask_now_diff1,comp);
		kt1=spu_sel(v_key1,v_key2,comp);
		kt2=spu_sel(v_key2,v_key1,comp);
		dt1=spu_sel(data1,data2,comp);
		dt2=spu_sel(data2,data1,comp);
		v_key1=spu_shuffle(kt1,kt2,(vector unsigned char)(28,29,30,31, 0, 1, 2, 3,16,17,18,19, 4, 5, 6, 7));
		v_key2=spu_shuffle(kt1,kt2,(vector unsigned char)(20,21,22,23, 8, 9,10,11,24,25,26,27,12,13,14,15));
		data1=spu_shuffle(dt1,dt2, (vector unsigned char)(28,29,30,31, 0, 1, 2, 3,16,17,18,19, 4, 5, 6, 7));
		data2=spu_shuffle(dt1,dt2, (vector unsigned char)(20,21,22,23, 8, 9,10,11,24,25,26,27,12,13,14,15));
		key[i*2]  =spu_sel(v_key1,ek_now,(vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0,0,0,0,0,0,0));
		key[i*2+1]=v_key2;
		data[i*2]  =spu_sel(data1,ed_now,(vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0,0,0,0,0,0,0));
		data[i*2+1]=data2;
		ek_now=spu_sel(ek_next,v_key1,(vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0,0,0,0,0,0,0));
		ed_now=spu_sel(ed_next,data1, (vector unsigned char)(0xFF,0xFF,0xFF,0xFF,0,0,0,0,0,0,0,0,0,0,0,0));
	}
}

template <class VectorizedKey>
static void OddEvenMergeSortSub_QWComp(VectorizedKey* key,vector unsigned int* data,int num,int init,int pass_cyc)
{
	int max_num=init;
	VectorizedKey* k_i=key+(init/4);
	vector unsigned int* d_i=data+(init/4);
	int pass=pass_cyc;
	int i=0;
	while(1)
	{
		vector unsigned int data_a1,data_a2,data_b1,data_b2;
		VectorizedKey v_key_a1,v_key_a2,v_key_b1,v_key_b2;
		vector unsigned char comp1,comp2;
		
		pass--;
		
		if(max_num+i*16>=num)
			return;
		v_key_a1=k_i[i*4  ];
		v_key_b1=k_i[i*4+1];
		v_key_a2=k_i[i*4+2];
		v_key_b2=k_i[i*4+3];
		data_a1=d_i[i*4  ];
		data_b1=d_i[i*4+1];
		data_a2=d_i[i*4+2];
		data_b2=d_i[i*4+3];
		comp1=(vector unsigned char)spu_cmpgt(v_key_a1,v_key_b1);
		comp2=(vector unsigned char)spu_cmpgt(v_key_a2,v_key_b2);
		k_i[i*4  ]=spu_sel(v_key_a1,v_key_b1,comp1);
		k_i[i*4+1]=spu_sel(v_key_b1,v_key_a1,comp1);
		d_i[i*4  ]=spu_sel(data_a1,data_b1,comp1);
		d_i[i*4+1]=spu_sel(data_b1,data_a1,comp1);
		comp2=(pass)?comp2:(vector unsigned char)(0);
		if(max_num+i*16+8>=num)
			return;
		k_i[i*4+2]=spu_sel(v_key_a2,v_key_b2,comp2);
		k_i[i*4+3]=spu_sel(v_key_b2,v_key_a2,comp2);
		d_i[i*4+2]=spu_sel(data_a2,data_b2,comp2);
		d_i[i*4+3]=spu_sel(data_b2,data_a2,comp2);
		pass=(pass)?pass:pass_cyc;
		i++;
	}
}

template <class VectorizedKey>
static void OddEvenMergeSortSub_2QWComp(VectorizedKey* key,vector unsigned int* data,int num,int init,int diff,int pass_cyc)
{
	int max_num=init;
	VectorizedKey* k_i=key+(init/4);
	vector unsigned int* d_i=data+(init/4);
	int pass=pass_cyc;
	while(1)
	{
		for(int i=0;i<(diff/8);i++)
		{
			vector unsigned int data_a1,data_a2,data_b1,data_b2;
			VectorizedKey v_key_a1,v_key_a2,v_key_b1,v_key_b2;
			vector unsigned char comp1,comp2;
			
			if(max_num+diff+i*8>=num)
				return;
			v_key_a1=k_i[i*2  ];
			v_key_a2=k_i[i*2+1];
			v_key_b1=k_i[i*2  +diff/4];
			v_key_b2=k_i[i*2+1+diff/4];
			data_a1=d_i[i*2  ];
			data_a2=d_i[i*2+1];
			data_b1=d_i[i*2  +diff/4];
			data_b2=d_i[i*2+1+diff/4];
			comp1=(vector unsigned char)spu_cmpgt(v_key_a1,v_key_b1);
			comp2=(vector unsigned char)spu_cmpgt(v_key_a2,v_key_b2);
			k_i[i*2  ]       =spu_sel(v_key_a1,v_key_b1,comp1);
			k_i[i*2+1]       =spu_sel(v_key_a2,v_key_b2,comp2);
			k_i[i*2  +diff/4]=spu_sel(v_key_b1,v_key_a1,comp1);
			k_i[i*2+1+diff/4]=spu_sel(v_key_b2,v_key_a2,comp2);
			d_i[i*2  ]       =spu_sel(data_a1,data_b1,comp1);
			d_i[i*2+1]       =spu_sel(data_a2,data_b2,comp2);
			d_i[i*2  +diff/4]=spu_sel(data_b1,data_a1,comp1);
			d_i[i*2+1+diff/4]=spu_sel(data_b2,data_a2,comp2);
		}
		pass--;
		k_i+=(pass)?(diff/2):diff;
		d_i+=(pass)?(diff/2):diff;
		max_num+=(pass)?(diff*2):(diff*4);
		pass=(pass)?pass:pass_cyc;
	}
}

#include "matrix_transpose.h"

template <class VectorizedKey>
static void OddEvenMergeSortSub_12combo(VectorizedKey* key,vector unsigned int* data,int num)
{
	int loop_cnt=(num-1)/16;
	VectorizedKey key1,key2,key3,key4;
	vector unsigned int data1,data2,data3,data4;

	VectorizedKey kt11,kt12,kt13,kt14;
	VectorizedKey kt22,kt23;
	VectorizedKey kr1,kr2,kr3,kr4;
	vector unsigned int dt11,dt12,dt13,dt14;
	vector unsigned int dt22,dt23;
	vector unsigned int dr1,dr2,dr3,dr4;
	vector unsigned char cmp1,cmp2,cmp3,cmp4,cmp5;
	
	VectorizedKey skey1,skey2,skey3,skey4;
	vector unsigned int sdata1,sdata2,sdata3,sdata4;
	
	
	for(int i=0;i<loop_cnt;i++)
	{
// Load Stage
		key1=key[i*4+0];
		key2=key[i*4+1];
		key3=key[i*4+2];
		key4=key[i*4+3];
		data1=data[i*4+0];
		data2=data[i*4+1];
		data3=data[i*4+2];
		data4=data[i*4+3];
// compare Stage
		cmp1=(vector unsigned char)spu_cmpgt(key1,key2);
		cmp2=(vector unsigned char)spu_cmpgt(key3,key4);
		kt11=spu_sel(key1,key2,cmp1);
		kt12=spu_sel(key2,key1,cmp1);
		kt13=spu_sel(key3,key4,cmp2);
		kt14=spu_sel(key4,key3,cmp2);
		dt11=spu_sel(data1,data2,cmp1);
		dt12=spu_sel(data2,data1,cmp1);
		dt13=spu_sel(data3,data4,cmp2);
		dt14=spu_sel(data4,data3,cmp2);
		cmp3=(vector unsigned char)spu_cmpgt(kt11,kt13);
		cmp4=(vector unsigned char)spu_cmpgt(kt12,kt14);
		kr1 =spu_sel(kt11,kt13,cmp3);
		kt23=spu_sel(kt13,kt11,cmp3);
		kt22=spu_sel(kt12,kt14,cmp4);
		kr4 =spu_sel(kt14,kt12,cmp4);
		dr1 =spu_sel(dt11,dt13,cmp3);
		dt23=spu_sel(dt13,dt11,cmp3);
		dt22=spu_sel(dt12,dt14,cmp4);
		dr4 =spu_sel(dt14,dt12,cmp4);
		cmp5=(vector unsigned char)spu_cmpgt(kt22,kt23);
		kr2=spu_sel(kt22,kt23,cmp5);
		kr3=spu_sel(kt23,kt22,cmp5);
		dr2=spu_sel(dt22,dt23,cmp5);
		dr3=spu_sel(dt23,dt22,cmp5);

		
// Store Stage
		MatrixTranspose(kr1,kr2,kr3,kr4,skey1,skey2,skey3,skey4);
		MatrixTranspose(dr1,dr2,dr3,dr4,sdata1,sdata2,sdata3,sdata4);
		key[i*4+0]=skey1;
		key[i*4+1]=skey2;
		key[i*4+2]=skey3;
		key[i*4+3]=skey4;
		data[i*4+0]=sdata1;
		data[i*4+1]=sdata2;
		data[i*4+2]=sdata3;
		data[i*4+3]=sdata4;
	}
// Load Stage
	key1=key[loop_cnt*4+0];
	key2=key[loop_cnt*4+1];
	key3=key[loop_cnt*4+2];
	key4=key[loop_cnt*4+3];
	data1=data[loop_cnt*4+0];
	data2=data[loop_cnt*4+1];
	data3=data[loop_cnt*4+2];
	data4=data[loop_cnt*4+3];

	MatrixTranspose(key1,key2,key3,key4,key1,key2,key3,key4);
	MatrixTranspose(data1,data2,data3,data4,data1,data2,data3,data4);

// compare Stage
	cmp1=(vector unsigned char)spu_cmpgt(key1,key2);
	cmp2=(vector unsigned char)spu_cmpgt(key3,key4);
	kt11=spu_sel(key1,key2,cmp1);
	kt12=spu_sel(key2,key1,cmp1);
	kt13=spu_sel(key3,key4,cmp2);
	kt14=spu_sel(key4,key3,cmp2);
	dt11=spu_sel(data1,data2,cmp1);
	dt12=spu_sel(data2,data1,cmp1);
	dt13=spu_sel(data3,data4,cmp2);
	dt14=spu_sel(data4,data3,cmp2);
	cmp3=(vector unsigned char)spu_cmpgt(kt11,kt13);
	cmp4=(vector unsigned char)spu_cmpgt(kt12,kt14);
	kr1 =spu_sel(kt11,kt13,cmp3);
	kt23=spu_sel(kt13,kt11,cmp3);
	kt22=spu_sel(kt12,kt14,cmp4);
	kr4 =spu_sel(kt14,kt12,cmp4);
	dr1 =spu_sel(dt11,dt13,cmp3);
	dt23=spu_sel(dt13,dt11,cmp3);
	dt22=spu_sel(dt12,dt14,cmp4);
	dr4 =spu_sel(dt14,dt12,cmp4);
	cmp5=(vector unsigned char)spu_cmpgt(kt22,kt23);
	kr2=spu_sel(kt22,kt23,cmp5);
	kr3=spu_sel(kt23,kt22,cmp5);
	dr2=spu_sel(dt22,dt23,cmp5);
	dr3=spu_sel(dt23,dt22,cmp5);

	
// Store Stage
	MatrixTranspose(kr1,kr2,kr3,kr4,skey1,skey2,skey3,skey4);
	MatrixTranspose(dr1,dr2,dr3,dr4,sdata1,sdata2,sdata3,sdata4);
	
	key[loop_cnt*4+0]=skey1;
	key[loop_cnt*4+1]=skey2;
	key[loop_cnt*4+2]=skey3;
	key[loop_cnt*4+3]=skey4;
	data[loop_cnt*4+0]=sdata1;
	data[loop_cnt*4+1]=sdata2;
	data[loop_cnt*4+2]=sdata3;
	data[loop_cnt*4+3]=sdata4;
}

template <class VectorizedKey>
void OddEvenMergeSort(VectorizedKey* key,vector unsigned int* data,int num)
{
	int i,j;
	if(num<=0)return;
	OddEvenMergeSortSub_12combo(key,data,num);
	OddEvenMergeSortSub_QWComp(key,data,num,0,num);
	OddEvenMergeSortSub_diff2and1Odd(key,data,num,3);
	for(i=4;(1<<(i-1))<num;i++)
	{
		OddEvenMergeSortSub_2QWComp(key,data,num,0,1<<(i-1),num);
		for(j=1;j<i-3;j++)
		{
			OddEvenMergeSortSub_2QWComp(key,data,num,1<<(i-j-1),1<<(i-j-1),(1<<j)-1);
		}
		OddEvenMergeSortSub_QWComp(key,data,num,4,(1<<(i-4)));
		OddEvenMergeSortSub_diff2and1Odd(key,data,num,(1<<(i-1))-1);
	}
}



#endif  //__OE_MERGESORT_H_INCLUDED__

/*
 * Local Variables:
 * mode:C++
 * c-file-style: "stroustrup"
 * tab-width:4
 * End:
 * vim:ts=4:sw=4:
 */
