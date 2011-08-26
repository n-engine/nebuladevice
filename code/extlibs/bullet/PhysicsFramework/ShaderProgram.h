/* [SCE CONFIDENTIAL DOCUMENT]
 * PLAYSTATION(R)3 Programmer Tool Runtime Library 280.001
 *                Copyright (C) 2006 Sony Computer Entertainment Inc.
 *                                                All Rights Reserved.
 */

#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include "GLInclude.h"

///////////////////////////////////////////////////////////////////////////////
// シェーダータイプ

enum ShaderType {
	ShaderTypeMesh,
	ShaderTypeInstanceMesh,
	ShaderTypeSkinMesh,
};

///////////////////////////////////////////////////////////////////////////////
// シェーダープログラムベース

class ShaderProgramBase {
public:
	ShaderType type;
	CGprogram vertexProgram;
	CGprogram fragmentProgram;
	
	ShaderProgramBase(ShaderType t) : type(t) {}
	virtual ~ShaderProgramBase() {}
	
	ShaderType getType() const {return type;}
	
	virtual void setParameter() = 0;
	virtual void init(CGcontext context,const char *vertexFilename,const char *fragmenFilename);
	virtual void clear();
	virtual void bind();
	virtual void unbind();
};

///////////////////////////////////////////////////////////////////////////////
// メッシュシェーダープログラム

class ShaderProgramMesh : public ShaderProgramBase {
public:
	CGparameter cgParamWvp;
	CGparameter cgParamWorldLightPosition;
	CGparameter cgParamWorldEyePosition;
	CGparameter cgParamVtx;
	CGparameter cgParamNml;
	CGparameter cgParamTex;
	CGparameter cgParamCol;
	CGparameter cgParamlw;
	CGparameter cgParamitlw;
	
	ShaderProgramMesh() : ShaderProgramBase(ShaderTypeMesh) {}
	~ShaderProgramMesh() {}
	
	void setParameter();
};

///////////////////////////////////////////////////////////////////////////////
// インスタンスメッシュシェーダープログラム

class ShaderProgramInstanceMesh : public ShaderProgramBase {
public:
	CGparameter cgParamWvp;
	CGparameter cgParamWorldLightPosition;
	CGparameter cgParamWorldEyePosition;
	CGparameter cgParamVtx;
	CGparameter cgParamNml;
	CGparameter cgParamTex;
	CGparameter cgParamCol;
	CGparameter cgParamProperty;
	CGparameter cgParamlwRow0;
	CGparameter cgParamlwRow1;
	CGparameter cgParamlwRow2;
	CGparameter cgParamitlwRow0;
	CGparameter cgParamitlwRow1;
	CGparameter cgParamitlwRow2;
	
	ShaderProgramInstanceMesh() : ShaderProgramBase(ShaderTypeInstanceMesh) {}
	~ShaderProgramInstanceMesh() {}
	
	void setParameter();
};

///////////////////////////////////////////////////////////////////////////////
// スキニングメッシュシェーダープログラム

class ShaderProgramSkinMesh : public ShaderProgramBase {
public:
	CGparameter cgParamWvp;
	CGparameter cgParamWorldLightPosition;
	CGparameter cgParamWorldEyePosition;
	CGparameter cgParamVtx;
	CGparameter cgParamNml;
	CGparameter cgParamTex;
	CGparameter cgParamCol;
	CGparameter cgParamlw;
	CGparameter cgParamitlw;
	CGparameter cgParamBoneIndex;
	CGparameter cgParamBoneWeight;
	CGparameter cgParamBoneMatrices;
	
	ShaderProgramSkinMesh() : ShaderProgramBase(ShaderTypeSkinMesh) {}
	~ShaderProgramSkinMesh() {}
	
	void setParameter();
};

#endif // __SHADERPROGRAM_H__

