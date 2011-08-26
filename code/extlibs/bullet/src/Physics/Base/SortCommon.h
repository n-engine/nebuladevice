/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SORT_COMMON_H__
#define __SORT_COMMON_H__

#include "Physics/Base/PhysicsCommon.h"
#include "Physics/Base/PfxHandle.h"

/*
	* Structure of vdata
	32bit +-------+-------+-------+-------+
	          0       1       2       3
	16bit +---+---+---+---+---+---+---+---+
	        0   1   2   3   4   5   6   7
	 8bit +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	       0 1 2 3 4 5 6 7 8 9 A B C D E F
 */

#define NULL_KEY	0xffffffff

#ifdef WIN32
	#pragma warning(disable: 4311)
	#pragma warning(disable: 4312)
	#pragma warning(disable: 4819)

	struct SortData {
		uint32_t vdata[2][4];
	};
#else
	struct SortData {
		vec_uint4 vdata[2];
	} __attribute__ ((aligned(16)));
#endif

typedef SortData PfxBroadphaseProxy;
typedef SortData PfxBroadphasePair;
typedef SortData PfxConstraintPtr;

#ifdef WIN32
	#define PFX_SET8(v,i,a)  *((uint8_t*)v+i) = (uint8_t)a;
	#define PFX_SET16(v,i,a) *((uint16_t*)v+i) = (uint16_t)a;
	#define PFX_SET32(v,i,a) *(v+i) = (uint32_t)a;
	#define PFX_GET8(v,i)  *((uint8_t*)v+i);
	#define PFX_GET16(v,i) *((uint16_t*)v+i);
	#define PFX_GET32(v,i) *(v+i);
#else
	#ifdef __PPU__
		#include <spu2vmx.h>
	#endif
	#define PFX_SET8(v,i,a)  v=(vec_uint4)spu_insert((uint8_t)a,(vec_uchar16)v,i);
	#define PFX_SET16(v,i,a) v=(vec_uint4)spu_insert((uint16_t)a,(vec_ushort8)v,i);
	#define PFX_SET32(v,i,a) v=(vec_uint4)spu_insert((uint32_t)a,(vec_uint4)v,i);
	#define PFX_GET8(v,i)  spu_extract((vec_uchar16)v,i);
	#define PFX_GET16(v,i) spu_extract((vec_ushort8)v,i);
	#define PFX_GET32(v,i) spu_extract((vec_uint4)v,i);
#endif

inline static void setKey(SortData& s,uint32_t key) {PFX_SET32(s.vdata[1],3,key);}
inline static uint32_t Key(const SortData& s)       {return PFX_GET32(s.vdata[1],3);}

//J ブロードフェーズペア
//E Broadphase Pair
inline static void setUserData(PfxBroadphasePair& s,PfxHandle c)       {PFX_SET32(s.vdata[0],0,(uint32_t)c);}
inline static void setStateA(PfxBroadphasePair& s,PfxHandle i)         {PFX_SET32(s.vdata[0],1,(uint32_t)i);}
inline static void setStateB(PfxBroadphasePair& s,PfxHandle i)         {PFX_SET32(s.vdata[0],2,(uint32_t)i);}
inline static void setBodyA(PfxBroadphasePair& s,PfxHandle i)          {PFX_SET32(s.vdata[0],3,(uint32_t)i);}
inline static void setBodyB(PfxBroadphasePair& s,PfxHandle i)          {PFX_SET32(s.vdata[1],0,(uint32_t)i);}
inline static void setUniqueIdA(PfxBroadphasePair& s,uint16_t i)       {PFX_SET16(s.vdata[1],2,i);}
inline static void setUniqueIdB(PfxBroadphasePair& s,uint16_t i)       {PFX_SET16(s.vdata[1],3,i);}
inline static void setMovA(PfxBroadphasePair& s,uint8_t i)             {PFX_SET8(s.vdata[1],8,i);}
inline static void setMovB(PfxBroadphasePair& s,uint8_t i)             {PFX_SET8(s.vdata[1],9,i);}
inline static void setUpdatedFlag(PfxBroadphasePair& s,uint8_t f)      {PFX_SET8(s.vdata[1],10,f);}
inline static void setCallbackFlag(PfxBroadphasePair& s,uint8_t f)     {PFX_SET8(s.vdata[1],11,f);}

