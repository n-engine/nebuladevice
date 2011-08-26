#ifndef __INTERSECT_FUNCTION_H__
#define __INTERSECT_FUNCTION_H__

#include <float.h>

#include <vectormath_aos.h>
using namespace Vectormath::Aos;

#define RAY_TRIANGLE_EPSILON 0.00001f

// レイとAABB交差判定
// 交差しているかどうかだけ判定します。
inline
bool rayIntersectAABBFast(
	const Vector3 &AABBhalf,
	const Vector3 &AABBpos,
	const Vector3 &rayStart,
	const Vector3 &rayDir,
	float &t)
{
	Vector3 AABBmin=AABBpos-AABBhalf;
	Vector3 AABBmax=AABBpos+AABBhalf;

	float tmin=-FLT_MAX,tmax=FLT_MAX;

	Vector3 absRayDir = absPerElem(rayDir);

	if(absRayDir[0] < 0.00001f && (rayStart[0] < AABBmin[0] || rayStart[0] > AABBmax[0]) )
		return false;
	if(absRayDir[1] < 0.00001f && (rayStart[1] < AABBmin[1] || rayStart[1] > AABBmax[1]) )
		return false;
	if(absRayDir[2] < 0.00001f && (rayStart[2] < AABBmin[2] || rayStart[2] > AABBmax[2]) )
		return false;
	
	Vector3 t1_ = divPerElem((AABBmin-rayStart),rayDir);
	Vector3 t2_ = divPerElem((AABBmax-rayStart),rayDir);

	Vector3 t1 = minPerElem(t1_,t2_);
	Vector3 t2 = maxPerElem(t1_,t2_);

	if(t1[0] > tmin) tmin = t1[0];
	if(t2[0] < tmax) tmax = t2[0];
	if(t1[1] > tmin) tmin = t1[1];
	if(t2[1] < tmax) tmax = t2[1];
	if(t1[2] > tmin) tmin = t1[2];
	if(t2[2] < tmax) tmax = t2[2];

	if(tmin > tmax) return false;

	t = tmin;

	return true;
}

// レイとAABB交差判定
// レイの開始点がAABB内部にある場合は判定しません
inline
bool rayIntersectAABB(
	const Vector3 &AABBhalf,
	const Vector3 &AABBpos,
	const Vector3 &rayStart,
	const Vector3 &rayDir,
	float &t,
	Vector3 &nml)
{
	Vector3 AABBmin=AABBpos-AABBhalf;
	Vector3 AABBmax=AABBpos+AABBhalf;
	
	float t1,t2,tt,tmin=-FLT_MAX,tmax=FLT_MAX;
	bool sign = false;

	// X
	if(fabsf(rayDir[0]) < 0.00001f && (rayStart[0] < AABBmin[0] || rayStart[0] > AABBmax[0]) )
		return false;
	
	t1 = (AABBmin[0]-rayStart[0]) / rayDir[0];
	t2 = (AABBmax[0]-rayStart[0]) / rayDir[0];
	if(t1 > t2) {tt=t2;t2=t1;t1=tt;sign=true;}

	if(t1 > tmin) {tmin = t1;nml=sign?Vector3(1.0f,0.0f,0.0f):Vector3(-1.0f,0.0f,0.0f);}
	if(t2 < tmax) tmax = t2;
	if(tmin > tmax) return false;
	
	// Y
	if(fabsf(rayDir[1]) < 0.00001f && (rayStart[1] < AABBmin[1] || rayStart[1] > AABBmax[1]) )
		return false;
	
	sign = false;
	t1 = (AABBmin[1]-rayStart[1]) / rayDir[1];
	t2 = (AABBmax[1]-rayStart[1]) / rayDir[1];
	if(t1 > t2) {tt=t2;t2=t1;t1=tt;sign=true;}
	
	if(t1 > tmin) {tmin = t1;nml=sign?Vector3(0.0f,1.0f,0.0f):Vector3(0.0f,-1.0f,0.0f);}
	if(t2 < tmax) tmax = t2;
	if(tmin > tmax) return false;
	
	// Z
	if(fabsf(rayDir[2]) < 0.00001f && (rayStart[2] < AABBmin[2] || rayStart[2] > AABBmax[2]) )
		return false;
	
	sign = false;
	t1 = (AABBmin[2]-rayStart[2]) / rayDir[2];
	t2 = (AABBmax[2]-rayStart[2]) / rayDir[2];
	if(t1 > t2) {tt=t2;t2=t1;t1=tt;sign=true;}
	
	if(t1 > tmin) {tmin = t1;nml=sign?Vector3(0.0f,0.0f,1.0f):Vector3(0.0f,0.0f,-1.0f);}
	if(t2 < tmax) tmax = t2;

	if(tmin > tmax || tmin < 0.0f || tmin > 1.0f) return false;

	t = tmin;
	
	return true;
}

