/************************************************************************
* Filename:  		PixelShader.hlsl
* Date:      		10/02/2018
* Mod. Date: 		10/09/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Basic PixelShader for Rendering
*************************************************************************/

texture2D tTexture : register(t0);

SamplerState sSampler_State[2] : register(s0);

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
	float4 fEnd_Color = float4( 0.0f, 0.0f, 0.0f, 1.0f );
	return fEnd_Color;
}