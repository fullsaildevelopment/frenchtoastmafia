/************************************************************************
* Filename:  		Scene_Manager.cpp
* Date:      		24/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Managing system to handle all objects within a scene and related task.
*************************************************************************/
#include "Scene_Manager.h"

cScene_Manager::cScene_Manager()
{
}

cScene_Manager::~cScene_Manager()
{
}

tScene_Objects cScene_Manager::Get_Personal_Scene()
{
	tScene_Objects tScene;

	tScene.nObject_Count = 2;

	// Left Hand - 0
	{
		// World Position
		XMFLOAT4X4 temp;

		XMMATRIX tempMatrix = XMMatrixIdentity();

		//tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.1, 0.1, -0.1));

		//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.1, 0.1, 0.1), tempMatrix);

		XMStoreFloat4x4(&temp, tempMatrix);

		tScene.fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tLeft_Hand = cBinary_Read.Read_Mesh("left_hand_mesh.bin");

		for (int i = 0; i < tLeft_Hand.nVertex_Count; i++)
		{
			tScene.tMesh_Data[0].tVerts.push_back(tLeft_Hand.tVerts[i]);
		}

		tScene.tMesh_Data[0].nVertex_Count = tLeft_Hand.nVertex_Count;


		for (int i = 0; i < tLeft_Hand.nIndex_Count; i++)
		{
			tScene.tMesh_Data[0].nIndicies.push_back(tLeft_Hand.nIndicies[i]);
		}
		tScene.tMesh_Data[0].nIndex_Count = tLeft_Hand.nIndex_Count;

		// Material
		tScene.tMaterials_Data[0] = cBinary_Read.Read_Material("left_hand_material.bin");
	}

	// Right Hand - 1
	{
		// World Position
		XMFLOAT4X4 temp;

		XMMATRIX tempMatrix = XMMatrixIdentity();

		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.1, 0.1, -0.1));

		XMStoreFloat4x4(&temp, tempMatrix);

		tScene.fWorld_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(temp);


		// Mesh
		tMesh tLeft_Hand = cBinary_Read.Read_Mesh("right_hand_mesh.bin");

		for (int i = 0; i < tLeft_Hand.nVertex_Count; i++)
		{
			tScene.tMesh_Data[1].tVerts.push_back(tLeft_Hand.tVerts[i]);
		}

		tScene.tMesh_Data[1].nVertex_Count = tLeft_Hand.nVertex_Count;


		for (int i = 0; i < tLeft_Hand.nIndex_Count; i++)
		{
			tScene.tMesh_Data[1].nIndicies.push_back(tLeft_Hand.nIndicies[i]);
		}
		tScene.tMesh_Data[1].nIndex_Count = tLeft_Hand.nIndex_Count;

		// Material
		tScene.tMaterials_Data[1] = cBinary_Read.Read_Material("right_hand_material.bin");
	}

	return tScene;
}

