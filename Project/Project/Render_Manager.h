/************************************************************************
* Filename:  		Render_Manager.h
* Date:      		02/10/2018
* Mod. Date: 		05/12/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all rendering related task.
*************************************************************************/
#pragma once

#include "Base_Spell.h"
#include "Collisions.h"
#include "Controllers.h"
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

#include "Particle.h"
#include "basic_structs.h"
#include "Effects.h"
#include "Particle_Pixel_Shader.csh"

class cRender_Manager
{
private:
	cGraphics_Setup *c_Graphics_Setup;
	cBase_Spell *c_Player_Fireball;
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

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;



	static size_t pp_vert_count;

	particle *line_vert;      // tVertex
	int line_vert_count = 0;


	//Particle p;

	// Particle Stuff
	ComPtr<ID3D11Buffer> particle_Vertex_Buffer;
	ComPtr<ID3D11PixelShader> particle_Pixel_Shader;
	ComPtr<ID3D11VertexShader> particle_Vertex_Shader;

	ComPtr<ID3D11Buffer> particle_Constant_Buffer;
	D3D11_MAPPED_SUBRESOURCE particle_Constant_Mapped_RS;

	D3D11_BUFFER_DESC particle_Const_Buff_Desc;
	D3D11_SUBRESOURCE_DATA particle_Const_Buff_Data;

	tConstantBuffer_VertexShader_Bullet tPart;

	float random_color;
	float random_alpha;
	// Particle Stuff

public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);
	void Load_Data(int nScene_Id, tScene_Objects* tObject_List);
	void Unload(tScene_Objects* t_Object_List);
	void Draw_Personal(tScene_Objects* t_Object_List, cHead_Mount c_Head_Mount, cControllers c_Controllers, tFloat4x4 offset, cBase_Spell c_Player_Fireball);
	void Draw_World(int nScene_Id, tScene_Objects* t_Object_List, bool *bChange_Scene, bool *bMove_Bullet, cHead_Mount c_Head_Mount, tFloat4x4 offset, double timer);
	particle* get_particle_array();
	void set_particle_array(particle* p_arr);
};