inline static PfxHandle UserData(const PfxBroadphasePair& s)     {return (PfxHandle)PFX_GET32(s.vdata[0],0);}
inline static PfxHandle StateA(const PfxBroadphasePair& s)       {return (PfxHandle)PFX_GET32(s.vdata[0],1);}
inline static PfxHandle StateB(const PfxBroadphasePair& s)       {return (PfxHandle)PFX_GET32(s.vdata[0],2);}
inline static PfxHandle BodyA(const PfxBroadphasePair& s)        {return (PfxHandle)PFX_GET32(s.vdata[0],3);}
inline static PfxHandle BodyB(const PfxBroadphasePair& s)        {return (PfxHandle)PFX_GET32(s.vdata[1],0);}
inline static uint16_t  UniqueIdA(const PfxBroadphasePair& s)    {return PFX_GET16(s.vdata[1],2);}
inline static uint16_t  UniqueIdB(const PfxBroadphasePair& s)    {return PFX_GET16(s.vdata[1],3);}
inline static uint8_t   MovA(const PfxBroadphasePair& s)         {return PFX_GET8(s.vdata[1],8);}
inline static uint8_t   MovB(const PfxBroadphasePair& s)         {return PFX_GET8(s.vdata[1],9);}
inline static uint8_t   UpdatedFlag(const PfxBroadphasePair& s)  {return PFX_GET8(s.vdata[1],10);}
inline static uint8_t   CallbackFlag(const PfxBroadphasePair& s) {return PFX_GET8(s.vdata[1],11);}

//J コンストレイントペア
//E Constraint Pair
inline static void setUserConstraint(PfxConstraintPtr& s,PfxHandle c)   {PFX_SET32(s.vdata[0],0,(uint32_t)c);}
inline static void setConstraintRowId(PfxConstraintPtr& s,uint32_t c)   {PFX_SET32(s.vdata[0],1,c);}
inline static void setSolverBodyA(PfxConstraintPtr& s,PfxHandle i)      {PFX_SET32(s.vdata[0],2,(uint32_t)i);}
inline static void setSolverBodyB(PfxConstraintPtr& s,PfxHandle i)      {PFX_SET32(s.vdata[0],3,(uint32_t)i);}
inline static void setUserObjectA(PfxConstraintPtr& s,PfxHandle i)      {PFX_SET32(s.vdata[1],0,(uint32_t)i);}
inline static void setUserObjectB(PfxConstraintPtr& s,PfxHandle i)      {PFX_SET32(s.vdata[1],1,(uint32_t)i);}
inline static void setSolverUniqueIdA(PfxBroadphasePair& s,uint16_t i)  {PFX_SET16(s.vdata[1],4,i);}
inline static void setSolverUniqueIdB(PfxBroadphasePair& s,uint16_t i)  {PFX_SET16(s.vdata[1],5,i);}
inline static void setNumConstraintRows(PfxConstraintPtr& s,uint32_t c) {PFX_SET8(s.vdata[1],12,c);}
inline static void setIsStaticA(PfxBroadphasePair& s,uint8_t i)          {PFX_SET8(s.vdata[1],13,i);}
inline static void setIsStaticB(PfxBroadphasePair& s,uint8_t i)          {PFX_SET8(s.vdata[1],14,i);}

inline static PfxHandle UserConstraint(const PfxConstraintPtr& s)    {return (PfxHandle)PFX_GET32(s.vdata[0],0);}
inline static uint32_t  ConstraintRowId(const PfxConstraintPtr& s)   {return PFX_GET32(s.vdata[0],1);}
inline static PfxHandle SolverBodyA(const PfxConstraintPtr& s)       {return (PfxHandle)PFX_GET32(s.vdata[0],2);}
inline static PfxHandle SolverBodyB(const PfxConstraintPtr& s)       {return (PfxHandle)PFX_GET32(s.vdata[0],3);}
inline static PfxHandle UserObjectA(const PfxConstraintPtr& s)       {return (PfxHandle)PFX_GET32(s.vdata[1],0);}
inline static PfxHandle UserObjectB(const PfxConstraintPtr& s)       {return (PfxHandle)PFX_GET32(s.vdata[1],1);}
inline static uint16_t SolverUniqueIdA(const PfxConstraintPtr& s)    {return PFX_GET16(s.vdata[1],4);}
inline static uint16_t SolverUniqueIdB(const PfxConstraintPtr& s)    {return PFX_GET16(s.vdata[1],5);}
inline static uint8_t  NumConstraintRows(const PfxConstraintPtr& s)  {return PFX_GET8(s.vdata[1],12);}
inline static uint8_t  IsStaticA(const PfxConstraintPtr& s)           {return PFX_GET8(s.vdata[1],13);}
inline static uint8_t  IsStaticB(const PfxConstraintPtr& s)           {return PFX_GET8(s.vdata[1],14);}