// レイとトライアングルの交差判定（両面）
// ※両端点は判定から除く
inline
bool rayIntersectTriangle(
	const Vector3 *pnts,
	const Vector3 &rayStart,
	const Vector3 &rayDir,
	float &t)
{
	float v,w;
	Vector3 ab = pnts[1] - pnts[0];
	Vector3 ac = pnts[2] - pnts[0];

	Vector3 n = cross(ab,ac);

	float d = dot(-rayDir,n);
	
	if(fabsf(d) < 0.00001f) return false;

	Vector3 ap = rayStart - pnts[0];
	t = dot(ap,n) / d;

	if(t <= 0.0f || t >= 1.0f) return false;

	Vector3 e = cross(-rayDir,ap);
	v = dot(ac,e) / d;
	if(v < -RAY_TRIANGLE_EPSILON || v > 1.0f+RAY_TRIANGLE_EPSILON) return false;

	w = -dot(ab,e) / d;
	if(w < -RAY_TRIANGLE_EPSILON || v+w > 1.0f+RAY_TRIANGLE_EPSILON) return false;

	return true;
}

// レイとトライアングルの交差判定（表面貫通）
// ※両端点は判定から除く
inline
bool rayIntersectTriangleWithoutFrontFace(
	const Vector3 *pnts,
	const Vector3 &rayStart,
	const Vector3 &rayDir,
	float &t)
{
	float v,w;
	Vector3 ab = pnts[1] - pnts[0];
	Vector3 ac = pnts[2] - pnts[0];

	Vector3 n = cross(ab,ac);

	float d = dot(-rayDir,n);
	
	if(d >= 0.0f) return false;

	Vector3 ap = rayStart - pnts[0];
	t = dot(ap,n) / d;

	if(t <= 0.0f || t >= 1.0f) return false;

	Vector3 e = cross(-rayDir,ap);
	v = dot(ac,e) / d;
	if(v < -RAY_TRIANGLE_EPSILON || v > 1.0f+RAY_TRIANGLE_EPSILON) return false;

	w = -dot(ab,e) / d;
	if(w < -RAY_TRIANGLE_EPSILON || v+w > 1.0+RAY_TRIANGLE_EPSILON) return false;

	return true;
}

// レイとトライアングルの交差判定（裏面貫通）
// ※両端点は判定から除く
inline
bool rayIntersectTriangleWithoutBackFace(
	const Vector3 *pnts,
	const Vector3 &rayStart,
	const Vector3 &rayDir,
	float &t)
{
	float v,w;
	Vector3 ab = pnts[1] - pnts[0];
	Vector3 ac = pnts[2] - pnts[0];

	Vector3 n = cross(ab,ac);

	float d = dot(-rayDir,n);
	
	if(d <= 0.0f) return false;

	Vector3 ap = rayStart - pnts[0];
	t = dot(ap,n) / d;

	if(t <= 0.0f || t >= 1.0f) return false;

	Vector3 e = cross(-rayDir,ap);
	v = dot(ac,e) / d;
	if(v < -RAY_TRIANGLE_EPSILON || v > 1.0f+RAY_TRIANGLE_EPSILON) return false;

	w = -dot(ab,e) / d;
	if(w < -RAY_TRIANGLE_EPSILON || v+w > 1.0f+RAY_TRIANGLE_EPSILON) return false;

	return true;
}

