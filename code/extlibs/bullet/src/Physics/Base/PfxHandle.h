#ifndef __PFX_HANDLE_H__
#define __PFX_HANDLE_H__

#include "Physics/Base/PhysicsCommon.h"

typedef void* PfxHandle;

#ifdef WIN32
	typedef uint32_t PfxHandle16[4];

	inline static void      setHdl(PfxHandle16 &h,PfxHandle p) {h[0]=(uint32_t)p;}
	inline static PfxHandle getHdl(PfxHandle16 &h) {return (PfxHandle)h[0];}
#else
	typedef vec_uint4 PfxHandle16;
	#ifdef __PPU__
		#include <spu2vmx.h>
	#endif

	inline static void      setHdl(PfxHandle16 &h,PfxHandle p) {h=(vec_uint4)spu_insert((uint32_t)p,(vec_uint4)h,0);}
	inline static PfxHandle getHdl(PfxHandle16 &h) {return (PfxHandle)spu_extract(h,0);}
#endif

#endif /* __PFX_HANDLE_H__ */
