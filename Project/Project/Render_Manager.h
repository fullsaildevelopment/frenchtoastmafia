/************************************************************************
* Filename:  		Render_Manager.h
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all rendering related task.
*************************************************************************/
#pragma once

#include "DDSTextureLoader.h"
#include "Graphic_Setup.h"
#include "Renderer_Structs.h"
#include "WICTextureLoader.h"
#include "XTime.h"

#include "VertexShader_Animation.csh"
#include "VertexShader_Arena.csh"

#include "PixelShader_Arena.csh"
#include "PixelShader_Mage.csh"
#include "PixelShader_Priest.csh"
#include "PixelShader_Dragon.csh"
#include "PixelShader_Fireball.csh"
#include "PixelShader_Screen.csh"
#include "dopeSoundSystem.h"

class cRender_Manager
{
private:

	cGraphics_Setup *c_Graphics_Setup;

	dopeSoundSystem sound;

	// WVPC
	ComPtr<ID3D11Buffer> d3d_Constant_Buffer_WVP;
	ComPtr<ID3D11Buffer> d3d_Constant_Buffer_Mage;
	tConstantBuffer_PixelShader cps_mage;
	tConstantBuffer_PixelShader cps_arena;
	tConstantBuffer_PixelShader cps_dragon;
	tConstantBuffer_Dragon cps_dragonColor;
	tConstantBuffer_Dragon cps_fireballColor;
	tConstantBuffer_Dragon cps_priestColor;

	D3D11_BUFFER_DESC d3d_Constant_Buffer_Desc;
	D3D11_MAPPED_SUBRESOURCE d3d_MSR;

	tConstantBuffer_VertexShader_WVP tWVP;
	tConstantBuffer_VertexShader_Animation tAnim;
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
	// Animation
	int nAnimation_Frame;
	ComPtr<ID3D11Buffer> d3d_Constant_Buffer_Animation;

public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);
	void Load_Data(int nScene_Id, tScene_Objects* tObject_List);
	void Unload();
	void Draw(int nScene_Id, tScene_Objects* t_Object_List);
	void DrawToTexture();

	void setDragonColor(float _color);

	bool objSet = false;
	XMMATRIX tempWorld = XMMatrixIdentity();
};
