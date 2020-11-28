#pragma once
#include "ShaderPair.h"

//cbuffer CBuf
//{
//	matrix modelView;
//	matrix modelViewProj;
//};
//
//struct VSOut
//{
//	float3 viewPos : Position;
//	float3 viewNormal : Normal;
//	float4 pos : SV_Position;
//};
//
//VSOut main(float3 pos : Position, float3 n : Normal)
//{
//	VSOut vso;
//	vso.viewPos = (float3)mul(float4(pos, 1.0f), modelView);
//	vso.viewNormal = mul(n, (float3x3)modelView);
//	vso.pos = mul(float4(pos, 1.0f), modelViewProj);
//	return vso;
//}
const uint32_t Phong_VS[] = {
	0x07230203,0x00010000,0x0008000a,0x0000005b,0x00000000,0x00020011,0x00000001,0x0006000b,
	0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
	0x000a000f,0x00000000,0x00000004,0x6e69616d,0x00000000,0x00000045,0x00000048,0x00000051,
	0x00000054,0x00000058,0x00030003,0x00000005,0x000001f4,0x00040005,0x00000004,0x6e69616d,
	0x00000000,0x00040005,0x0000000a,0x754f5356,0x00000074,0x00050006,0x0000000a,0x00000000,
	0x77656976,0x00736f50,0x00060006,0x0000000a,0x00000001,0x77656976,0x6d726f4e,0x00006c61,
	0x00040006,0x0000000a,0x00000002,0x00736f70,0x00060005,0x0000000e,0x69616d40,0x6676286e,
	0x66763b33,0x00003b33,0x00030005,0x0000000c,0x00736f70,0x00030005,0x0000000d,0x0000006e,
	0x00030005,0x00000011,0x006f7376,0x00040005,0x00000015,0x66754243,0x00000000,0x00060006,
	0x00000015,0x00000000,0x65646f6d,0x6569566c,0x00000077,0x00070006,0x00000015,0x00000001,
	0x65646f6d,0x6569566c,0x6f725077,0x0000006a,0x00030005,0x00000017,0x00000000,0x00030005,
	0x00000043,0x00736f70,0x00030005,0x00000045,0x00736f70,0x00030005,0x00000047,0x0000006e,
	0x00030005,0x00000048,0x0000006e,0x00050005,0x0000004a,0x74616c66,0x546e6574,0x00706d65,
	0x00040005,0x0000004b,0x61726170,0x0000006d,0x00040005,0x0000004d,0x61726170,0x0000006d,
	0x00090005,0x00000051,0x746e6540,0x6f507972,0x4f746e69,0x75707475,0x69762e74,0x6f507765,
	0x00000073,0x000a0005,0x00000054,0x746e6540,0x6f507972,0x4f746e69,0x75707475,0x69762e74,
	0x6f4e7765,0x6c616d72,0x00000000,0x00080005,0x00000058,0x746e6540,0x6f507972,0x4f746e69,
	0x75707475,0x6f702e74,0x00000073,0x00040048,0x00000015,0x00000000,0x00000004,0x00050048,
	0x00000015,0x00000000,0x00000023,0x00000000,0x00050048,0x00000015,0x00000000,0x00000007,
	0x00000010,0x00040048,0x00000015,0x00000001,0x00000004,0x00050048,0x00000015,0x00000001,
	0x00000023,0x00000040,0x00050048,0x00000015,0x00000001,0x00000007,0x00000010,0x00030047,
	0x00000015,0x00000002,0x00040047,0x00000017,0x00000022,0x00000000,0x00040047,0x00000017,
	0x00000021,0x00000000,0x00040047,0x00000045,0x0000001e,0x00000000,0x00040047,0x00000048,
	0x0000001e,0x00000001,0x00040047,0x00000051,0x0000001e,0x00000000,0x00040047,0x00000054,
	0x0000001e,0x00000001,0x00040047,0x00000058,0x0000000b,0x00000000,0x00020013,0x00000002,
	0x00030021,0x00000003,0x00000002,0x00030016,0x00000006,0x00000020,0x00040017,0x00000007,
	0x00000006,0x00000003,0x00040020,0x00000008,0x00000007,0x00000007,0x00040017,0x00000009,
	0x00000006,0x00000004,0x0005001e,0x0000000a,0x00000007,0x00000007,0x00000009,0x00050021,
	0x0000000b,0x0000000a,0x00000008,0x00000008,0x00040020,0x00000010,0x00000007,0x0000000a,
	0x00040015,0x00000012,0x00000020,0x00000001,0x0004002b,0x00000012,0x00000013,0x00000000,
	0x00040018,0x00000014,0x00000009,0x00000004,0x0004001e,0x00000015,0x00000014,0x00000014,
	0x00040020,0x00000016,0x00000002,0x00000015,0x0004003b,0x00000016,0x00000017,0x00000002,
	0x00040020,0x00000018,0x00000002,0x00000014,0x0004002b,0x00000006,0x0000001c,0x3f800000,
	0x0004002b,0x00000012,0x00000027,0x00000001,0x00040018,0x0000002a,0x00000007,0x00000003,
	0x0004002b,0x00000012,0x00000035,0x00000002,0x00040020,0x0000003e,0x00000007,0x00000009,
	0x00040020,0x00000044,0x00000001,0x00000007,0x0004003b,0x00000044,0x00000045,0x00000001,
	0x0004003b,0x00000044,0x00000048,0x00000001,0x00040020,0x00000050,0x00000003,0x00000007,
	0x0004003b,0x00000050,0x00000051,0x00000003,0x0004003b,0x00000050,0x00000054,0x00000003,
	0x00040020,0x00000057,0x00000003,0x00000009,0x0004003b,0x00000057,0x00000058,0x00000003,
	0x00050036,0x00000002,0x00000004,0x00000000,0x00000003,0x000200f8,0x00000005,0x0004003b,
	0x00000008,0x00000043,0x00000007,0x0004003b,0x00000008,0x00000047,0x00000007,0x0004003b,
	0x00000010,0x0000004a,0x00000007,0x0004003b,0x00000008,0x0000004b,0x00000007,0x0004003b,
	0x00000008,0x0000004d,0x00000007,0x0004003d,0x00000007,0x00000046,0x00000045,0x0003003e,
	0x00000043,0x00000046,0x0004003d,0x00000007,0x00000049,0x00000048,0x0003003e,0x00000047,
	0x00000049,0x0004003d,0x00000007,0x0000004c,0x00000043,0x0003003e,0x0000004b,0x0000004c,
	0x0004003d,0x00000007,0x0000004e,0x00000047,0x0003003e,0x0000004d,0x0000004e,0x00060039,
	0x0000000a,0x0000004f,0x0000000e,0x0000004b,0x0000004d,0x0003003e,0x0000004a,0x0000004f,
	0x00050041,0x00000008,0x00000052,0x0000004a,0x00000013,0x0004003d,0x00000007,0x00000053,
	0x00000052,0x0003003e,0x00000051,0x00000053,0x00050041,0x00000008,0x00000055,0x0000004a,
	0x00000027,0x0004003d,0x00000007,0x00000056,0x00000055,0x0003003e,0x00000054,0x00000056,
	0x00050041,0x0000003e,0x00000059,0x0000004a,0x00000035,0x0004003d,0x00000009,0x0000005a,
	0x00000059,0x0003003e,0x00000058,0x0000005a,0x000100fd,0x00010038,0x00050036,0x0000000a,
	0x0000000e,0x00000000,0x0000000b,0x00030037,0x00000008,0x0000000c,0x00030037,0x00000008,
	0x0000000d,0x000200f8,0x0000000f,0x0004003b,0x00000010,0x00000011,0x00000007,0x00050041,
	0x00000018,0x00000019,0x00000017,0x00000013,0x0004003d,0x00000014,0x0000001a,0x00000019,
	0x0004003d,0x00000007,0x0000001b,0x0000000c,0x00050051,0x00000006,0x0000001d,0x0000001b,
	0x00000000,0x00050051,0x00000006,0x0000001e,0x0000001b,0x00000001,0x00050051,0x00000006,
	0x0000001f,0x0000001b,0x00000002,0x00070050,0x00000009,0x00000020,0x0000001d,0x0000001e,
	0x0000001f,0x0000001c,0x00050091,0x00000009,0x00000021,0x0000001a,0x00000020,0x00050051,
	0x00000006,0x00000022,0x00000021,0x00000000,0x00050051,0x00000006,0x00000023,0x00000021,
	0x00000001,0x00050051,0x00000006,0x00000024,0x00000021,0x00000002,0x00060050,0x00000007,
	0x00000025,0x00000022,0x00000023,0x00000024,0x00050041,0x00000008,0x00000026,0x00000011,
	0x00000013,0x0003003e,0x00000026,0x00000025,0x00050041,0x00000018,0x00000028,0x00000017,
	0x00000013,0x0004003d,0x00000014,0x00000029,0x00000028,0x00050051,0x00000009,0x0000002b,
	0x00000029,0x00000000,0x0008004f,0x00000007,0x0000002c,0x0000002b,0x0000002b,0x00000000,
	0x00000001,0x00000002,0x00050051,0x00000009,0x0000002d,0x00000029,0x00000001,0x0008004f,
	0x00000007,0x0000002e,0x0000002d,0x0000002d,0x00000000,0x00000001,0x00000002,0x00050051,
	0x00000009,0x0000002f,0x00000029,0x00000002,0x0008004f,0x00000007,0x00000030,0x0000002f,
	0x0000002f,0x00000000,0x00000001,0x00000002,0x00060050,0x0000002a,0x00000031,0x0000002c,
	0x0000002e,0x00000030,0x0004003d,0x00000007,0x00000032,0x0000000d,0x00050091,0x00000007,
	0x00000033,0x00000031,0x00000032,0x00050041,0x00000008,0x00000034,0x00000011,0x00000027,
	0x0003003e,0x00000034,0x00000033,0x00050041,0x00000018,0x00000036,0x00000017,0x00000027,
	0x0004003d,0x00000014,0x00000037,0x00000036,0x0004003d,0x00000007,0x00000038,0x0000000c,
	0x00050051,0x00000006,0x00000039,0x00000038,0x00000000,0x00050051,0x00000006,0x0000003a,
	0x00000038,0x00000001,0x00050051,0x00000006,0x0000003b,0x00000038,0x00000002,0x00070050,
	0x00000009,0x0000003c,0x00000039,0x0000003a,0x0000003b,0x0000001c,0x00050091,0x00000009,
	0x0000003d,0x00000037,0x0000003c,0x00050041,0x0000003e,0x0000003f,0x00000011,0x00000035,
	0x0003003e,0x0000003f,0x0000003d,0x0004003d,0x0000000a,0x00000040,0x00000011,0x000200fe,
	0x00000040,0x00010038
};