//J ブロードフェーズプロキシ
//E Broadphase Proxy
inline static void setXMin(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],0,i);}
inline static void setXMax(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],1,i);}
inline static void setYMin(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],2,i);}
inline static void setYMax(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],3,i);}
inline static void setZMin(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],4,i);}
inline static void setZMax(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[0],5,i);}
inline static void setXYZMin(PfxBroadphaseProxy& s,uint16_t i,int axis) {PFX_SET16(s.vdata[0],axis*2,i);}
inline static void setXYZMax(PfxBroadphaseProxy& s,uint16_t i,int axis) {PFX_SET16(s.vdata[0],axis*2+1,i);}

inline static uint16_t XMin(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],0);}
inline static uint16_t XMax(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],1);}
inline static uint16_t YMin(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],2);}
inline static uint16_t YMax(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],3);}
inline static uint16_t ZMin(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],4);}
inline static uint16_t ZMax(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[0],5);}
inline static uint16_t XYZMin(const PfxBroadphaseProxy& s,int axis) {return PFX_GET16(s.vdata[0],axis*2);}
inline static uint16_t XYZMax(const PfxBroadphaseProxy& s,int axis) {return PFX_GET16(s.vdata[0],axis*2+1);}

inline static void setState(PfxBroadphaseProxy& s,PfxHandle i)   {PFX_SET32(s.vdata[0],3,(uint32_t)i);}
inline static void setBody(PfxBroadphaseProxy& s,PfxHandle i)    {PFX_SET32(s.vdata[1],0,(uint32_t)i);}
inline static void setUniqueId(PfxBroadphaseProxy& s,uint16_t i) {PFX_SET16(s.vdata[1],2,i);}
inline static void setMovType(PfxBroadphaseProxy& s,uint8_t i)   {PFX_SET8(s.vdata[1],6,i);}
inline static void setCallback(PfxBroadphaseProxy& s,uint8_t i)  {PFX_SET8(s.vdata[1],7,i);}
inline static void setSelf(PfxBroadphaseProxy& s,uint16_t i)     {PFX_SET16(s.vdata[1],4,i);}
inline static void setTarget(PfxBroadphaseProxy& s,uint16_t i)   {PFX_SET16(s.vdata[1],5,i);}

inline static PfxHandle State(const PfxBroadphaseProxy& s)    {return (PfxHandle)PFX_GET32(s.vdata[0],3);}
inline static PfxHandle Body(const PfxBroadphaseProxy& s)     {return (PfxHandle)PFX_GET32(s.vdata[1],0);}
inline static uint16_t  UniqueId(const PfxBroadphaseProxy& s) {return PFX_GET16(s.vdata[1],2);}
inline static uint8_t   MovType(const PfxBroadphaseProxy& s)  {return PFX_GET8(s.vdata[1],6);}
inline static uint8_t   Callback(const PfxBroadphaseProxy& s) {return PFX_GET8(s.vdata[1],7);}
inline static uint16_t  Self(const PfxBroadphaseProxy& s)     {return PFX_GET16(s.vdata[1],4);}
inline static uint16_t  Target(const PfxBroadphaseProxy& s)   {return PFX_GET16(s.vdata[1],5);}

// create a key number from two unique ids (i != j)
inline static void setKeyFromID(SortData& s,uint16_t i,uint16_t j)
{
	uint32_t minIdx = i < j ? i : j;
	uint32_t maxIdx = i > j ? i : j;
	setKey(s,maxIdx * (maxIdx - 1) / 2 + minIdx);
	setUniqueIdA(s,i);
	setUniqueIdB(s,j);
}

// (i == j)
inline static void setKeyFromIDEq(SortData& s,uint16_t i,uint16_t j)
{
	uint32_t minIdx = i < j ? i : j;
	uint32_t maxIdx = i > j ? i : j;
	setKey(s,maxIdx * (maxIdx + 1) / 2 + minIdx);
	setUniqueIdA(s,i);
	setUniqueIdB(s,j);
}

#endif
