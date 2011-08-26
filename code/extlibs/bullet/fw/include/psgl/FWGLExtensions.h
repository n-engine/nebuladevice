/* SCE CONFIDENTIAL
* $PSLibId$
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/
//-----------------------------------------------------------------------------
//                             Sample Framework
//
// OpenGL Extensions - This is a limited set of functions that are supported
// by PSGL, but are not present in standard OGL 1.1
//
// $File: //nextgendev/Framework_080/include/FWGLExtensions.h $
// $Author: asidwell $
// $Date: 2006/01/30 $
// $Revision: #2 $
//
// Copyright (C) 2006 Sony Computer Entertainment.
// All Rights Reserved.
//
//-----------------------------------------------------------------------------

#ifndef __FW_GLEXTENSIONS_H__
#define __FW_GLEXTENSIONS_H__

#ifndef _WIN32
#ifndef APIENTRY
#define APIENTRY
#endif//APIENTRY
#endif//_WIN32

#ifndef GL_VERSION_1_5
#include <stddef.h>
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif//GL_VERSION_1_5

class FWGLExtension
{
#ifndef GL_VERSION_1_2

public:

typedef void (APIENTRY *PFNGLCOPYTEXSUBIMAGE3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
static PFNGLCOPYTEXSUBIMAGE3D spCopyTexSubImage3D;
#define glCopyTexSubImage3D FWGLExtension::spCopyTexSubImage3D

typedef void (APIENTRY *PFNGLDRAWRANGEELEMENTS)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
static PFNGLDRAWRANGEELEMENTS spDrawRangeElements;
#define glDrawRangeElements FWGLExtension::spDrawRangeElements

typedef void (APIENTRY *PFNGLTEXIMAGE3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
static PFNGLTEXIMAGE3D spTexImage3D;
#define glTexImage3D FWGLExtension::spTexImage3D

typedef void (APIENTRY *PFNGLTEXSUBIMAGE3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
static PFNGLTEXSUBIMAGE3D spTexSubImage3D;
#define glTexSubImage3D FWGLExtension::spTexSubImage3D

private:

	static void APIENTRY initCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	static void APIENTRY initDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
	static void APIENTRY initTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	static void APIENTRY initTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);

#define GL_TEXTURE_3D                     0x806F
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_BGRA                           0x80E1
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#endif//GL_VERSION_1_2

#ifndef GL_VERSION_1_3

public:

typedef void (APIENTRY *PFNGLACTIVETEXTURE)(GLenum texture);
static PFNGLACTIVETEXTURE spActiveTexture;
#define glActiveTexture FWGLExtension::spActiveTexture

typedef void (APIENTRY *PFNGLCLIENTACTIVETEXTURE)(GLenum texture);
static PFNGLCLIENTACTIVETEXTURE spClientActiveTexture;
#define glClientActiveTexture FWGLExtension::spClientActiveTexture

typedef void (APIENTRY *PFNGLCOMPRESSEDTEXIMAGE2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
static PFNGLCOMPRESSEDTEXIMAGE2D spCompressedTexImage2D;
#define glCompressedTexImage2D FWGLExtension::spCompressedTexImage2D

typedef void (APIENTRY *PFNGLCOMPRESSEDTEXIMAGE3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
static PFNGLCOMPRESSEDTEXIMAGE3D spCompressedTexImage3D;
#define glCompressedTexImage3D FWGLExtension::spCompressedTexImage3D

typedef void (APIENTRY *PFNGLCOMPRESSEDTEXSUBIMAGE2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
static PFNGLCOMPRESSEDTEXSUBIMAGE2D spCompressedTexSubImage2D;
#define glCompressedTexSubImage2D FWGLExtension::spCompressedTexSubImage2D

typedef void (APIENTRY *PFNGLCOMPRESSEDTEXSUBIMAGE3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
static PFNGLCOMPRESSEDTEXSUBIMAGE3D spCompressedTexSubImage3D;
#define glCompressedTexSubImage3D FWGLExtension::spCompressedTexSubImage3D

typedef void (APIENTRY *PFNGLMULTITEXCOORD4F)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
static PFNGLMULTITEXCOORD4F spMultiTexCoord4f;
#define glMultiTexCoord4f FWGLExtension::spMultiTexCoord4f

typedef void (APIENTRY *PFNGLSAMPLECOVERAGE)(GLclampf value, GLboolean invert);
static PFNGLSAMPLECOVERAGE spSampleCoverage;
#define glSampleCoverage FWGLExtension::spSampleCoverage

private:

	static void APIENTRY initActiveTexture(GLenum texture);
	static void APIENTRY initClientActiveTexture(GLenum texture);
	static void APIENTRY initCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
	static void APIENTRY initCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
	static void APIENTRY initCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
	static void APIENTRY initCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
	static void APIENTRY initMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	static void APIENTRY initSampleCoverage(GLclampf value, GLboolean invert);

#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#endif//GL_VERSION_1_3

#ifndef GL_VERSION_1_5

public:

typedef void (APIENTRY *PFNGLBINDBUFFER)(GLenum target, GLuint buffer);
static PFNGLBINDBUFFER spBindBuffer;
#define glBindBuffer FWGLExtension::spBindBuffer

typedef void (APIENTRY *PFNGLBUFFERDATA)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
static PFNGLBUFFERDATA spBufferData;
#define glBufferData FWGLExtension::spBufferData

typedef void (APIENTRY *PFNGLBUFFERSUBDATA)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
static PFNGLBUFFERSUBDATA spBufferSubData;
#define glBufferSubData FWGLExtension::spBufferSubData

typedef void (APIENTRY *PFNGLDELETEBUFFERS)(GLsizei n, const GLuint *buffers);
static PFNGLDELETEBUFFERS spDeleteBuffers;
#define glDeleteBuffers FWGLExtension::spDeleteBuffers

typedef void (APIENTRY *PFNGLGENBUFFERS)(GLsizei n, GLuint *buffers);
static PFNGLGENBUFFERS spGenBuffers;
#define glGenBuffers FWGLExtension::spGenBuffers

typedef GLvoid* (APIENTRY *PFNGLMAPBUFFER)(GLenum target, GLenum access);
static PFNGLMAPBUFFER spMapBuffer;
#define glMapBuffer FWGLExtension::spMapBuffer

typedef GLboolean (APIENTRY *PFNGLUNMAPBUFFER)(GLenum target);
static PFNGLUNMAPBUFFER spUnmapBuffer;
#define glUnmapBuffer FWGLExtension::spUnmapBuffer

private:

	static void APIENTRY initBindBuffer(GLenum target, GLuint buffer);
	static void APIENTRY initBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
	static void APIENTRY initBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
	static void APIENTRY initDeleteBuffers(GLsizei n, const GLuint *buffers);
	static void APIENTRY initGenBuffers(GLsizei n, GLuint *buffers);
	static GLvoid* APIENTRY initMapBuffer(GLenum target, GLenum access);
	static GLboolean APIENTRY initUnmapBuffer(GLenum target);

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_STREAM_DRAW                    0x88E0
#endif//GL_VERSION_1_5

#ifndef GL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#endif//GL_EXT_texture_compression_s3tc

#ifndef GL_ARB_shadow
#define GL_TEXTURE_COMPARE_MODE_ARB       0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB       0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB       0x884E
#endif//GL_ARB_shadow

#ifndef GL_ARB_fragment_program
#define GL_MAX_TEXTURE_COORDS_ARB         0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB    0x8872
#endif//GL_ARB_fragment_program

#ifndef GL_NV_primitive_restart

public:

typedef void (APIENTRY *PFNGLPRIMITIVERESTARTINDEXNV)(GLuint index);
static PFNGLPRIMITIVERESTARTINDEXNV spPrimitiveRestartIndexNV;
#define glPrimitiveRestartIndexNV FWGLExtension::spPrimitiveRestartIndexNV

private:
	static void APIENTRY initPrimitiveRestartIndexNV(GLuint index);

#define GL_PRIMITIVE_RESTART_NV           0x8558

#endif//GL_NV_primitive_restart

private:
	static void	reportError(char *extensionName);

};

#endif//__FW_GLEXTENSIONS_H__

// Local variables:
// indent-tabs-mode: t
// tab-width: 4
// End:
// vim:ts=4:sw=4