//	struct LightVectorData
//	{
//		float3 vToL;
//		float3 dirToL;
//		float distToL;
//	};
//	
//	LightVectorData CalculateLightVectorData(const in float3 lightPos, const in float3 fragPos)
//	{
//		LightVectorData lv;
//		lv.vToL = lightPos - fragPos;
//		lv.distToL = length(lv.vToL);
//		lv.dirToL = lv.vToL / lv.distToL;
//		return lv;
//	}
//	
//	float3 MapNormal(
//		const in float3 tan,
//		const in float3 bitan,
//		const in float3 normal,
//		const in float2 tc,
//		uniform Texture2D nmap,
//		uniform SamplerState splr)
//	{
//		// build the tranform (rotation) into same space as tan/bitan/normal (target space)
//		const float3x3 tanToTarget = float3x3(tan, bitan, normal);
//		// sample and unpack the normal from texture into target space   
//		const float3 normalSample = nmap.Sample(splr, tc).xyz;
//		const float3 tanNormal = normalSample * 2.0f - 1.0f;
//		// bring normal from tanspace into target space
//		return normalize(mul(tanNormal, tanToTarget));
//	}
//	
//	float Attenuate(uniform float attConst, uniform float attLin, uniform float attQuad, const in float distFragToL)
//	{
//		return 1.0f / (attConst + attLin * distFragToL + attQuad * (distFragToL * distFragToL));
//	}
//	
//	float3 Diffuse(
//		uniform float3 diffuseColor,
//		uniform float diffuseIntensity,
//		const in float att,
//		const in float3 viewDirFragToL,
//		const in float3 viewNormal)
//	{
//		return diffuseColor * diffuseIntensity * att * max(0.0f, dot(viewDirFragToL, viewNormal));
//	}
//	
//	float3 Speculate(
//		const in float3 specularColor,
//		uniform float specularIntensity,
//		const in float3 viewNormal,
//		const in float3 viewFragToL,
//		const in float3 viewPos,
//		const in float att,
//		const in float specularPower)
//	{
//		// calculate reflected light vector
//		const float3 w = viewNormal * dot(viewFragToL, viewNormal);
//		const float3 r = normalize(w * 2.0f - viewFragToL);
//		// vector from camera to fragment (in view space)
//		const float3 viewCamToFrag = normalize(viewPos);
//		// calculate specular component color based on angle between
//		// viewing vector and reflection vector, narrow with power function
//		return att * specularColor * specularIntensity * pow(max(0.0f, dot(-r, viewCamToFrag)), specularPower);
//	}
//	
//	
//	cbuffer PointLightCBuf : register(b1)
//	{
//		float3 viewLightPos;
//		float3 ambient;
//		float3 diffuseColor;
//		float diffuseIntensity;
//		float attConst;
//		float attLin;
//		float attQuad;
//	};
//	cbuffer ObjectCBuf : register(b2)
//	{
//		float3 materialColor;
//		float3 specularColor;
//		float specularWeight;
//		float specularGloss;
//	};
//	
//	
//	float4 main(float3 viewFragPos : Position, float3 viewNormal : Normal) : SV_Target
//	{
//		// normalize the mesh normal
//		viewNormal = normalize(viewNormal);
//	// fragment to light vector data
//	const LightVectorData lv = CalculateLightVectorData(viewLightPos, viewFragPos);
//	// attenuation
//	const float att = Attenuate(attConst, attLin, attQuad, lv.distToL);
//	// diffuse
//	const float3 diffuse = Diffuse(diffuseColor, diffuseIntensity, att, lv.dirToL, viewNormal);
//	// specular
//	const float3 specular = Speculate(
//		diffuseColor * diffuseIntensity * specularColor, specularWeight, viewNormal,
//		lv.vToL, viewFragPos, att, specularGloss
//	);
//	// final color
//	return float4(saturate((diffuse + ambient) * materialColor + specular), 1.0f);
//	}
	// 1011.0.0
