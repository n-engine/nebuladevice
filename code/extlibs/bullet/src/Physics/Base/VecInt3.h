/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __VECINT3_H__
#define __VECINT3_H__

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#ifndef __SPU__

class VecInt3
{
private:
	int32_t mX,mY,mZ,mW;

public:
	VecInt3() {mX=mY=mZ=mW=0;}
	VecInt3(const Vector3 vec) {mX=(int32_t)vec[0];mY=(int32_t)vec[1];mZ=(int32_t)vec[2];mW=0;}
	VecInt3(float fx,float fy,float fz) {mX=(int32_t)fx;mY=(int32_t)fy;mZ=(int32_t)fz;mW=0;}
	VecInt3(int32_t iv) {mX=mY=mZ=iv;mW=0;}
	VecInt3(int32_t ix,int32_t iy,int32_t iz) {mX=ix;mY=iy;mZ=iz;mW=0;}

    inline VecInt3 &operator =( const VecInt3 &vec);

	inline int32_t get(int32_t i) const {return *(&mX+i);}
	inline int32_t getX() const {return mX;}
	inline int32_t getY() const {return mY;}
	inline int32_t getZ() const {return mZ;}
	inline void set(int32_t i,int32_t v) {*(&mX+i) = v;}
	inline void setX(int32_t v) {mX = v;}
	inline void setY(int32_t v) {mY = v;}
	inline void setZ(int32_t v) {mZ = v;}

    inline const VecInt3 operator +( const VecInt3 & vec ) const;
    inline const VecInt3 operator -( const VecInt3 & vec ) const;
    inline const VecInt3 operator *( int32_t scalar ) const;
    inline const VecInt3 operator /( int32_t scalar ) const;

    inline VecInt3 & operator +=( const VecInt3 & vec );
    inline VecInt3 & operator -=( const VecInt3 & vec );
    inline VecInt3 & operator *=( int32_t scalar );
    inline VecInt3 & operator /=( int32_t scalar );

    inline const VecInt3 operator -() const;

	operator Vector3() const
	{
		return Vector3((float)mX,(float)mY,(float)mZ);
	}
} __attribute__ ((aligned(16)));

inline VecInt3 &VecInt3::operator =( const VecInt3 &vec)
{
    mX = vec.mX;
    mY = vec.mY;
    mZ = vec.mZ;
    return *this;
}

inline const VecInt3 VecInt3::operator +( const VecInt3 & vec ) const
{
    return VecInt3(mX+vec.mX, mY+vec.mY, mZ+vec.mZ);
}

inline const VecInt3 VecInt3::operator -( const VecInt3 & vec ) const
{
    return VecInt3(mX-vec.mX, mY-vec.mY, mZ-vec.mZ);
}

inline const VecInt3 VecInt3::operator *( int32_t scalar ) const
{
    return VecInt3(mX*scalar, mY*scalar, mZ*scalar);
}

inline const VecInt3 VecInt3::operator /( int32_t scalar ) const
{
    return VecInt3(mX/scalar, mY/scalar, mZ/scalar);
}

inline VecInt3 &VecInt3::operator +=( const VecInt3 & vec )
{
    *this = *this + vec;
    return *this;
}

inline VecInt3 &VecInt3::operator -=( const VecInt3 & vec )
{
    *this = *this - vec;
    return *this;
}

inline VecInt3 &VecInt3::operator *=( int32_t scalar )
{
    *this = *this * scalar;
    return *this;
}

inline VecInt3 &VecInt3::operator /=( int32_t scalar )
{
    *this = *this / scalar;
    return *this;
}

inline const VecInt3 VecInt3::operator -() const
{
	return VecInt3(-mX,-mY,-mZ);
}

inline const VecInt3 operator *( int32_t scalar, const VecInt3 & vec )
{
    return vec * scalar;
}

inline const VecInt3 mulPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
	return VecInt3(vec0.getX()*vec1.getX(), vec0.getY()*vec1.getY(), vec0.getZ()*vec1.getZ());
}

inline const VecInt3 divPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
	return VecInt3(vec0.getX()/vec1.getX(), vec0.getY()/vec1.getY(), vec0.getZ()/vec1.getZ());
}

inline const VecInt3 absPerElem( const VecInt3 & vec )
{
	return VecInt3(abs(vec.getX()), abs(vec.getY()), abs(vec.getZ()));
}

inline const VecInt3 maxPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
    return VecInt3(
        (vec0.getX() > vec1.getX())? vec0.getX() : vec1.getX(),
        (vec0.getY() > vec1.getY())? vec0.getY() : vec1.getY(),
        (vec0.getZ() > vec1.getZ())? vec0.getZ() : vec1.getZ()
    );
}

inline const VecInt3 minPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
    return VecInt3(
        (vec0.getX() < vec1.getX())? vec0.getX() : vec1.getX(),
        (vec0.getY() < vec1.getY())? vec0.getY() : vec1.getY(),
        (vec0.getZ() < vec1.getZ())? vec0.getZ() : vec1.getZ()
    );
}

#else // __SPU__

#include <math.h>
#include <spu_intrinsics.h>

