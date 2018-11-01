#include "Scene_Manager.h"



cScene_Manager::cScene_Manager()
{
}


cScene_Manager::~cScene_Manager()
{
}

tScene_Objects cScene_Manager::GetScene(int nScene_Id)
{
	tScene_Objects tScene;
	// SCREEN
	if (nScene_Id < 2 || nScene_Id > 3)
	{
		//tBinary_Screen tBS;
		//if (nScene_Id == 0)
		//	tBS = cBinary_Read.Read_Screen_Binary("intro.bin");
		//else if (nScene_Id == 1)
		//	tBS = cBinary_Read.Read_Screen_Binary("menu.bin");
		//else
		//	tBS = cBinary_Read.Read_Screen_Binary("replay.bin");
		//
		//
		//tScene.nObject_Count = tBS.nObject_Count;
		//tScene.fWorld_Position[0] = { 0,0,0 };
		//tScene.tMesh_Data[0] = tBS.tMes;
		//if (tBS.vs_check != 0)
		//	tScene.szVS_File_Path[0] = tBS.vs_name;
		//if (tBS.ps_check != 0)
		//	tScene.szPS_File_Path[0] = tBS.ps_name;
		//if (tBS.srv_check != 0)
		//	tScene.szSRV_File_Path[0] = tBS.srv_name;
		tScene.nObject_Count = 1;
		tScene.fWorld_Position[0] = { 0, 0, 15 };

		tVertex *test_screen = new tVertex[4];
		test_screen[0].fPosition.fX = -4.0f;// -20.0f;
		test_screen[0].fPosition.fY = 3.0f;//15.0f;
		test_screen[0].fPosition.fZ = 1.0f;

		test_screen[0].fTexture_Coordinate.fX = 0.0f;
		test_screen[0].fTexture_Coordinate.fY = 0.0f;

		test_screen[1].fPosition.fX = 4.0f;//20.0f;
		test_screen[1].fPosition.fY = 3.0f;//15.0f;
		test_screen[1].fPosition.fZ = 1.0f;

		test_screen[1].fTexture_Coordinate.fX = 1.0f;
		test_screen[1].fTexture_Coordinate.fY = 0.0f;

		test_screen[2].fPosition.fX = -4.0f;//-20.0f;
		test_screen[2].fPosition.fY = -3.0f;//-15.0f;
		test_screen[2].fPosition.fZ = 1.0f;

		test_screen[2].fTexture_Coordinate.fX = 0.0f;
		test_screen[2].fTexture_Coordinate.fY = 1.0f;

		test_screen[3].fPosition.fX = 4.0f;//20.0f;
		test_screen[3].fPosition.fY = -3.0f;//-15.0f;
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

		if (nScene_Id == 0)
			tScene.szSRV_File_Path[0] = "1.dds";
		else if (nScene_Id == 1)
			tScene.szSRV_File_Path[0] = "2.dds";
		else if (nScene_Id > 3)
			tScene.szSRV_File_Path[0] = "3.dds";


		return tScene;
	}
	// GAME
	else
	{
		tScene.nObject_Count = 2;

		// GAME 1 with mage
		if (nScene_Id == 2)
		{
			// Battle Mage
			{
				XMFLOAT4X4 temp;

				XMStoreFloat4x4(&temp, XMMatrixMultiply(XMMatrixIdentity(), XMMatrixTranslation(0, 0, 2.5)));

				tScene.fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);
				tMesh tMage = cBinary_Read.Read_Mesh("mesh.bin");

				/*for (int i = 0; i < tMage.nVertex_Count; i++)
				{
					tMage.tVerts[i].fTexture_Coordinate.fY = 1.0f - tMage.tVerts[i].fTexture_Coordinate.fY;
				}*/

				for (int i = 0; i < tMage.nVertex_Count; i++)
				{
					tScene.tMesh_Data[0].tVerts.push_back(tMage.tVerts[i]);
				}

				tScene.tMesh_Data[0].nVertex_Count = tMage.nVertex_Count;


				for (int i = 0; i < tMage.nIndex_Count; i++)
				{
					tScene.tMesh_Data[0].nIndicies.push_back(tMage.nIndicies[i]);
				}
				tScene.tMesh_Data[0].nIndex_Count = tMage.nIndex_Count;

				//XMStoreFloat4x4(&tScene.fWorld_Matrix[0], XMMatrixIdentity());

				tScene.tMaterials_Data[0] = cBinary_Read.Read_Material("material.bin");
				//tScene.tMaterials_Data[0].tMats[0].tNormal.fX = 1.0f;
			}
			// Battle Mage

			// Arena
			{
				
				//tScene.fWorld_Position[1] = { 0, 0,  };
				tMesh tArena = cBinary_Read.Read_Mesh("arenaMesh.bin");
				tScene.tMesh_Data[1].nIndex_Count = tArena.nIndex_Count;
				tScene.tMaterials_Data[1] = cBinary_Read.Read_Material("arenaMat.bin");
				
				for (int i = 0; i < tArena.nVertex_Count; i++)
				{
					tScene.tMesh_Data[1].tVerts.push_back(tArena.tVerts[i]);
				}
				tScene.tMesh_Data[1].nVertex_Count = tArena.nVertex_Count;
				
				for (int i = 0; i < tArena.nIndex_Count; i++)
				{
					tScene.tMesh_Data[1].nIndicies.push_back(tArena.nIndicies[i]);
				}
				XMMATRIX tempMat = XMMatrixIdentity();
				
				tempMat = XMMatrixMultiply(tempMat, XMMatrixScaling(0.05, 0.05, 0.05));
				tempMat = XMMatrixMultiply(tempMat, XMMatrixRotationX(-3.14 / 2));
				tempMat = XMMatrixMultiply(tempMat, XMMatrixTranslation(0, 0, -2.5));
				
				XMFLOAT4X4 tmp;
				XMStoreFloat4x4(&tmp, tempMat);

				tScene.fWorld_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(tmp);
			}
			// Arena

			// Bullet
			{
				//tScene.fWorld_Position[2] = { 0, 0, 1 };
				//tVertex *test_bullet = new tVertex[8];
				//for (unsigned int i = 0; i < 8; i++)
				//{
				//	test_bullet[i].fPosition.fX = 1.0f;
				//	test_bullet[i].fPosition.fY = 1.0f;
				//	test_bullet[i].fPosition.fZ = 1.0f;
				//	test_bullet[i].fPosition.fW = 1.0f;
				//
				//	if (i % 2 == 0)
				//		test_bullet[i].fPosition.fX *= -1.0f;
				//
				//	if (i == 2 || i == 3 || i == 6 || i == 7)
				//		test_bullet[i].fPosition.fY *= -1.0f;
				//
				//	if (i < 4)
				//		test_bullet[i].fPosition.fZ *= -1.0f;
				//}
				//
				//for (int i = 0; i < 8; i++)
				//{
				//	tScene.tMesh_Data[2].tVerts.push_back(test_bullet[i]);
				//}
				//
				//tScene.tMesh_Data[2].nVertex_Count = 8;
				//// INDEX BUFFER
				//
				//unsigned int test_bullet_indicies[36] =
				//{
				//	0,1,2,
				//	1,3,2,
				//	4,0,6,
				//	0,2,6,
				//	5,4,7,
				//	4,6,7,
				//	1,5,3,
				//	5,7,3,
				//	4,5,0,
				//	5,1,0,
				//	2,3,6,
				//	3,7,6
				//};
				//for (int i = 0; i < 36; i++)
				//{
				//	tScene.tMesh_Data[2].nIndicies.push_back(test_bullet_indicies[i]);
				//}
				//
				//tScene.tMesh_Data[2].nIndex_Count = 36;
				//
				//XMStoreFloat4x4(&tScene.fWorld_Matrix[2], XMMatrixIdentity());
			}
			// Bullet
		}
		else
			tMesh  tPriest = cBinary_Read.Read_Mesh("PriestDeathMesh.bin");
		
		return tScene;
	}
}
