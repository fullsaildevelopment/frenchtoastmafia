/************************************************************************
* Filename:  		VertexShader_Animation.hlsl
* Date:      		05/11/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Specific VertexShader for Rendering objects with Animation
*************************************************************************/
#pragma pack_matrix(row_major)

cbuffer tWVP : register(b0)
{
	float4x4 fWorld_Matrix;
	float4x4 fView_Matrix;
	float4x4 fProjection_Matrix;
};

cbuffer tAnimation : register(b1)
{
	float4x4 fAnimation_Data[28];
};

struct INPUT_DATA
{
	float4 fPosition : POSITION;
	float4 fNormal : NORMAL;
	float4 fColor : COLOR;
	float2 fTexture : TEXTURE;
	uint4  nJoints : JOINTS;
	float4 fWeights : WEIGHTS;
};

struct OUTPUT_DATA
{
	float4 fPosition : SV_POSITION;
	float3 fNormal : NORMAL;
	float4 fColor : COLOR;
	float2 fTexture : TEXTURE;
	float4 fWorld_Position : WORLD;
};

OUTPUT_DATA main(INPUT_DATA tInput)
{
	OUTPUT_DATA tOutput;

	float4 fCurrent_Position = float4(tInput.fPosition.xyz, 1.0f);
	float4 skinned_pos = { 0,0,0,0 };
	for (int i = 0; i < 4; ++i)
	{
		float4 anim = mul(fCurrent_Position, fAnimation_Data[tInput.nJoints[i]]);
		anim = mul(anim, tInput.fWeights[i]);
		skinned_pos += anim;
	}

	fCurrent_Position = mul(float4(skinned_pos.xyz, 1.0f), fWorld_Matrix);

	tOutput.fWorld_Position = fCurrent_Position;

	fCurrent_Position = mul(fCurrent_Position, fView_Matrix);
	fCurrent_Position = mul(fCurrent_Position, fProjection_Matrix);

	tOutput.fPosition = fCurrent_Position;
	tOutput.fNormal = mul(tInput.fNormal, fWorld_Matrix);
	tOutput.fColor = tInput.fColor;
	tOutput.fTexture = tInput.fTexture;
	return tOutput;
}