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
//	float4 fEnd_Color;
//float4 BLACK = float4(0.0f, 0.0f, 0.0f, 1.0f);
//float4 RED = float4(1.0f, 0.0f, 0.0f, 1.0f);
//
//if (fData.w == 1)
//fEnd_Color = RED;
//else
//fEnd_Color = BLACK;
//
//return fEnd_Color;

	float4 ambient = { 0.5, 0.5, 0.5, 1 };

float4 pointLightColor = { 0.5, 0.5, 3.0, 1 };

float3 pointLightPos = { 7.0f , 3.0, 1.0 };
float3 pointLightDir = normalize(pointLightPos - input.fWorld_Position);
float pointLightStrength = 2.0 - length(pointLightPos - input.fWorld_Position);
if (pointLightStrength < 0)
{
	pointLightStrength = 0;
}
float pointLightRatio = pointLightStrength * clamp(dot(pointLightDir, input.fNormal), 0, 1);


return ambient * (tTexture.Sample(sSampler_State[1], input.fTexture) + (pointLightColor * pointLightRatio));
}