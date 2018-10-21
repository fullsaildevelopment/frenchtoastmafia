#include "Scene_Manager.h"



cScene_Manager::cScene_Manager()
{
}


cScene_Manager::~cScene_Manager()
{
}

void cScene_Manager::SetDevice(CComPtr<ID3D11Device> _d3dDevice)
{
	d3dDevice = _d3dDevice;
}

tScene_Objects cScene_Manager::GetIntro()
{
	tScene_Objects tIntro;

	tIntro.fWorld_Position[0] = { 0,0,0 };

	CComPtr<ID3D11Buffer> d3d_game_screen_vertex_buffer;
	CComPtr<ID3D11Buffer> d3d_game_screen_index_buffer;
	CComPtr<ID3D11ShaderResourceView> intro_srv;

	D3D11_BUFFER_DESC d3dBuffer_Desc;
	D3D11_SUBRESOURCE_DATA d3dSRD;

	// VERTEX BUFFER
	tVertex *test_screen = new tVertex[4];
	test_screen[0].fPosition.fX = -20.0f;
	test_screen[0].fPosition.fY = 15.0f;
	test_screen[0].fPosition.fZ = 1.0f;

	test_screen[0].fTexture_Coordinate.fX = 0.0f;
	test_screen[0].fTexture_Coordinate.fY = 0.0f;

	test_screen[1].fPosition.fX = 20.0f;
	test_screen[1].fPosition.fY = 15.0f;
	test_screen[1].fPosition.fZ = 1.0f;

	test_screen[1].fTexture_Coordinate.fX = 1.0f;
	test_screen[1].fTexture_Coordinate.fY = 0.0f;

	test_screen[2].fPosition.fX = -20.0f;
	test_screen[2].fPosition.fY = -15.0f;
	test_screen[2].fPosition.fZ = 1.0f;

	test_screen[2].fTexture_Coordinate.fX = 0.0f;
	test_screen[2].fTexture_Coordinate.fY = 1.0f;

	test_screen[3].fPosition.fX = 20.0f;
	test_screen[3].fPosition.fY = -15.0f;
	test_screen[3].fPosition.fZ = 1.0f;

	test_screen[3].fTexture_Coordinate.fX = 1.0f;
	test_screen[3].fTexture_Coordinate.fY = 1.0f;

	ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3dBuffer_Desc.ByteWidth = sizeof(tVertex) * 4;
	d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
	d3dBuffer_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBuffer_Desc.CPUAccessFlags = NULL;
	d3dBuffer_Desc.MiscFlags = 0;
	d3dBuffer_Desc.StructureByteStride = 0;

	ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dSRD.pSysMem = test_screen;
	d3dSRD.SysMemPitch = 0;
	d3dSRD.SysMemSlicePitch = 0;

	HRESULT hr = d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_game_screen_vertex_buffer);

	// INDEX BUFFER

	unsigned int test_screen_indicies[6] =
	{
		0,1,2,
		1,3,2
	};

	ZeroMemory(&d3dBuffer_Desc, sizeof(D3D11_BUFFER_DESC));
	d3dBuffer_Desc.ByteWidth = sizeof(unsigned int) * 6;
	d3dBuffer_Desc.Usage = D3D11_USAGE_IMMUTABLE;
	d3dBuffer_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	d3dBuffer_Desc.CPUAccessFlags = NULL;
	d3dBuffer_Desc.MiscFlags = 0;
	d3dBuffer_Desc.StructureByteStride = 0;

	ZeroMemory(&d3dSRD, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dSRD.pSysMem = test_screen_indicies;
	d3dSRD.SysMemPitch = 0;
	d3dSRD.SysMemSlicePitch = 0;

	d3dDevice->CreateBuffer(&d3dBuffer_Desc, &d3dSRD, &d3d_game_screen_index_buffer.p);

	// SRV
	CreateDDSTextureFromFile(d3dDevice, L"1.dds", nullptr, &intro_srv.p);

	tIntro.d3d_Vertex_Buffers[0] = d3d_game_screen_vertex_buffer;
	tIntro.d3d_Index_Buffers[0] = d3d_game_screen_index_buffer;
	tIntro.d3d_SRV[0] = intro_srv;

	return tIntro;
}
