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

tScene_Objects cScene_Manager::GetScene(int nScene_Id)
{

	tScene_Objects tScene;

	tScene.nObject_Count = 1;
	tScene.fWorld_Position[0] = { 0,0,0 };



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

	for (int i = 0; i < 4; i++)
	{
		tScene.tMesh_Data[0].tVerts.push_back(test_screen[i]);
	}

	tScene.tMesh_Data[0].nVertex_Count = 4;

	// INDEX BUFFER

	unsigned int test_screen_indicies[6] =
	{
		0,1,2,
		1,3,2
	};

	for (int i = 0; i < 6; i++)
	{
		tScene.tMesh_Data[0].nIndicies.push_back(test_screen_indicies[i]);
	}
	tScene.tMesh_Data[0].nIndex_Count = 6;

	tScene.szSRV_File_Path[0] = "1.dds";

	return tScene;
}
