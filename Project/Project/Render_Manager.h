/************************************************************************
* Filename:  		Render_Manager.h
* Date:      		02/10/2018
* Mod. Date: 		12/12/2018
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

#include "PixelShader_Object.csh"
#include "PixelShader_Screen.csh"
#include "PixelShader_Spell.csh"
#include "dopeSoundSystem.h"

#include "Particle.h"
#include "basic_structs.h"
#include "Effects.h"
// Particle Stuff
#include "Particle_Pixel_Shader.csh"
#include "Particle_Vertex_Shader.csh"
// Particle Stuff

#include "AI.h"

#include "Math_Conversion.h"

#include "Base_Character.h"

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

	tFloat4 dragonTint;
	FLOAT blend[4];

	// Collision
	bool bCollided;
	tAABB tAABB_Bullet, tAABB_Dragon;

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;



	static size_t pp_vert_count;

	particle *line_vert;      // tVertex
	int line_vert_count = 0;
	int line_vert_count_D = 0;

	//Particle p;

	// Particle Stuff
	ComPtr<ID3D11Buffer> particle_Vertex_Buffer;
	ComPtr<ID3D11Buffer> particle_Index_Buffer;
	ComPtr<ID3D11PixelShader> particle_Pixel_Shader;
	ComPtr<ID3D11VertexShader> particle_Vertex_Shader;

	ComPtr<ID3D11Buffer> particle_Constant_Buffer;
	D3D11_MAPPED_SUBRESOURCE particle_Constant_Mapped_RS;

	D3D11_BUFFER_DESC particle_Const_Buff_Desc;
	D3D11_SUBRESOURCE_DATA particle_Const_Buff_Data;

	tConstantBuffer_VertexShader_Bullet tPart;

	ComPtr<ID3D11ShaderResourceView> particle_Shader_Resource_View;
	ComPtr<ID3D11SamplerState> particle_Sample_State;

	ComPtr<ID3D11BlendState> particle_Blend_State;

	D3D11_BUFFER_DESC particle_Vertex_Buffer_DESC;
	D3D11_SUBRESOURCE_DATA particle_Vertex_Buffer_DATA;
	D3D11_BUFFER_DESC particle_Index_Buffer_DESC;
	D3D11_SUBRESOURCE_DATA particle_Index_Buffer_DATA;
	D3D11_BLEND_DESC particle_Blend_DESC;
	D3D11_SAMPLER_DESC particle_Sample_State_DESC;

	D3D11_BUFFER_DESC particle_Vertex_Buffer_DESC_D;
	D3D11_SUBRESOURCE_DATA particle_Vertex_Buffer_DATA_D;

	//static std::array<tVertex, 100> preAlloc_particle;
	//static std::array<tVertex, 100> preAlloc_particle_D;

	FLOAT blend_Ratio[4];

	float random_color;
	float random_alpha;

	UINT quad_indexes[100];
	// Particle Stuff

	// Health Bar Stuff

	/*ComPtr<ID3D11ShaderResourceView> player_100_health;
	ComPtr<ID3D11ShaderResourceView> player_90_health;
	ComPtr<ID3D11ShaderResourceView> player_80_health;
	ComPtr<ID3D11ShaderResourceView> player_70_health;
	ComPtr<ID3D11ShaderResourceView> player_60_health;
	ComPtr<ID3D11ShaderResourceView> player_50_health;
	ComPtr<ID3D11ShaderResourceView> player_40_health;
	ComPtr<ID3D11ShaderResourceView> player_30_health;
	ComPtr<ID3D11ShaderResourceView> player_20_health;
	ComPtr<ID3D11ShaderResourceView> player_10_health;*/

	// Health Bar Stuff

public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup* c_Graphics_Setup);
	void Load_Data(int nScene_Id, tScene_Objects* tObject_List);
	void Unload(tScene_Objects* t_Object_List);
	void Draw_Personal(tScene_Objects* t_Object_List, cHead_Mount c_Head_Mount, cControllers c_Controllers, tFloat4x4 offset, bool *bMove_Spell_01, bool *bMove_Spell_02, bool *bSpell_Ready_01, bool *bSpell_Ready_02, cBase_Character player, tFloat4 tSwap_Id);
	void Draw_Spell(tScene_Objects* t_Object_List, cHead_Mount c_Head_Mount, tFloat4x4 offset, bool bDisplay_Spell_Book, bool bUse_Node, bool bNode_Order[]);
	void Draw_World(int nScene_Id, tScene_Objects* t_Object_List, bool *bChange_Scene, cHead_Mount c_Head_Mount, tFloat4x4 offset, double totalTime, AI* _AI, bool dragon_hit, double timeDelta, tFloat4x4 player_pos, tScene_Objects *tPersonal_Object_List, bool f_alive, tFloat4 spell_id);
	particle* get_particle_array();
	void set_particle_array(particle* p_arr);
	void keyboardInputs(tScene_Objects* tObject_List);

	void Debugging_AABB(tAABB obj, cHead_Mount c_Head_Mount, tFloat4x4 offset);

	void Draw_UI(tScene_Objects* t_Object_List, cHead_Mount c_Head_Mount, tFloat4x4 offset, tFloat4x4 drag_World_Matrix, cBase_Character dragon, cBase_Character player);
	void Texture_Swap(std::string fname, ComPtr<ID3D11ShaderResourceView> *srv);
};
