/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SPU_VECTOR_TABLE__INCLUDED__
#define __SPU_VECTOR_TABLE__INCLUDED__

template <typename index>
struct scalar_vector_table
{
	typedef index this_type;
	typedef void vector_type;
	typedef void scalar_type;
	static const int prefered_slot=0;
	static const int num_slot=1;
	static const enum{NON_VECTORABLE,VECTORABLE,VECTOR} vectorablity=NON_VECTORABLE;
};

#define ScalarVectorTableDefinition_SCALAR(S,V,PS,NS) \
template <> struct scalar_vector_table<S> \
{ \
	typedef S this_type; \
	typedef V vector_type; \
	typedef S scalar_type; \
	static const int prefered_slot=PS; \
	static const int num_slot=NS; \
	static const enum{NON_VECTORABLE,VECTORABLE,VECTOR} vectorablity=VECTORABLE; \
}

#define ScalarVectorTableDefinition_VECTOR(S,V,PS,NS) \
template <> struct scalar_vector_table<V> \
{ \
	typedef V this_type; \
	typedef V vector_type; \
	typedef S scalar_type; \
	static const int prefered_slot=PS; \
	static const int num_slot=NS; \
	static const enum{NON_VECTORABLE,VECTORABLE,VECTOR} vectorablity=VECTOR; \
}

#define ScalarVectorTableDefinition(S,V,PS,NS) \
ScalarVectorTableDefinition_SCALAR(S,V,PS,NS); \
ScalarVectorTableDefinition_VECTOR(S,V,PS,NS) 

ScalarVectorTableDefinition(unsigned char     , vector unsigned char     , 3,16);
ScalarVectorTableDefinition(  signed char     , vector   signed char     , 3,16);
ScalarVectorTableDefinition(unsigned short    , vector unsigned short    , 1, 8);
ScalarVectorTableDefinition(  signed short    , vector   signed short    , 1, 8);
ScalarVectorTableDefinition(unsigned int      , vector unsigned int      , 0, 4);
ScalarVectorTableDefinition(  signed int      , vector   signed int      , 0, 4);
ScalarVectorTableDefinition(unsigned long long, vector unsigned long long, 0, 2);
ScalarVectorTableDefinition(  signed long long, vector   signed long long, 0, 2);
ScalarVectorTableDefinition(  float           , vector   float           , 0, 4);
ScalarVectorTableDefinition(  double          , vector   double          , 0, 2);

#undef ScalarVectorTableDefinition_VECTOR
#undef ScalarVectorTableDefinition_SCALAR
#undef ScalarVectorTableDefinition

#endif
