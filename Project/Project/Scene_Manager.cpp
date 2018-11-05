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
		tScene.nObject_Count = 3;

		// GAME 1 with mage
		if (nScene_Id == 2)
		{
			// Battle Mage
			{
				XMFLOAT4X4 temp;
				
				XMMATRIX tempMatrix = XMMatrixIdentity();
				tempMatrix = XMMatrixMultiply(XMMatrixTranslation(2, -3, 0), tempMatrix);
				tempMatrix = XMMatrixMultiply(XMMatrixRotationY(3.14/2), tempMatrix);
				//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.9, 0.9, 0.9), tempMatrix);
				

				XMStoreFloat4x4(&temp, tempMatrix);

				tScene.fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);
				tMesh tMage = cBinary_Read.Read_Mesh("mesh.bin");

				for (int i = 0; i < tMage.nVertex_Count; i++)
				{
					tMage.tVerts[i].fPosition.fZ *= -1;
				}

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
				
				XMFLOAT4X4 temp;

				XMMATRIX tempMatrix = XMMatrixIdentity();

				tempMatrix = XMMatrixMultiply(XMMatrixTranslation(0, -3, 0), tempMatrix);
				//
				//tempMatrix = XMMatrixMultiply(XMMatrixRotationX(3.14 / 2), tempMatrix);

				//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.1, 0.1, 0.1), tempMatrix);


				XMStoreFloat4x4(&temp, tempMatrix);

				tScene.fWorld_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(temp);

				tMesh tArena = cBinary_Read.Read_Mesh("arena_3_mesh.bin");
				tScene.tMesh_Data[1].nIndex_Count = tArena.nIndex_Count;
				tScene.tMaterials_Data[1] = cBinary_Read.Read_Material("arena_3_material.bin");
				tMaterials tMat_Arena = cBinary_Read.Read_Material("arenaMat.bin");
				tScene.tMaterials_Data[1].tMats[0].tDiffuse = tMat_Arena.tMats[0].tDiffuse;
				tScene.tMaterials_Data[1].tMats[0].szDiffuse_File_Path = tMat_Arena.tMats[0].szDiffuse_File_Path;

				for (int i = 0; i < tArena.nVertex_Count; i++)
				{
					tArena.tVerts[i].fPosition.fZ *= -1;
				}
				
				for (int i = 0; i < tArena.nVertex_Count; i++)
				{
					tScene.tMesh_Data[1].tVerts.push_back(tArena.tVerts[i]);
				}

				tScene.tMesh_Data[1].nVertex_Count = tArena.nVertex_Count;
				
				for (int i = 0; i < tArena.nIndex_Count; i++)
				{
					tScene.tMesh_Data[1].nIndicies.push_back(tArena.nIndicies[i]);
				}
			}
			// Arena

			// Bullet
			{
				//XMFLOAT4X4 temp;
				//
				//XMMATRIX tempMatrix = XMMatrixIdentity();
				//
				//tempMatrix = XMMatrixMultiply(XMMatrixTranslation(0, 0, -10), tempMatrix);
				//
				//
				//XMStoreFloat4x4(&temp, tempMatrix);
				//
				//tScene.fWorld_Position[2] = { 0, 0, 1 };
				//tVertex *test_bullet = new tVertex[8];
				//for (unsigned int i = 0; i < 8; i++)
				//{
				//	test_bullet[i].fPosition.fX = 0.1f;
				//	test_bullet[i].fPosition.fY = 0.1f;
				//	test_bullet[i].fPosition.fZ = 0.1f;
				//	test_bullet[i].fPosition.fW = 0.1f;
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
				//
				////for (int i = 0; i < 8; i++)
				////{
				////	test_bullet[i].fPosition.fZ *= -1.0f;
				////}
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
				//XMFLOAT4X4 tmp;
				//XMStoreFloat4x4(&tmp, XMMatrixIdentity());
				//tScene.fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(tmp);
			}
			// Bullet

			// GRID
			{
				tScene.tMesh_Data[2].nVertex_Count = 44;
				tVertex *test_grid = new tVertex[tScene.tMesh_Data[2].nVertex_Count];
				int counter = 0;
				for (int j = 0; j < 2; j++)
				{
					for (int i = 0; i < 11; i++)
					{
						counter = 11 * j + i;
						test_grid[counter].fPosition.fX = ((float)i / 60) - 3.0f;
						test_grid[counter].fPosition.fY = 0;
						test_grid[counter].fPosition.fZ = (j == 0) ? -3.0f : 3.0f;
						test_grid[counter].fPosition.fW = 1;


						counter = 22 + (11 * j) + i;
						test_grid[counter].fPosition.fX = (j == 0) ? -3.0f : 3.0f;
						test_grid[counter].fPosition.fY = 0;
						test_grid[counter].fPosition.fZ = ((float)i / 60) - 3.0f;
						test_grid[counter].fPosition.fW = 1;
					}
				}
				
				for (int i = 0; i < tScene.tMesh_Data[2].nVertex_Count; i++)
				{
					tScene.tMesh_Data[2].tVerts.push_back(test_grid[i]);
				}

				tScene.tMesh_Data[2].nIndex_Count = 44;

				unsigned int test_grid_indicies[44];

					//for (int i = 0; i < 11; i++)
					//{
					//	test_grid[i];
					//}
					//for (int i = 0; i < 11; i++)
					//{
					//	test_grid[i + 11];
					//}
					//for (int i = 0; i < 11; i++)
					//{
					//	test_grid[22 + i];
					//}
					//for (int i = 0; i < 11; i++)
					//{
					//	test_grid[33 + i];
					//}

				for (int i = 0, j = 0; j < 11; i += 2, j++)
				{
					test_grid_indicies[i] = j;
					test_grid_indicies[i + 1] = j + 11;
					test_grid_indicies[i + 22] = j + 22;
					test_grid_indicies[i + 23] = j + 33;
				}
				//int ind_size = 0;
				//for (int i = 0; i < 11; i++)
				//{
				//	test_grid_indicies[ind_size] = i;
				//	ind_size++;
				//	test_grid_indicies[ind_size] = i + 11;
				//	ind_size++;
				//}
				//for (int i = 22; i < 33; i++)
				//{
				//	test_grid_indicies[ind_size] = i;
				//	ind_size++;
				//	test_grid_indicies[ind_size] = i + 11;
				//	ind_size++;
				//}

				for (int i = 0; i < tScene.tMesh_Data[2].nIndex_Count; i++)
				{
					tScene.tMesh_Data[2].nIndicies.push_back(test_grid_indicies[i]);
				}

				XMFLOAT4X4 tmp;
				XMStoreFloat4x4(&tmp, XMMatrixIdentity());
				tScene.fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(tmp);
			}
			// GRID
		}
		else
			tMesh  tPriest = cBinary_Read.Read_Mesh("PriestDeathMesh.bin");
		
		return tScene;
	}
}