// トライアングル高速交差判定（交差しているかどうかだけを判定）
inline
bool fastCheckIntersectTwoTriangles(
	const Vector3 *pA,const Vector3 &normalA,
	const Vector3 *pB,const Vector3 &normalB)
{
	Vector3 axis;
	float areaMinA,areaMaxA,areaMinB,areaMaxB;
	
	// ----------------------------------
	// 面で分離判定

	// A -> B
	{
		axis = normalA;
		areaMinA = areaMaxA = dot(axis,pA[0]);

		areaMinB = FLT_MAX;
		areaMaxB = FLT_MIN;
		float prj;
		prj = dot(axis,pB[0]);
		areaMinB = areaMinB > prj ? prj : areaMinB;
		areaMaxB = areaMaxB < prj ? prj : areaMaxB;
		prj = dot(axis,pB[1]);
		areaMinB = areaMinB > prj ? prj : areaMinB;
		areaMaxB = areaMaxB < prj ? prj : areaMaxB;
		prj = dot(axis,pB[2]);
		areaMinB = areaMinB > prj ? prj : areaMinB;
		areaMaxB = areaMaxB < prj ? prj : areaMaxB;

		if(areaMaxB <= areaMinA || areaMinB >= areaMaxA) {
			return false;
		}
	}

	// B -> A
	{
		axis = normalB;
		areaMinB = areaMaxB = dot(axis,pB[0]);

		areaMinA = FLT_MAX;
		areaMaxA = FLT_MIN;
		float prj;
		prj = dot(axis,pA[0]);	
		areaMinA = areaMinA > prj ? prj : areaMinA;
		areaMaxA = areaMaxA < prj ? prj : areaMaxA;
		prj = dot(axis,pA[1]);
		areaMinA = areaMinA > prj ? prj : areaMinA;
		areaMaxA = areaMaxA < prj ? prj : areaMaxA;
		prj = dot(axis,pA[2]);
		areaMinA = areaMinA > prj ? prj : areaMinA;
		areaMaxA = areaMaxA < prj ? prj : areaMaxA;

		if(areaMaxB <= areaMinA || areaMinB >= areaMaxA) {
			return false;
		}
	}

	// ----------------------------------
	// エッジで分離判定

	for(int ia=0;ia<3;ia++) {
		for(int ib=0;ib<3;ib++) {
			Vector3 eA = normalize(pA[(ia+1)%3]-pA[ia]);
			Vector3 eB = normalize(pB[(ib+1)%3]-pB[ib]);
			
			if(1.0f - fabsf(dot(eA,eB)) < 0.00001f) continue;

			axis = normalize(cross(eA,eB));

			float prj;

			areaMinA = FLT_MAX;
			areaMaxA = FLT_MIN;

			prj = dot(axis,pA[0]);
			areaMinA = areaMinA > prj ? prj : areaMinA;
			areaMaxA = areaMaxA < prj ? prj : areaMaxA;
			prj = dot(axis,pA[1]);
			areaMinA = areaMinA > prj ? prj : areaMinA;
			areaMaxA = areaMaxA < prj ? prj : areaMaxA;
			prj = dot(axis,pA[2]);
			areaMinA = areaMinA > prj ? prj : areaMinA;
			areaMaxA = areaMaxA < prj ? prj : areaMaxA;

			areaMinB = FLT_MAX;
			areaMaxB = FLT_MIN;

			prj = dot(axis,pB[0]);
			areaMinB = areaMinB > prj ? prj : areaMinB;
			areaMaxB = areaMaxB < prj ? prj : areaMaxB;
			prj = dot(axis,pB[1]);
			areaMinB = areaMinB > prj ? prj : areaMinB;
			areaMaxB = areaMaxB < prj ? prj : areaMaxB;
			prj = dot(axis,pB[2]);
			areaMinB = areaMinB > prj ? prj : areaMinB;
			areaMaxB = areaMaxB < prj ? prj : areaMaxB;

			if(areaMaxB <= areaMinA || areaMinB >= areaMaxA) {
				return false;
			}
		}
	}

	return true;
}

