//------------------------------------------------------------------------------
//  terrain.fx
//  (C) 2011 xiongyouyi
//------------------------------------------------------------------------------
#include "lib/common.fxh"
#include "lib/config.fxh"
#include "lib/util.fxh"
#include "lib/shared.fxh"

const float blendUvOffset = 31.0 / 32.0;
float4 shadowColor = float4(0.1, 0.1, 0.1, 1.0);

texture DiffMap0 : DiffMap0;
sampler DiffSampler0 = sampler_state
{
	Texture = <DiffMap0>;
	AddressU = WRAP;
	AddressV = WRAP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture DiffMap1 : DiffMap1;
sampler DiffSampler1 = sampler_state
{
	Texture = <DiffMap1>;
	AddressU = WRAP;
	AddressV = WRAP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture DiffMap2 : DiffMap2;
sampler DiffSampler2 = sampler_state
{
	Texture = <DiffMap2>;
	AddressU = WRAP;
	AddressV = WRAP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture DiffMap3 : DiffMap3;
sampler DiffSampler3 = sampler_state
{
	Texture = <DiffMap3>;
	AddressU = WRAP;
	AddressV = WRAP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

texture BlendMap : BlendMap;
sampler BlendSampler = sampler_state
{
	Texture = <BlendMap>;
	AddressU = CLAMP;
	AddressV = CLAMP;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = None;
};

void
terrain_vs(float4 position : POSITION,
		   float3 normal   : NORMAL,
		   float2 uv       : TEXCOORD0,
		   out float4 oPos : POSITION,
		   out float2 oUv  : TEXCOORD0,
		   out float2 oUvBlend  : TEXCOORD1,
		   out float4 oDiffuse  : COLOR0,
		   out float4 oSpecular : COLOR1)
{
	oPos = mul(position, mvp);
	oUv = uv;
	oUvBlend = uv / 8.0 * blendUvOffset;
	
	//float3 worldPos = mul(position, model);
	//float3 N = normalize(mul(normal, model));
	//float3 L = normalize(lightPos - worldPos);
	
	//float3 V = normalize(eyePos - worldPos);
	//float3 R = reflect(L, N);
	
	//oDiffuse = mtlLightDiffuse * saturate(dot(N, L));
	//oDiffuse.a = 1.0;
	
	//oSpecular = mtlLightSpecular * pow(saturate(dot(V, R)), lightShininess);
	//oSpecular.a = 1.0;
	
	oDiffuse = float4(1.0, 1.0, 1.0, 1.0);
	oSpecular = float4(1.0, 1.0, 1.0, 1.0);
}

void
terrain_ps(float2 uv		: TEXCOORD0,
		   float2 uvBlend   : TEXCOORD1,
		   float4 diffuse   : COLOR0,
           float4 specular  : COLOR1,
           out float4 oColor : COLOR,
           uniform int numLayers)
{
	float4 col, layer, blend;
	
	// tetch textures
	col = tex2D(DiffSampler0, uv);
	blend = tex2D(BlendSampler, uvBlend);
	
	// layer 1
	if (numLayers > 1)
	{
		layer = tex2D(DiffSampler1, uv);
		col = lerp(col, layer, blend.r);
	}
	
	// layer 2
	if (numLayers > 2)
	{
		layer = tex2D(DiffSampler2, uv);
		col = lerp(col, layer, blend.g);
	}
	
	// layer 3
	if (numLayers > 3)
	{
		layer = tex2D(DiffSampler3, uv);
		col = lerp(col, layer, blend.b);
	}
	
	// specular
	//col = diffuse * col + specular * col.a;
	
	// shadow
	oColor = lerp(col, shadowColor, blend.a);

	oColor.a = shadowColor.a;
}

//---------------------------------------------------------------------------------------------------------------------
/**
    Techniques for terrain.
*/

#define TerrainTechnique(name, features, vertexShader, pixelShader, numLayers) \
technique name < string Mask = features; > \
{ \
    pass p0 \
    { \
        VertexShader    = compile vs_3_0 vertexShader(); \
        PixelShader     = compile ps_3_0 pixelShader(numLayers); \
        CullMode        = 0; \
    } \
}

TerrainTechnique(Terrain1, "Terrain1", terrain_vs, terrain_ps, 1);
TerrainTechnique(Terrain2, "Terrain2", terrain_vs, terrain_ps, 2);
TerrainTechnique(Terrain3, "Terrain3", terrain_vs, terrain_ps, 3);
TerrainTechnique(Terrain4, "Terrain4", terrain_vs, terrain_ps, 4);



