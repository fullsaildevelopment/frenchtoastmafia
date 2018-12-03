/************************************************************************
* Filename:  		Render_Manager.h
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all rendering related task.
*************************************************************************/
#pragma once

#include "Collisions.h"
#include "DDSTextureLoader.h"
#include "Graphic_Setup.h"
#include "Head_Mount.h"
#include "Renderer_Structs.h"
#include "WICTextureLoader.h"
#include "XTime.h"

#include "VertexShader_Animation.csh"
#include "VertexShader_Bullet.csh"

#include "PixelShader_Mage.csh"
#include "PixelShader_Screen.csh"
#include "dopeSoundSystem.h"

class cRender_Manager
{
private:

	cGraphics_Setup *c_Graphics_Setup;
	tCollisions t_Collisions;
	dopeSoundSystem sound;

	// WVPC
	ComPtr<ID3D11Buffer> d3d_Constant_Buffer_WVP;
	tConstantBuffer_VertexShader_WVP tWVP;

	// Resources
	D3D11_BUFFER_DESC d3d_Constant_Buffer_Desc;
	D3D11_MAPPED_SUBRESOURCE d3d_MSR;

	// Animation
	ComPtr<ID3D11Buffer> d3d_Constant_Buffer_Animation;
	tConstantBuffer_VertexShader_Animation tAnim;

	// CPS
	tConstantBuffer_PixelShader tCB_PS;
	
	//XMFLOAT4X4 fCamera_Matrix;
	//XMFLOAT4X4 fCamera_Origin;

	// TIME
	XTime cTime;

	// Dragon Behavior
	bool isHit = false;
	float flashTime = 0.5f;
	float flashTimer = 0.0f;

	bool dragonAlive;
	int dragonHealth;
	tFloat4 dragonTint;

	// Collision
	bool bCollided;
	tAABB tAABB_Bullet, tAABB_Dragon;

	// HANDS
	// left
	ComPtr<ID3D11Buffer> d3d_Left_Hand_Vertex_Buffer;
	ComPtr<ID3D11Buffer> d3d_Left_Hand_Index_Buffer;
	//ComPtr<ID3D11Buffer> d3d_Left_Hand_Material_Buffer;
	ComPtr<ID3D11VertexShader> d3d_Left_Hand_Vertex_Shader;
	ComPtr<ID3D11PixelShader> d3d_Left_Hand_Pixel_Shader;

	// right
	ComPtr<ID3D11Buffer> d3d_Right_Hand_Vertex_Buffer;
	ComPtr<ID3D11Buffer> d3d_Right_Hand_Index_Buffer;
	ComPtr<ID3D11Buffer> d3d_Right_Hand_Material_Buffer;
	//ComPtr<ID3D11VertexShader> d3d_Right_Hand_Vertex_Shader;
	ComPtr<ID3D11PixelShader> d3d_Right_Hand_Pixel_Shader;

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;

public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);
	void Load_Data(int nScene_Id, tScene_Objects* tObject_List);
	void Unload(tScene_Objects* t_Object_List);
	void Draw(int nScene_Id, tScene_Objects* t_Object_List, bool *bChange_Scene, bool *bMove_Bullet, tFloat3 lhand, cHead_Mount c_Head_Mount);
};