// 2つの線分の最近接点を計算
// ※常に線分の長さ＞０とする
inline
void distanceTwoLines(
	const Vector3 &p1,const Vector3 &q1,
	const Vector3 &p2,const Vector3 &q2,
	Vector3 &s1,Vector3 &s2)
{
	Vector3 v1 = q1-p1;
	Vector3 v2 = q2-p2;
	Vector3 r = p1 - p2;

	float a = dot(v1,v1);
	float e = dot(v2,v2);
	float f = dot(v2,r);
	float b = dot(v1,v2);
	float c = dot(v1,r);
	float den = a*e-b*b;
	
	float s,t;
	
	if(den != 0.0f) {
		s = PFX_CLAMP((b*f-c*e)/den,0.0f,1.0f);
	}
	else {
		s = 0.0f;
	}
	
	t = (b*s+f)/e;
	
	if(t < 0.0f) {
		t = 0.0f;
		s = PFX_CLAMP(-c/a,0.0f,1.0f);
	}
	else if(t > 1.0f) {
		t = 1.0f;
		s = PFX_CLAMP((b-c)/a,0.0f,1.0f);
	}
	
	s1 = p1 + s * v1;
	s2 = p2 + t * v2;
}

inline
void distancePointAndTriangle(
	const Vector3 &a,const Vector3 &b,const Vector3 &c,const Vector3 &p,
	Vector3 &s)
{
    Vector3 ab = b - a;
    Vector3 ac = c - a;
    Vector3 ap = p - a;
    float d1 = dot(ab, ap);
    float d2 = dot(ac, ap);
	if(d1 <= 0.0f && d2 <= 0.0f) {
		s = a;
		return;
	}

    Vector3 bp = p - b;
    float d3 = dot(ab, bp);
    float d4 = dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3) {
		s = b;
		return;
	}

    float vc = d1*d4 - d3*d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
        float v = d1 / (d1 - d3);
        s = a + v * ab;
		return;
    }

    Vector3 cp = p - c;
    float d5 = dot(ab, cp);
    float d6 = dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6) {
		s = c;
		return;
	}

    float vb = d5*d2 - d1*d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
        float w = d2 / (d2 - d6);
        s = a + w * ac;
		return;
    }

    float va = d3*d6 - d5*d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
        float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        s = b + w * (c - b);
		return;
    }

    float den = 1.0f / (va + vb + vc);
    float v = vb * den;
    float w = vc * den;
    s = a + ab * v + ac * w;
}

inline
void closestPointAndAABB(const Vector3 &p,const Vector3 &aabb,Vector3 &s)
{
	s = p;
	s = maxPerElem(s,-aabb);
	s = minPerElem(s,aabb);
}

// 面のローカル座標を取得
// 面の座標をP0,P1,P2、面上の点をQとするとき
// v0 = P1 - P0 , v1 = P2 - P0 , dir = Q - P0
inline
void get_ST( float &s, float &t,
			const Vector3 &v0, const Vector3 &v1, const Vector3 &dir ) {
	Vector3 v = cross( v0, v1 );
	Vector3 crS = cross( v, v0 );
	Vector3 crT = cross( v, v1 );
	s = dot( crT, dir ) / dot( crT, v0 );
	t = dot( crS, dir ) / dot( crS, v1 );
}

#endif /* __INTERSECT_FUNCTION_H__ */
