
texture2D tTexture : register(t0);

SamplerState sSampler_State[2] : register(s0);

cbuffer tConstant_Buffer : register(b0)
{
	float4 fData;
};

cbuffer particle_Constant_Buffer : register(b1)
{
	float4 pData;
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
	/* float3 lDir;
	lDir.x = -1;
	lDir.y = 0;
	lDir.z = 0;*/

	float4 color;
	color.x = saturate(sin(pData.w) * sin(input.fWorld_Position)) * 50; // can use this in the VERTEX shader to make models do the wave or have moving water waves
	color.y = saturate(cos(pData.w) * cos(input.fWorld_Position)) * 50 + 0.5; // can use this in the VERTEX shader to make models do the wave or have moving water waves
	color.z = saturate(tan(pData.w)) + 0.2;         // can use this in the VERTEX shader to make models do the wave or have moving water waves
	color.w = 1.0f;

	float4 NEWcolor = saturate(color * sin(pData.w));

	float4 tColor = saturate(color.x * tan(pData.w));
	float4 sColor = saturate(color.x * sin(pData.w));
	float4 cColor = saturate(color.x * cos(pData.w));

	//float4 returnThis;                                                      // time.x          // posUV.posT.x
	//returnThis.xyz = saturate((dot(lightDirection, input.fNormal))) * color; // NEWColor          tan(time.z)
	//returnThis.w = 1;
	

	//float4 baseColor = tTexture.Sample(sSampler_State[0], input.fTexture.xy) * returnThis; // gets the base color
	
	return color;   // color // tColor // sColor // cColor
}