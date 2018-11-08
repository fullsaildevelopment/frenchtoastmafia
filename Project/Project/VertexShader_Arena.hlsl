#pragma pack_matrix(row_major)

cbuffer tConstant_Buffer : register(b0)
{
	float4x4 fWorld_Matrix;
	float4x4 fView_Matrix;
	float4x4 fProjection_Matrix;
	float4x4 fCamera_Matrix;
	float4x4 fCamera_Origin;
};

struct INPUT_DATA
{
	float4 fPosition : POSITION;
	float4 fNormal : NORMAL;
	float4 fColor : COLOR;
	float2 fTexture : TEXTURE;
	uint4 joints : JOINTS;
	float4 weights : WEIGHTS;
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

	fCurrent_Position = mul(fCurrent_Position, fWorld_Matrix);

	tOutput.fWorld_Position = fCurrent_Position;

	fCurrent_Position = mul(fCurrent_Position, fView_Matrix);
	fCurrent_Position = mul(fCurrent_Position, fProjection_Matrix);

	tOutput.fPosition = fCurrent_Position;
	tOutput.fNormal = mul(tInput.fNormal, fWorld_Matrix);
	tOutput.fColor = tInput.fColor;
	tOutput.fTexture = tInput.fTexture;
	return tOutput;
}