const uint32_t Phong_PS[] = {
	0x07230203,0x00010000,0x0008000a,0x000000e2,0x00000000,0x00020011,0x00000001,0x0006000b,
	0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
	0x0008000f,0x00000004,0x00000004,0x6e69616d,0x00000000,0x000000d6,0x000000d9,0x000000dc,
	0x00030010,0x00000004,0x00000007,0x00030003,0x00000005,0x000001f4,0x00040005,0x00000004,
	0x6e69616d,0x00000000,0x00060005,0x00000009,0x6867694c,0x63655674,0x44726f74,0x00617461,
	0x00050006,0x00000009,0x00000000,0x4c6f5476,0x00000000,0x00050006,0x00000009,0x00000001,
	0x54726964,0x00004c6f,0x00050006,0x00000009,0x00000002,0x74736964,0x004c6f54,0x000b0005,
	0x0000000d,0x636c6143,0x74616c75,0x67694c65,0x65567468,0x726f7463,0x61746144,0x33667628,
	0x3366763b,0x0000003b,0x00050005,0x0000000b,0x6867696c,0x736f5074,0x00000000,0x00040005,
	0x0000000c,0x67617266,0x00736f50,0x00080005,0x00000015,0x65747441,0x7461756e,0x31662865,
	0x3b31663b,0x663b3166,0x00003b31,0x00050005,0x00000011,0x43747461,0x74736e6f,0x00000000,
	0x00040005,0x00000012,0x4c747461,0x00006e69,0x00040005,0x00000013,0x51747461,0x00646175,
	0x00050005,0x00000014,0x74736964,0x67617246,0x004c6f54,0x00090005,0x0000001d,0x66666944,
	0x28657375,0x3b336676,0x663b3166,0x66763b31,0x66763b33,0x00003b33,0x00060005,0x00000018,
	0x66666964,0x43657375,0x726f6c6f,0x00000000,0x00070005,0x00000019,0x66666964,0x49657375,
	0x6e65746e,0x79746973,0x00000000,0x00030005,0x0000001a,0x00747461,0x00060005,0x0000001b,
	0x77656976,0x46726944,0x54676172,0x00004c6f,0x00050005,0x0000001c,0x77656976,0x6d726f4e,
	0x00006c61,0x000b0005,0x00000027,0x63657053,0x74616c75,0x66762865,0x31663b33,0x3366763b,
	0x3366763b,0x3366763b,0x3b31663b,0x003b3166,0x00060005,0x00000020,0x63657073,0x72616c75,
	0x6f6c6f43,0x00000072,0x00070005,0x00000021,0x63657073,0x72616c75,0x65746e49,0x7469736e,
	0x00000079,0x00050005,0x00000022,0x77656976,0x6d726f4e,0x00006c61,0x00050005,0x00000023,
	0x77656976,0x67617246,0x004c6f54,0x00040005,0x00000024,0x77656976,0x00736f50,0x00030005,
	0x00000025,0x00747461,0x00060005,0x00000026,0x63657073,0x72616c75,0x65776f50,0x00000072,
	0x00060005,0x0000002d,0x69616d40,0x6676286e,0x66763b33,0x00003b33,0x00050005,0x0000002b,
	0x77656976,0x67617246,0x00736f50,0x00050005,0x0000002c,0x77656976,0x6d726f4e,0x00006c61,
	0x00030005,0x00000030,0x0000766c,0x00030005,0x0000005e,0x00000077,0x00030005,0x00000064,
	0x00000072,0x00060005,0x0000006b,0x77656976,0x546d6143,0x6172466f,0x00000067,0x00030005,
	0x0000007e,0x0000766c,0x00060005,0x0000007f,0x6e696f50,0x67694c74,0x42437468,0x00006675,
	0x00070006,0x0000007f,0x00000000,0x77656976,0x6867694c,0x736f5074,0x00000000,0x00050006,
	0x0000007f,0x00000001,0x69626d61,0x00746e65,0x00070006,0x0000007f,0x00000002,0x66666964,
	0x43657375,0x726f6c6f,0x00000000,0x00080006,0x0000007f,0x00000003,0x66666964,0x49657375,
	0x6e65746e,0x79746973,0x00000000,0x00060006,0x0000007f,0x00000004,0x43747461,0x74736e6f,
	0x00000000,0x00050006,0x0000007f,0x00000005,0x4c747461,0x00006e69,0x00050006,0x0000007f,
	0x00000006,0x51747461,0x00646175,0x00030005,0x00000081,0x00000000,0x00040005,0x00000082,
	0x61726170,0x0000006d,0x00040005,0x00000086,0x61726170,0x0000006d,0x00030005,0x00000089,
	0x00747461,0x00040005,0x00000094,0x61726170,0x0000006d,0x00040005,0x00000098,0x66666964,
	0x00657375,0x00040005,0x0000009e,0x61726170,0x0000006d,0x00040005,0x000000a0,0x61726170,
	0x0000006d,0x00040005,0x000000a3,0x61726170,0x0000006d,0x00050005,0x000000a6,0x63657073,
	0x72616c75,0x00000000,0x00050005,0x000000ac,0x656a624f,0x42437463,0x00006675,0x00070006,
	0x000000ac,0x00000000,0x6574616d,0x6c616972,0x6f6c6f43,0x00000072,0x00070006,0x000000ac,
	0x00000001,0x63657073,0x72616c75,0x6f6c6f43,0x00000072,0x00070006,0x000000ac,0x00000002,
	0x63657073,0x72616c75,0x67696557,0x00007468,0x00070006,0x000000ac,0x00000003,0x63657073,
	0x72616c75,0x736f6c47,0x00000073,0x00030005,0x000000ae,0x00000000,0x00040005,0x000000b4,
	0x61726170,0x0000006d,0x00040005,0x000000b5,0x61726170,0x0000006d,0x00040005,0x000000b7,
	0x61726170,0x0000006d,0x00040005,0x000000ba,0x61726170,0x0000006d,0x00040005,0x000000bc,
	0x61726170,0x0000006d,0x00040005,0x000000be,0x61726170,0x0000006d,0x00050005,0x000000d4,
	0x77656976,0x67617246,0x00736f50,0x00050005,0x000000d6,0x77656976,0x67617246,0x00736f50,
	0x00050005,0x000000d8,0x77656976,0x6d726f4e,0x00006c61,0x00050005,0x000000d9,0x77656976,
	0x6d726f4e,0x00006c61,0x00070005,0x000000dc,0x746e6540,0x6f507972,0x4f746e69,0x75707475,
	0x00000074,0x00040005,0x000000dd,0x61726170,0x0000006d,0x00040005,0x000000df,0x61726170,
	0x0000006d,0x00050048,0x0000007f,0x00000000,0x00000023,0x00000000,0x00050048,0x0000007f,
	0x00000001,0x00000023,0x00000010,0x00050048,0x0000007f,0x00000002,0x00000023,0x00000020,
	0x00050048,0x0000007f,0x00000003,0x00000023,0x0000002c,0x00050048,0x0000007f,0x00000004,
	0x00000023,0x00000030,0x00050048,0x0000007f,0x00000005,0x00000023,0x00000034,0x00050048,
	0x0000007f,0x00000006,0x00000023,0x00000038,0x00030047,0x0000007f,0x00000002,0x00040047,
	0x00000081,0x00000022,0x00000001,0x00040047,0x00000081,0x00000021,0x00000001,0x00050048,
	0x000000ac,0x00000000,0x00000023,0x00000000,0x00050048,0x000000ac,0x00000001,0x00000023,
	0x00000010,0x00050048,0x000000ac,0x00000002,0x00000023,0x0000001c,0x00050048,0x000000ac,
	0x00000003,0x00000023,0x00000020,0x00030047,0x000000ac,0x00000002,0x00040047,0x000000ae,
	0x00000022,0x00000000,0x00040047,0x000000ae,0x00000021,0x00000002,0x00040047,0x000000d6,
	0x0000001e,0x00000000,0x00040047,0x000000d9,0x0000001e,0x00000001,0x00040047,0x000000dc,
	0x0000001e,0x00000000,0x00020013,0x00000002,0x00030021,0x00000003,0x00000002,0x00030016,
	0x00000006,0x00000020,0x00040017,0x00000007,0x00000006,0x00000003,0x00040020,0x00000008,
	0x00000007,0x00000007,0x0005001e,0x00000009,0x00000007,0x00000007,0x00000006,0x00050021,
	0x0000000a,0x00000009,0x00000008,0x00000008,0x00040020,0x0000000f,0x00000007,0x00000006,
	0x00070021,0x00000010,0x00000006,0x00000006,0x00000006,0x00000006,0x0000000f,0x00080021,
	0x00000017,0x00000007,0x00000007,0x00000006,0x0000000f,0x00000008,0x00000008,0x000a0021,
	0x0000001f,0x00000007,0x00000008,0x00000006,0x00000008,0x00000008,0x00000008,0x0000000f,
	0x0000000f,0x00040017,0x00000029,0x00000006,0x00000004,0x00050021,0x0000002a,0x00000029,
	0x00000008,0x00000008,0x00040020,0x0000002f,0x00000007,0x00000009,0x00040015,0x00000031,
	0x00000020,0x00000001,0x0004002b,0x00000031,0x00000032,0x00000000,0x0004002b,0x00000031,
	0x00000037,0x00000002,0x0004002b,0x00000031,0x0000003c,0x00000001,0x0004002b,0x00000006,
	0x00000047,0x3f800000,0x0004002b,0x00000006,0x00000056,0x00000000,0x0004002b,0x00000006,
	0x00000066,0x40000000,0x0009001e,0x0000007f,0x00000007,0x00000007,0x00000007,0x00000006,
	0x00000006,0x00000006,0x00000006,0x00040020,0x00000080,0x00000002,0x0000007f,0x0004003b,
	0x00000080,0x00000081,0x00000002,0x00040020,0x00000083,0x00000002,0x00000007,0x0004002b,
	0x00000031,0x0000008a,0x00000004,0x00040020,0x0000008b,0x00000002,0x00000006,0x0004002b,
	0x00000031,0x0000008e,0x00000005,0x0004002b,0x00000031,0x00000091,0x00000006,0x0004002b,
	0x00000031,0x0000009b,0x00000003,0x0006001e,0x000000ac,0x00000007,0x00000007,0x00000006,
	0x00000006,0x00040020,0x000000ad,0x00000002,0x000000ac,0x0004003b,0x000000ad,0x000000ae,
	0x00000002,0x00040020,0x000000d5,0x00000001,0x00000007,0x0004003b,0x000000d5,0x000000d6,
	0x00000001,0x0004003b,0x000000d5,0x000000d9,0x00000001,0x00040020,0x000000db,0x00000003,
	0x00000029,0x0004003b,0x000000db,0x000000dc,0x00000003,0x00050036,0x00000002,0x00000004,
	0x00000000,0x00000003,0x000200f8,0x00000005,0x0004003b,0x00000008,0x000000d4,0x00000007,
	0x0004003b,0x00000008,0x000000d8,0x00000007,0x0004003b,0x00000008,0x000000dd,0x00000007,
	0x0004003b,0x00000008,0x000000df,0x00000007,0x0004003d,0x00000007,0x000000d7,0x000000d6,
	0x0003003e,0x000000d4,0x000000d7,0x0004003d,0x00000007,0x000000da,0x000000d9,0x0003003e,
	0x000000d8,0x000000da,0x0004003d,0x00000007,0x000000de,0x000000d4,0x0003003e,0x000000dd,
	0x000000de,0x0004003d,0x00000007,0x000000e0,0x000000d8,0x0003003e,0x000000df,0x000000e0,
	0x00060039,0x00000029,0x000000e1,0x0000002d,0x000000dd,0x000000df,0x0003003e,0x000000dc,
	0x000000e1,0x000100fd,0x00010038,0x00050036,0x00000009,0x0000000d,0x00000000,0x0000000a,
	0x00030037,0x00000008,0x0000000b,0x00030037,0x00000008,0x0000000c,0x000200f8,0x0000000e,
	0x0004003b,0x0000002f,0x00000030,0x00000007,0x0004003d,0x00000007,0x00000033,0x0000000b,
	0x0004003d,0x00000007,0x00000034,0x0000000c,0x00050083,0x00000007,0x00000035,0x00000033,
	0x00000034,0x00050041,0x00000008,0x00000036,0x00000030,0x00000032,0x0003003e,0x00000036,
	0x00000035,0x00050041,0x00000008,0x00000038,0x00000030,0x00000032,0x0004003d,0x00000007,
	0x00000039,0x00000038,0x0006000c,0x00000006,0x0000003a,0x00000001,0x00000042,0x00000039,
	0x00050041,0x0000000f,0x0000003b,0x00000030,0x00000037,0x0003003e,0x0000003b,0x0000003a,
	0x00050041,0x00000008,0x0000003d,0x00000030,0x00000032,0x0004003d,0x00000007,0x0000003e,
	0x0000003d,0x00050041,0x0000000f,0x0000003f,0x00000030,0x00000037,0x0004003d,0x00000006,
	0x00000040,0x0000003f,0x00060050,0x00000007,0x00000041,0x00000040,0x00000040,0x00000040,
	0x00050088,0x00000007,0x00000042,0x0000003e,0x00000041,0x00050041,0x00000008,0x00000043,
	0x00000030,0x0000003c,0x0003003e,0x00000043,0x00000042,0x0004003d,0x00000009,0x00000044,
	0x00000030,0x000200fe,0x00000044,0x00010038,0x00050036,0x00000006,0x00000015,0x00000000,
	0x00000010,0x00030037,0x00000006,0x00000011,0x00030037,0x00000006,0x00000012,0x00030037,
	0x00000006,0x00000013,0x00030037,0x0000000f,0x00000014,0x000200f8,0x00000016,0x0004003d,
	0x00000006,0x00000048,0x00000014,0x00050085,0x00000006,0x00000049,0x00000012,0x00000048,
	0x00050081,0x00000006,0x0000004a,0x00000011,0x00000049,0x0004003d,0x00000006,0x0000004b,
	0x00000014,0x0004003d,0x00000006,0x0000004c,0x00000014,0x00050085,0x00000006,0x0000004d,
	0x0000004b,0x0000004c,0x00050085,0x00000006,0x0000004e,0x00000013,0x0000004d,0x00050081,
	0x00000006,0x0000004f,0x0000004a,0x0000004e,0x00050088,0x00000006,0x00000050,0x00000047,
	0x0000004f,0x000200fe,0x00000050,0x00010038,0x00050036,0x00000007,0x0000001d,0x00000000,
	0x00000017,0x00030037,0x00000007,0x00000018,0x00030037,0x00000006,0x00000019,0x00030037,
	0x0000000f,0x0000001a,0x00030037,0x00000008,0x0000001b,0x00030037,0x00000008,0x0000001c,
	0x000200f8,0x0000001e,0x0005008e,0x00000007,0x00000053,0x00000018,0x00000019,0x0004003d,
	0x00000006,0x00000054,0x0000001a,0x0005008e,0x00000007,0x00000055,0x00000053,0x00000054,
	0x0004003d,0x00000007,0x00000057,0x0000001b,0x0004003d,0x00000007,0x00000058,0x0000001c,
	0x00050094,0x00000006,0x00000059,0x00000057,0x00000058,0x0007000c,0x00000006,0x0000005a,
	0x00000001,0x00000028,0x00000056,0x00000059,0x0005008e,0x00000007,0x0000005b,0x00000055,
	0x0000005a,0x000200fe,0x0000005b,0x00010038,0x00050036,0x00000007,0x00000027,0x00000000,
	0x0000001f,0x00030037,0x00000008,0x00000020,0x00030037,0x00000006,0x00000021,0x00030037,
	0x00000008,0x00000022,0x00030037,0x00000008,0x00000023,0x00030037,0x00000008,0x00000024,
	0x00030037,0x0000000f,0x00000025,0x00030037,0x0000000f,0x00000026,0x000200f8,0x00000028,
	0x0004003b,0x00000008,0x0000005e,0x00000007,0x0004003b,0x00000008,0x00000064,0x00000007,
	0x0004003b,0x00000008,0x0000006b,0x00000007,0x0004003d,0x00000007,0x0000005f,0x00000022,
	0x0004003d,0x00000007,0x00000060,0x00000023,0x0004003d,0x00000007,0x00000061,0x00000022,
	0x00050094,0x00000006,0x00000062,0x00000060,0x00000061,0x0005008e,0x00000007,0x00000063,
	0x0000005f,0x00000062,0x0003003e,0x0000005e,0x00000063,0x0004003d,0x00000007,0x00000065,
	0x0000005e,0x0005008e,0x00000007,0x00000067,0x00000065,0x00000066,0x0004003d,0x00000007,
	0x00000068,0x00000023,0x00050083,0x00000007,0x00000069,0x00000067,0x00000068,0x0006000c,
	0x00000007,0x0000006a,0x00000001,0x00000045,0x00000069,0x0003003e,0x00000064,0x0000006a,
	0x0004003d,0x00000007,0x0000006c,0x00000024,0x0006000c,0x00000007,0x0000006d,0x00000001,
	0x00000045,0x0000006c,0x0003003e,0x0000006b,0x0000006d,0x0004003d,0x00000006,0x0000006e,
	0x00000025,0x0004003d,0x00000007,0x0000006f,0x00000020,0x0005008e,0x00000007,0x00000070,
	0x0000006f,0x0000006e,0x0005008e,0x00000007,0x00000071,0x00000070,0x00000021,0x0004003d,
	0x00000007,0x00000072,0x00000064,0x0004007f,0x00000007,0x00000073,0x00000072,0x0004003d,
	0x00000007,0x00000074,0x0000006b,0x00050094,0x00000006,0x00000075,0x00000073,0x00000074,
	0x0007000c,0x00000006,0x00000076,0x00000001,0x00000028,0x00000056,0x00000075,0x0004003d,
	0x00000006,0x00000077,0x00000026,0x0007000c,0x00000006,0x00000078,0x00000001,0x0000001a,
	0x00000076,0x00000077,0x0005008e,0x00000007,0x00000079,0x00000071,0x00000078,0x000200fe,
	0x00000079,0x00010038,0x00050036,0x00000029,0x0000002d,0x00000000,0x0000002a,0x00030037,
	0x00000008,0x0000002b,0x00030037,0x00000008,0x0000002c,0x000200f8,0x0000002e,0x0004003b,
	0x0000002f,0x0000007e,0x00000007,0x0004003b,0x00000008,0x00000082,0x00000007,0x0004003b,
	0x00000008,0x00000086,0x00000007,0x0004003b,0x0000000f,0x00000089,0x00000007,0x0004003b,
	0x0000000f,0x00000094,0x00000007,0x0004003b,0x00000008,0x00000098,0x00000007,0x0004003b,
	0x0000000f,0x0000009e,0x00000007,0x0004003b,0x00000008,0x000000a0,0x00000007,0x0004003b,
	0x00000008,0x000000a3,0x00000007,0x0004003b,0x00000008,0x000000a6,0x00000007,0x0004003b,
	0x00000008,0x000000b4,0x00000007,0x0004003b,0x00000008,0x000000b5,0x00000007,0x0004003b,
	0x00000008,0x000000b7,0x00000007,0x0004003b,0x00000008,0x000000ba,0x00000007,0x0004003b,
	0x0000000f,0x000000bc,0x00000007,0x0004003b,0x0000000f,0x000000be,0x00000007,0x0004003d,
	0x00000007,0x0000007c,0x0000002c,0x0006000c,0x00000007,0x0000007d,0x00000001,0x00000045,
	0x0000007c,0x0003003e,0x0000002c,0x0000007d,0x00050041,0x00000083,0x00000084,0x00000081,
	0x00000032,0x0004003d,0x00000007,0x00000085,0x00000084,0x0003003e,0x00000082,0x00000085,
	0x0004003d,0x00000007,0x00000087,0x0000002b,0x0003003e,0x00000086,0x00000087,0x00060039,
	0x00000009,0x00000088,0x0000000d,0x00000082,0x00000086,0x0003003e,0x0000007e,0x00000088,
	0x00050041,0x0000008b,0x0000008c,0x00000081,0x0000008a,0x0004003d,0x00000006,0x0000008d,
	0x0000008c,0x00050041,0x0000008b,0x0000008f,0x00000081,0x0000008e,0x0004003d,0x00000006,
	0x00000090,0x0000008f,0x00050041,0x0000008b,0x00000092,0x00000081,0x00000091,0x0004003d,
	0x00000006,0x00000093,0x00000092,0x00050041,0x0000000f,0x00000095,0x0000007e,0x00000037,
	0x0004003d,0x00000006,0x00000096,0x00000095,0x0003003e,0x00000094,0x00000096,0x00080039,
	0x00000006,0x00000097,0x00000015,0x0000008d,0x00000090,0x00000093,0x00000094,0x0003003e,
	0x00000089,0x00000097,0x00050041,0x00000083,0x00000099,0x00000081,0x00000037,0x0004003d,
	0x00000007,0x0000009a,0x00000099,0x00050041,0x0000008b,0x0000009c,0x00000081,0x0000009b,
	0x0004003d,0x00000006,0x0000009d,0x0000009c,0x0004003d,0x00000006,0x0000009f,0x00000089,
	0x0003003e,0x0000009e,0x0000009f,0x00050041,0x00000008,0x000000a1,0x0000007e,0x0000003c,
	0x0004003d,0x00000007,0x000000a2,0x000000a1,0x0003003e,0x000000a0,0x000000a2,0x0004003d,
	0x00000007,0x000000a4,0x0000002c,0x0003003e,0x000000a3,0x000000a4,0x00090039,0x00000007,
	0x000000a5,0x0000001d,0x0000009a,0x0000009d,0x0000009e,0x000000a0,0x000000a3,0x0003003e,
	0x00000098,0x000000a5,0x00050041,0x00000083,0x000000a7,0x00000081,0x00000037,0x0004003d,
	0x00000007,0x000000a8,0x000000a7,0x00050041,0x0000008b,0x000000a9,0x00000081,0x0000009b,
	0x0004003d,0x00000006,0x000000aa,0x000000a9,0x0005008e,0x00000007,0x000000ab,0x000000a8,
	0x000000aa,0x00050041,0x00000083,0x000000af,0x000000ae,0x0000003c,0x0004003d,0x00000007,
	0x000000b0,0x000000af,0x00050085,0x00000007,0x000000b1,0x000000ab,0x000000b0,0x00050041,
	0x0000008b,0x000000b2,0x000000ae,0x00000037,0x0004003d,0x00000006,0x000000b3,0x000000b2,
	0x0003003e,0x000000b4,0x000000b1,0x0004003d,0x00000007,0x000000b6,0x0000002c,0x0003003e,
	0x000000b5,0x000000b6,0x00050041,0x00000008,0x000000b8,0x0000007e,0x00000032,0x0004003d,
	0x00000007,0x000000b9,0x000000b8,0x0003003e,0x000000b7,0x000000b9,0x0004003d,0x00000007,
	0x000000bb,0x0000002b,0x0003003e,0x000000ba,0x000000bb,0x0004003d,0x00000006,0x000000bd,
	0x00000089,0x0003003e,0x000000bc,0x000000bd,0x00050041,0x0000008b,0x000000bf,0x000000ae,
	0x0000009b,0x0004003d,0x00000006,0x000000c0,0x000000bf,0x0003003e,0x000000be,0x000000c0,
	0x000b0039,0x00000007,0x000000c1,0x00000027,0x000000b4,0x000000b3,0x000000b5,0x000000b7,
	0x000000ba,0x000000bc,0x000000be,0x0003003e,0x000000a6,0x000000c1,0x0004003d,0x00000007,
	0x000000c2,0x00000098,0x00050041,0x00000083,0x000000c3,0x00000081,0x0000003c,0x0004003d,
	0x00000007,0x000000c4,0x000000c3,0x00050081,0x00000007,0x000000c5,0x000000c2,0x000000c4,
	0x00050041,0x00000083,0x000000c6,0x000000ae,0x00000032,0x0004003d,0x00000007,0x000000c7,
	0x000000c6,0x00050085,0x00000007,0x000000c8,0x000000c5,0x000000c7,0x0004003d,0x00000007,
	0x000000c9,0x000000a6,0x00050081,0x00000007,0x000000ca,0x000000c8,0x000000c9,0x00060050,
	0x00000007,0x000000cb,0x00000056,0x00000056,0x00000056,0x00060050,0x00000007,0x000000cc,
	0x00000047,0x00000047,0x00000047,0x0008000c,0x00000007,0x000000cd,0x00000001,0x0000002b,
	0x000000ca,0x000000cb,0x000000cc,0x00050051,0x00000006,0x000000ce,0x000000cd,0x00000000,
	0x00050051,0x00000006,0x000000cf,0x000000cd,0x00000001,0x00050051,0x00000006,0x000000d0,
	0x000000cd,0x00000002,0x00070050,0x00000029,0x000000d1,0x000000ce,0x000000cf,0x000000d0,
	0x00000047,0x000200fe,0x000000d1,0x00010038
};


constexpr ShaderPair Phong =
{
	.VSShaderTag = "Phong_VS",
	.PSShaderTag = "Phong_PS",
	.VSShaderEntry = "main",
	.PSShaderEntry = "main",
	.VSShaderBytecode = Phong_VS,
	.PSShaderBytecode = Phong_PS
};
