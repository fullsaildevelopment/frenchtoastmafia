Texture2D tex1 : register(t0);

//Texture2D tex2 : register(t1);
//
//Texture2D tex3 : register(t2);

SamplerState filter : register(s0);

cbuffer PhongForShader : register(b0)
{
	float3 ambient;
	float3 diffuse;
	float3 emissive;
	float3 specular;

	float transparency;
	float shininess;
	float reflection;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 worldPos : POSITION;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{

	float4 ambient = { 0.5, 0.5, 0.5, 1 };

float4 pointLightColor = { 0.5, 0.5, 3.0, 1 };

float3 pointLightPos = { 7.0f , 3.0, 1.0 };
float3 pointLightDir = normalize(pointLightPos - input.worldPos);
float pointLightStrength = 2.0 - length(pointLightPos - input.worldPos);
if (pointLightStrength < 0)
{
	pointLightStrength = 0;
}
float pointLightRatio = pointLightStrength * clamp(dot(pointLightDir, input.normal), 0, 1);


return ambient * (tex1.Sample(filter, input.uv) + (pointLightColor * pointLightRatio));

}