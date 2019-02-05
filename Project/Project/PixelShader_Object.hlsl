/************************************************************************
* Filename:  		PixelShader_Object.hlsl
* Date:      		11/10/2018
* Mod. Date: 		11/10/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Specific PixelShader for Rendering Mage model
*************************************************************************/

texture2D tTexture : register(t0);
texture2D tTexture1 : register(t1);
texture2D tTexture2 : register(t2);
texture2D tTexture4 : register(t3);

SamplerState sSampler_State[2] : register(s0);

cbuffer CBUFF : register(b0)
{
	float4 light_pos;
	float4 light_col;
	float4 light_nrm;
	float4 ambient;
	float4 diffuse;
	float4 emissive;
	float4 reflection;
	float4 shininess;
	float4 specular;
	float4 transparency;
	float4 tint;
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
	float4 final_color;
	float4 light_color = light_col;
	float3 light_dir, light_dir_norm;
	float attenuation, ratio;

	float4 diffuse_color = tTexture.Sample(sSampler_State[0], input.fTexture.xy);
	diffuse_color.x = diffuse_color.x * diffuse.x * diffuse.w;
	diffuse_color.y = diffuse_color.y * diffuse.y * diffuse.w;
	diffuse_color.z = diffuse_color.z * diffuse.z * diffuse.w;

	float4 emissive_color = tTexture1.Sample(sSampler_State[0], input.fTexture.xy);
	emissive_color.x = emissive_color.x * emissive.x * emissive.w;
	emissive_color.y = emissive_color.y * emissive.y * emissive.w;
	emissive_color.z = emissive_color.z * emissive.z * emissive.w;

	float4 specular_color = tTexture2.Sample(sSampler_State[0], input.fTexture.xy);
	specular_color.x = specular_color.x * specular.x * specular.w;
	specular_color.y = specular_color.y * specular.y * specular.w;
	specular_color.z = specular_color.z * specular.z * specular.w;

	float4 combined_color;
	combined_color.x = diffuse_color.x + emissive_color.x + specular_color.x;
	combined_color.y = diffuse_color.y + emissive_color.y + specular_color.y;
	combined_color.z = diffuse_color.z + emissive_color.z + specular_color.z;
	combined_color.w = 1.0f;

	// Point Light
	//	LIGHTDIR = NORMALIZE(LIGHTPOS – SURFACEPOS)

	light_dir = light_pos.xyz - input.fWorld_Position.xyz;
	light_dir_norm = normalize(light_dir);

	//	LIGHTRATIO = CLAMP(DOT(LIGHTDIR, SURFACENORMAL))
	//ratio = saturate(dot(light_dir_norm, normalize(tTexture4.Sample(sSampler_State[0], input.fTexture))));

	ratio = saturate(dot(light_dir_norm, normalize(input.fNormal.xyz)));

	//	RESULT = LIGHTRATIO * LIGHTCOLOR * SURFACECOLOR

	final_color = combined_color;// +(light_col * ratio);

	//	ATTENUATION = 1.0 – CLAMP(MAGNITUDE(LIGHTPOS – SURFACEPOS) / LIGHTRADIUS)
	//attenuation = 1.0f - saturate(length(light_dir) / 13.0f);
	//attenuation *= attenuation;
	//final_color *= attenuation;
	final_color.a = combined_color.a;

	//if (tint.x == 1)
	//	final_color.x += 1;
	//
	//if (tint.y == 1)
	//	final_color.y += 1;
	//
	//if (tint.z == 1)
	//	final_color.z += 1;

	final_color.x += tint.x;
	final_color.y += tint.y;
	final_color.z += tint.z;

	return final_color;

	//return light_col;
}