class VecInt3
{
private:
	vec_int4 mVec128;

public:
	VecInt3() {mVec128=spu_splats(0);}
	VecInt3(const Vector3 vec) {mVec128=spu_convts(vec.get128(),0);}
	VecInt3(float fx,float fy,float fz) {mVec128=(vec_int4){(int32_t)fx,(int32_t)fy,(int32_t)fz,0};}
	VecInt3(int32_t iv) {mVec128=spu_splats(iv);}
	VecInt3(int32_t ix,int32_t iy,int32_t iz) {mVec128=(vec_int4){ix,iy,iz,0};}
	VecInt3(vec_int4 vec) {mVec128=vec;}

    inline VecInt3 &operator =( const VecInt3 &vec);

	inline int32_t get(int32_t i) const {return spu_extract(mVec128,i);}
	inline int32_t getX() const {return spu_extract(mVec128,0);}
	inline int32_t getY() const {return spu_extract(mVec128,1);}
	inline int32_t getZ() const {return spu_extract(mVec128,2);}
	inline void set(int32_t i,int32_t v) {spu_insert(v,mVec128,i);}
	inline void setX(int32_t v) {spu_insert(v,mVec128,0);}
	inline void setY(int32_t v) {spu_insert(v,mVec128,1);}
	inline void setZ(int32_t v) {spu_insert(v,mVec128,2);}

    inline const VecInt3 operator +( const VecInt3 & vec ) const;
    inline const VecInt3 operator -( const VecInt3 & vec ) const;
    inline const VecInt3 operator *( int32_t scalar ) const;
    inline const VecInt3 operator /( int32_t scalar ) const;

    inline VecInt3 & operator +=( const VecInt3 & vec );
    inline VecInt3 & operator -=( const VecInt3 & vec );
    inline VecInt3 & operator *=( int32_t scalar );
    inline VecInt3 & operator /=( int32_t scalar );

    inline const VecInt3 operator -() const;

	operator Vector3() const
	{
		return Vector3(spu_convtf(mVec128,0));
	}

	inline vec_int4 get128( ) const
	{
		return mVec128;
	}
} __attribute__ ((aligned(16)));

inline VecInt3 &VecInt3::operator =( const VecInt3 &vec)
{
	mVec128 = vec.mVec128;
    return *this;
}

inline const VecInt3 VecInt3::operator +( const VecInt3 & vec ) const
{
    return VecInt3(spu_add(mVec128,vec.mVec128));
}

inline const VecInt3 VecInt3::operator -( const VecInt3 & vec ) const
{
    return VecInt3(spu_sub(mVec128,vec.mVec128));
}

inline const VecInt3 VecInt3::operator *( int32_t scalar ) const
{
   vec_short8 lhs_short = (vec_short8)mVec128;
   vec_short8 rhs_short = (vec_short8)spu_splats(scalar);
   
   return VecInt3((vec_int4)spu_add( spu_add( spu_mulh( lhs_short, rhs_short ),
                                             spu_mulh( rhs_short, lhs_short ) ),
                                    (vec_int4)spu_mulo( (vec_ushort8)lhs_short, (vec_ushort8)rhs_short ) ) );
}

inline const VecInt3 VecInt3::operator /( int32_t scalar ) const
{
	return VecInt3(divi4(mVec128,spu_splats(scalar)).quot);
}

inline VecInt3 &VecInt3::operator +=( const VecInt3 & vec )
{
    *this = *this + vec;
    return *this;
}

inline VecInt3 &VecInt3::operator -=( const VecInt3 & vec )
{
    *this = *this - vec;
    return *this;
}

inline VecInt3 &VecInt3::operator *=( int32_t scalar )
{
    *this = *this * scalar;
    return *this;
}

inline VecInt3 &VecInt3::operator /=( int32_t scalar )
{
    *this = *this / scalar;
    return *this;
}

inline const VecInt3 VecInt3::operator -() const
{
    return VecInt3(spu_sub((int)0,mVec128));
}

inline const VecInt3 operator *( int32_t scalar, const VecInt3 & vec )
{
    return vec * scalar;
}

inline const VecInt3 mulPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
   vec_short8 lhs_short = (vec_short8)vec0.get128();
   vec_short8 rhs_short = (vec_short8)vec1.get128();
   
   return VecInt3((vec_int4)spu_add( spu_add( spu_mulh( lhs_short, rhs_short ),
                                             spu_mulh( rhs_short, lhs_short ) ),
                                    (vec_int4)spu_mulo( (vec_ushort8)lhs_short, (vec_ushort8)rhs_short ) ) );
}

inline const VecInt3 divPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
	return VecInt3(divi4(vec0.get128(),vec1.get128()).quot);
}

inline const VecInt3 absPerElem( const VecInt3 & vec )
{
	return VecInt3(absi4(vec.get128()));
}

inline const VecInt3 maxPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
	return VecInt3(spu_sel(vec1.get128(),vec0.get128(),spu_cmpgt(vec0.get128(),vec1.get128())));
}

inline const VecInt3 minPerElem( const VecInt3 & vec0, const VecInt3 & vec1 )
{
	return VecInt3(spu_sel(vec0.get128(),vec1.get128(),spu_cmpgt(vec0.get128(),vec1.get128())));
}

#endif // __SPU__

#endif /* __VECINT3_H__ */
