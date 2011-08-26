/* [SCE CONFIDENTIAL DOCUMENT]
 * $PSLibId$
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SUBDATA_H__
#define __SUBDATA_H__

struct SubData {
	enum {
		SubDataNone = 0,
		SubDataFacetLocal,
	};
	
	uint8_t  type;
	
	// 面ローカル座標
	struct {
		uint8_t  islandIdx;	// アイランドインデックス
		uint8_t  facetIdx; 	// 面インデックス
		uint16_t s;        	// 面ローカル座標系の衝突点を表すs,t(s>=0,t>=0,s+t<=1)
		uint16_t t;        	// 座標 = s * (p1-p0) + t * (p2-p0)
	} facetLocal;
	
	SubData()
	{
		type = 0;
		facetLocal.islandIdx = 0;
		facetLocal.facetIdx = 0;
		facetLocal.s = 0;
		facetLocal.t = 0;
	}

	void  setIslandIndex(uint8_t i) {facetLocal.islandIdx = i;}
	void  setFacetIndex(uint8_t i) {facetLocal.facetIdx = i;}
	void  setFacetLocalS(float s) {facetLocal.s = (uint16_t)(s * 65535.0f);}
	void  setFacetLocalT(float t) {facetLocal.t = (uint16_t)(t * 65535.0f);}

	uint8_t getIslandIndex() {return facetLocal.islandIdx;}
	uint8_t getFacetIndex() {return facetLocal.facetIdx;}
	float getFacetLocalS() {return facetLocal.s / 65535.0f;}
	float getFacetLocalT() {return facetLocal.t / 65535.0f;}
};

#endif