tScene_Objects cScene_Manager::Get_World_Scene(int nScene_Id)
{
	tScene_Objects tScene;
	// SCREEN
	if (nScene_Id < 2 || nScene_Id == 3)
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

		XMFLOAT4X4 temp;

		XMMATRIX tempMatrix = XMMatrixIdentity();

		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, 0, -3.0));
		//tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, 0, -12.234));

		XMStoreFloat4x4(&temp, tempMatrix);

		tScene.fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);

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
			test_screen[i].fPosition.fZ *= -1;
		}

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
			tScene.szSRV_File_Path = "1.dds";
		else if (nScene_Id == 1)
			tScene.szSRV_File_Path = "2.dds";
		else if (nScene_Id > 2)
			tScene.szSRV_File_Path = "3.dds";


		return tScene;
	}
	// GAME
	else
	{
		tScene.nObject_Count = 7;

		// Battle Mage - 0
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(5, -3, 0), tempMatrix);
			tempMatrix = XMMatrixMultiply(XMMatrixRotationY(180), tempMatrix);
			//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.9, 0.9, 0.9), tempMatrix);


			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);
			tScene.bIs_Animated[0] = true;
			tMesh_Skinned tMage = cBinary_Read.Read_Mesh_Skinned("mesh.bin");

			for (int i = 0; i < tMage.nVertex_Count; i++)
			{
				//tMage.tVerts[i].fPosition.fZ *= -1;
				//tMage.tVerts[i].fNormal.fZ *= -1;
			}

			for (int i = 0; i < tMage.nVertex_Count; i++)
			{
				tScene.tMesh_Skinned_Data[0].tVerts.push_back(tMage.tVerts[i]);
			}

			tScene.tMesh_Skinned_Data[0].nVertex_Count = tMage.nVertex_Count;


			for (int i = 0; i < tMage.nIndex_Count; i++)
			{
				tScene.tMesh_Skinned_Data[0].nIndicies.push_back(tMage.nIndicies[i]);
			}
			tScene.tMesh_Skinned_Data[0].nIndex_Count = tMage.nIndex_Count;

			tScene.tMaterials_Data[0] = cBinary_Read.Read_Material("material.bin");
			tScene.tAnim_Clip[0] = cBinary_Read.Read_Skeleton("skeleton.bin");
			tScene.tAnim_Data[0] = Create_Inverse_Bind_Pose(tScene.tAnim_Clip[0].tKeyFrames[0]);
		}
		// Battle Mage

		// Arena - 1
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

			tScene.tMaterials_Data[1] = cBinary_Read.Read_Material("arenaMat.bin");
		}
		// Arena
		
		// Dragon - 2
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			//tempMatrix = XMMatrixMultiply(XMMatrixRotationX(3.14 / 3), tempMatrix);
			//tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixRotationY(3.14 / 2));

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-30, 0, 0));

			tempMatrix = XMMatrixMultiply(XMMatrixRotationY(-3.14/15), tempMatrix);

			//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.1, 0.1, 0.1), tempMatrix);


			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tDragon = cBinary_Read.Read_Mesh("DarkDragon3Mesh.bin");

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				tDragon.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				tScene.tMesh_Data[2].tVerts.push_back(tDragon.tVerts[i]);
			}

			tScene.tMesh_Data[2].nVertex_Count = tDragon.nVertex_Count;


			for (int i = 0; i < tDragon.nIndex_Count; i++)
			{
				tScene.tMesh_Data[2].nIndicies.push_back(tDragon.nIndicies[i]);
			}
			tScene.tMesh_Data[2].nIndex_Count = tDragon.nIndex_Count;

			tScene.tMaterials_Data[2] = cBinary_Read.Read_Material("DarkDragon3Material.bin");
			tScene.tMaterials_Data[2].tMats[0].szDiffuse_File_Path = "Dragon.fbm\\DarkDragon_D.png";
		}
		// Dragon
		
		/*
		// Dragon - 2
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(350, -20, 0), tempMatrix);
			tempMatrix = XMMatrixMultiply(XMMatrixRotationY(180), tempMatrix);
			//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.9, 0.9, 0.9), tempMatrix);


			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(temp);
			tScene.bIs_Animated[2] = true;
			tMesh_Skinned tDragon = cBinary_Read.Read_Mesh_Skinned("DarkDragon3Skinned.bin");

			//for (int i = 0; i < tDragon.nVertex_Count; i++)
			//{
			//	//tDragon.tVerts[i].fPosition.fZ *= -1;
			//	//tDragon.tVerts[i].fNormal.fZ *= -1;
			//}

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				tScene.tMesh_Skinned_Data[2].tVerts.push_back(tDragon.tVerts[i]);
			}

			tScene.tMesh_Skinned_Data[2].nVertex_Count = tDragon.nVertex_Count;


			for (int i = 0; i < tDragon.nIndex_Count; i++)
			{
				tScene.tMesh_Skinned_Data[2].nIndicies.push_back(tDragon.nIndicies[i]);
			}
			tScene.tMesh_Skinned_Data[2].nIndex_Count = tDragon.nIndex_Count;

			tScene.tMaterials_Data[2] = cBinary_Read.Read_Material("DarkDragon3Material.bin");
			tScene.tMaterials_Data[2].tMats[0].szDiffuse_File_Path = "Dragon.fbm\\DarkDragon_D.png";

			tScene.tAnim_Clip[2] = cBinary_Read.Read_Skeleton("DarkDragon3Skeleton.bin");
			tScene.tAnim_Data[2] = Create_Inverse_Bind_Pose(tScene.tAnim_Clip[2].tKeyFrames[0]);
		}
		// Dragon
		*/

		// Fireball - 3
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(1, -8, 0), tempMatrix);

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene.tMesh_Data[3].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene.tMesh_Data[3].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene.tMesh_Data[3].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene.tMesh_Data[3].nIndex_Count = tFireball.nIndex_Count;

			tScene.tMaterials_Data[3] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene.tMaterials_Data[3].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Fireball

		// Bullet - 4
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.1, 0.1, -0.1));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[4] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene.tMesh_Data[4].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene.tMesh_Data[4].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene.tMesh_Data[4].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene.tMesh_Data[4].nIndex_Count = tFireball.nIndex_Count;

			tScene.tMaterials_Data[4] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene.tMaterials_Data[4].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Bullet

		// Snorlax - 5
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(-5, -3, 0), tempMatrix);
			tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.01, 0.01, 0.01), tempMatrix);

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("snorlax_mesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene.tMesh_Data[5].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene.tMesh_Data[5].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene.tMesh_Data[5].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene.tMesh_Data[5].nIndex_Count = tFireball.nIndex_Count;

			tScene.tMaterials_Data[5] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene.tMaterials_Data[5].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Snorlax

		// Red Dragon - 6
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, 589.0f, 589.0f));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene.fWorld_Matrix[6] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tRedDragon = cBinary_Read.Read_Mesh("redDragonMesh.bin");

			for (int i = 0; i < tRedDragon.nVertex_Count; i++)
			{
				tRedDragon.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tRedDragon.nVertex_Count; i++)
			{
				tScene.tMesh_Data[6].tVerts.push_back(tRedDragon.tVerts[i]);
			}

			tScene.tMesh_Data[6].nVertex_Count = tRedDragon.nVertex_Count;


			for (int i = 0; i < tRedDragon.nIndex_Count; i++)
			{
				tScene.tMesh_Data[6].nIndicies.push_back(tRedDragon.nIndicies[i]);
			}
			tScene.tMesh_Data[6].nIndex_Count = tRedDragon.nIndex_Count;

			tScene.tMaterials_Data[6] = cBinary_Read.Read_Material("redDragonMaterial.bin");
			tScene.tMaterials_Data[6].tMats[0].szDiffuse_File_Path = "RedDragon.fbm\\armored.png";
		}
		// Red Dragon
	}

	return tScene;
}
