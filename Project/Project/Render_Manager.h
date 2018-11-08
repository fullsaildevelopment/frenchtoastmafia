#pragma once

#include "DDSTextureLoader.h"
#include "Graphic_Setup.h"
#include "renderer_structs.h"
#include "WICTextureLoader.h"
#include "XTime.h"
#include "PixelShader_Screen.csh"
#include "VertexShader_Arena.csh"
#include "PixelShader_Arena.csh"
#include "PixelShader_Mage.csh"
#include "PixelShader_Priest.csh"
#include "PixelShader_Dragon.csh"
#include "PixelShader_Fireball.csh"

class cRender_Manager
{
private:

	cGraphics_Setup *c_Graphics_Setup;

	// WVPC
	CComPtr<ID3D11Buffer> d3d_Constant_Buffer_WVP;
	CComPtr<ID3D11Buffer> d3d_Constant_Buffer_Mage;
	tConstantBuffer_PixelShader cps_mage;
	tConstantBuffer_PixelShader cps_arena;
	tConstantBuffer_PixelShader cps_dragon;
	tConstantBuffer_Dragon cps_dragonColor;
	tConstantBuffer_Dragon cps_fireballColor;

	D3D11_BUFFER_DESC d3d_Constant_Buffer_Desc;
	D3D11_MAPPED_SUBRESOURCE d3d_MSR;

	tConstantBuffer_VertexShader_WVP tWVP;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;

	// TIME
	XTime cTime;

	// Dragon Behavior
	bool isHit = false;
	float flashTime = 0.5f;
	float flashTimer = 0.0f;

	bool dragonAlive = true;
	int dragonHealth = 7;
public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);
	void Load(int nScene_Id, tScene_Objects* t_Object_List);
	void Unload();
	void Draw(int nScene_Id, tScene_Objects t_Object_List);
	void DrawToTexture();

	void setDragonColor(float _color);

	bool objSet = false;
	XMMATRIX tempWorld = XMMatrixIdentity();
};

