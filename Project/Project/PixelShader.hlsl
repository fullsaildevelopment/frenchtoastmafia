/************************************************************************
* Filename:  		PixelShader.hlsl
* Date:      		10/02/2018
* Mod. Date: 		10/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Basic PixelShader for Rendering
*************************************************************************/

texture2D tTexture : register(t0);

SamplerState sSampler_State[2] : register(s0);

cbuffer tConstant_Buffer : register(b0)
{
	float4 fData;
};

struct INPUT_DATA
{
	float4 fPosition : SV_POSITION;
	float3 fNormal : NORMAL;
	float4 fColor : COLOR;
	float2 fTexture : TEXTURE;
	float4 fWorld_Position : WORLD;
};

float4 main(INPUT_DATA input) : SV_TARGET
{
	float4 fEnd_Color;
	float4 BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 RED = float4(1.0f, 0.0f, 0.0f, 1.0f);

	fEnd_Color = BLACK;

	return fEnd_Color;
}