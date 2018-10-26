#pragma once

#include "Graphic_Setup.h"
#include "renderer_structs.h"
#include "XTime.h"


class cRender_Manager
{
private:
	// WVPC
	CComPtr<ID3D11Buffer> d3d_Constant_Buffer_WVPC;
	D3D11_BUFFER_DESC d3d_Constant_Buffer_Desc;
	tConstantBuffer_VertexShader_WVPC tWVPC;
	XMFLOAT4X4 fCamera_Matrix;
	XMFLOAT4X4 fCamera_Origin;

	// TIME
	XTime cTime;
public:
	cRender_Manager();
	~cRender_Manager();

	void Initialize(cGraphics_Setup *c_Graphics_Setup);
//	tScene_Objects GetScene(int nScene_Id);
	void Load();
	void Unload();
	void Draw();
	void DrawToTexture();
};

