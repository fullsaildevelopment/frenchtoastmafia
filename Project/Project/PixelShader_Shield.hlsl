/************************************************************************
* Filename:  		PixelShader_Screen.hlsl
* Date:      		17/10/2018
* Mod. Date: 		17/10/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Specific PixelShader for Rendering temporary screen for intro, menu, replay
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
	float4 fEnd_Color = tTexture.Sample(sSampler_State[0], input.fTexture.xy);
	/*if (fEnd_Color.a == 0)
	fEnd_Color.a = 0;
	else
	fEnd_Color.a = 0.5;*/
	return fEnd_Color;
}