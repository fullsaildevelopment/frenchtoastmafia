/************************************************************************
* Filename:  		Scene_Manager.cpp
* Date:      		24/10/2018
* Mod. Date: 		12/12/2018
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

tScene_Objects* cScene_Manager::Get_Personal_Scene()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 14;

	// Left Hand Idle - 0
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("left_hand_idle_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("left_hand_material.bin");
		tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
	}
	// Left Hand Idle

	// Left Hand Select - 1
	{
		int obj_id = 1;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("left_hand_select_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("left_hand_material.bin");
	}
	// Left Hand Select

	// Left Hand Spell - 2
	{
		int obj_id = 2;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("left_hand_spell_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("left_hand_material.bin");
	}
	// Left Hand Spell

	// Left Hand Shield - 3
	{
		int obj_id = 3;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("left_hand_shield_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("left_hand_material.bin");
	}
	// Left Hand Shield

	// Right Hand Idle - 4
	{
		int obj_id = 4;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("right_hand_idle_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("right_hand_material.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
	}
	// Right Hand Idle

	// Right Hand Select - 5
	{
		int obj_id = 5;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("right_hand_select_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("right_hand_material.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
	}
	// Right Hand Select

	// Right Hand Spell - 6
	{
		int obj_id = 6;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("right_hand_spell_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("right_hand_material.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
	}
	// Right Hand Spell

	// Right Hand Shield - 7
	{
		int obj_id = 7;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tHand = cBinary_Read.Read_Mesh("right_hand_shield_mesh.bin");
		for (int i = 0; i < tHand.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tHand.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tHand.nVertex_Count;

		//for (int i = 0; i < tHand.nIndex_Count; i++)
		//{
		//	tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
		//}
		for (int i = 0; i < tHand.nIndex_Count; i++)
		{
			if (i % 3 == 0)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i]);
			}
			if (i % 3 == 1)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i + 1]);
			}
			if (i % 3 == 2)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(tHand.nIndicies[i - 1]);
			}
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tHand.nIndex_Count;

		// Material
		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("right_hand_material.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
	}
	// Right Hand Shield

	// Left Fireball - 8
	{
		int obj_id = 8;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");
		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tFireball.tVerts[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("fireballMaterial.bin");
		tScene->tMaterials_Data[obj_id].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
	}
	// Left Fireball

	// Left Icebolt - 9
	{
		int obj_id = 9;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");
		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tFireball.tVerts[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("fireballMaterial.bin");
		tScene->tMaterials_Data[obj_id].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
	}
	// Left Icebolt

	// Left Shield - 10
	{
		int obj_id = 10;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("shield_spell_mesh.bin");

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("shield_spell_material.bin");
	}
	// Left Shield

	// Right Fireball - 11
	{
		int obj_id = 11;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");
		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tFireball.tVerts[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("fireballMaterial.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
		tScene->tMaterials_Data[obj_id].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
	}
	// Right Fireball

	// Right Icebolt - 12
	{
		int obj_id = 12;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");
		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tFireball.tVerts[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("fireballMaterial.bin");
		//tScene->szSRV_File_Path[obj_id] = "Hand_Life_100.dds";
		tScene->tMaterials_Data[obj_id].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
	}
	// Right Icebolt

	// Right Shield - 13
	{
		int obj_id = 13;
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		// Mesh
		tMesh tFireball = cBinary_Read.Read_Mesh("shield_spell_mesh.bin");

		for (int i = 0; i < tFireball.nVertex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(tFireball.tVerts[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = tFireball.nVertex_Count;


		for (int i = 0; i < tFireball.nIndex_Count; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(tFireball.nIndicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = tFireball.nIndex_Count;

		tScene->tMaterials_Data[obj_id] = cBinary_Read.Read_Material("shield_spell_material.bin");
	}
	// Right Shield
	return tScene;
}

tScene_Objects* cScene_Manager::Get_World_Scene(int nScene_Id)
{
	tScene_Objects* tScene = new tScene_Objects;
	// SCREEN
	if (nScene_Id < 2 || nScene_Id == 3)
	{
		tScene->nObject_Count = 1;
		tScene->fWorld_Position[0] = { 0, 0, 15 };

		XMFLOAT4X4 temp;

		XMMATRIX tempMatrix = XMMatrixIdentity();

		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, 1, -3.0));

		XMStoreFloat4x4(&temp, tempMatrix);

		tScene->fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *test_screen = new tVertex[4];
		test_screen[0].fPosition.fX = -2.4f;
		test_screen[0].fPosition.fY = 1.8f;
		test_screen[0].fPosition.fZ = 1.0f;

		test_screen[0].fTexture_Coordinate.fX = 0.0f;
		test_screen[0].fTexture_Coordinate.fY = 0.0f;

		test_screen[1].fPosition.fX = 2.4f;
		test_screen[1].fPosition.fY = 1.8f;
		test_screen[1].fPosition.fZ = 1.0f;

		test_screen[1].fTexture_Coordinate.fX = 1.0f;
		test_screen[1].fTexture_Coordinate.fY = 0.0f;

		test_screen[2].fPosition.fX = -2.4f;
		test_screen[2].fPosition.fY = -1.8f;
		test_screen[2].fPosition.fZ = 1.0f;

		test_screen[2].fTexture_Coordinate.fX = 0.0f;
		test_screen[2].fTexture_Coordinate.fY = 1.0f;

		test_screen[3].fPosition.fX = 2.4f;
		test_screen[3].fPosition.fY = -1.8f;
		test_screen[3].fPosition.fZ = 1.0f;

		test_screen[3].fTexture_Coordinate.fX = 1.0f;
		test_screen[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			test_screen[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[0].tVerts.push_back(test_screen[i]);
		}

		tScene->tMesh_Data[0].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int test_screen_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[0].nIndicies.push_back(test_screen_indicies[i]);
		}
		tScene->tMesh_Data[0].nIndex_Count = 6;

		if (nScene_Id == 0)
			tScene->szSRV_File_Path[0] = "1.dds";
		else if (nScene_Id == 1)
			tScene->szSRV_File_Path[0] = "2.dds";
		else if (nScene_Id == 3)
			tScene->szSRV_File_Path[0] = "3.dds";
		else if (nScene_Id == 4)
			tScene->szSRV_File_Path[0] = "4.dds";


		return tScene;
	}
	// GAME
	else
	{
		tScene->nObject_Count = 8;

		// Battle Mage - 0
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(5, -3, 0), tempMatrix);
			tempMatrix = XMMatrixMultiply(XMMatrixRotationY(180), tempMatrix);


			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[0] = XMFLOAT4x4_to_tFloat4x4(temp);
			tScene->bIs_Animated[0] = true;
			tMesh_Skinned tMage = cBinary_Read.Read_Mesh_Skinned("mesh.bin");

			for (int i = 0; i < tMage.nVertex_Count; i++)
			{
				tScene->tMesh_Skinned_Data[0].tVerts.push_back(tMage.tVerts[i]);
			}

			tScene->tMesh_Skinned_Data[0].nVertex_Count = tMage.nVertex_Count;


			for (int i = 0; i < tMage.nIndex_Count; i++)
			{
				tScene->tMesh_Skinned_Data[0].nIndicies.push_back(tMage.nIndicies[i]);
			}
			tScene->tMesh_Skinned_Data[0].nIndex_Count = tMage.nIndex_Count;

			tScene->tMaterials_Data[0] = cBinary_Read.Read_Material("material.bin");
			tScene->tAnim_Clip[0][0] = cBinary_Read.Read_Skeleton("skeleton.bin");
			tScene->tAnim_Data[0] = Create_Inverse_Bind_Pose(tScene->tAnim_Clip[0][0].tKeyFrames[0]);
		}
		// Battle Mage

		// Arena - 1
		{

			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(0, -3, 0), tempMatrix);

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[1] = XMFLOAT4x4_to_tFloat4x4(temp);

			tMesh tArena = cBinary_Read.Read_Mesh("arena_3_mesh.bin");
			tScene->tMesh_Data[1].nIndex_Count = tArena.nIndex_Count;

			for (int i = 0; i < tArena.nVertex_Count; i++)
			{
				tArena.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tArena.nVertex_Count; i++)
			{
				tScene->tMesh_Data[1].tVerts.push_back(tArena.tVerts[i]);
			}

			tScene->tMesh_Data[1].nVertex_Count = tArena.nVertex_Count;

			for (int i = 0; i < tArena.nIndex_Count; i++)
			{
				tScene->tMesh_Data[1].nIndicies.push_back(tArena.nIndicies[i]);
			}

			tScene->tMaterials_Data[1] = cBinary_Read.Read_Material("arenaMat.bin");
		}
		// Arena
		/*
		// Dragon - 2
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			//tempMatrix = XMMatrixMultiply(XMMatrixRotationZ(3.14), tempMatrix);
			//
			//tempMatrix = XMMatrixMultiply(XMMatrixRotationX(-3.14 / 2), tempMatrix);
			//
			//tempMatrix = XMMatrixMultiply(XMMatrixRotationZ(-3.14/2), tempMatrix);
			//
			//tempMatrix = XMMatrixMultiply(XMMatrixRotationX(3.14 / 5), tempMatrix);

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-200, 0, 0));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tDragon = cBinary_Read.Read_Mesh("dragonMesh.bin");

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				float oldY = tDragon.tVerts[i].fPosition.fY;
				float oldZ = tDragon.tVerts[i].fPosition.fZ;

				tDragon.tVerts[i].fPosition.fY = oldZ;
				tDragon.tVerts[i].fPosition.fZ = oldY;

				tDragon.tVerts[i].fPosition.fZ *= -1;

			}

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				tScene->tMesh_Data[2].tVerts.push_back(tDragon.tVerts[i]);
			}

			tScene->tMesh_Data[2].nVertex_Count = tDragon.nVertex_Count;


			for (int i = 0; i < tDragon.nIndex_Count; i++)
			{
				tScene->tMesh_Data[2].nIndicies.push_back(tDragon.nIndicies[i]);
			}
			tScene->tMesh_Data[2].nIndex_Count = tDragon.nIndex_Count;

			tScene->tMaterials_Data[2] = cBinary_Read.Read_Material("dragonMaterial.bin");
			tScene->tMaterials_Data[2].tMats[0].szDiffuse_File_Path = "Dragon.fbm\\DarkDragon_D.png";
		}
		// Dragon
		*/

		// Anim Test - 2
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			//tempMatrix = XMMatrixMultiply(XMMatrixTranslation(-40, 8, 0), tempMatrix);
			//tempMatrix = XMMatrixMultiply(XMMatrixRotationY(3.14 / 8), tempMatrix);
			//tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.9, 0.9, 0.9), tempMatrix);

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-150, 0, 0));


			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[2] = XMFLOAT4x4_to_tFloat4x4(temp);
			tScene->bIs_Animated[2] = true;
			tMesh_Skinned tDragon = cBinary_Read.Read_Mesh_Skinned("Dragon_Flying2Skinned.bin");

			//for (int i = 0; i < tDragon.nVertex_Count; i++)
			//{
			//	//tDragon.tVerts[i].fPosition.fZ *= -1;
			//	//tDragon.tVerts[i].fNormal.fZ *= -1;
			//}

			for (int i = 0; i < tDragon.nVertex_Count; i++)
			{
				tScene->tMesh_Skinned_Data[2].tVerts.push_back(tDragon.tVerts[i]);
			}

			tScene->tMesh_Skinned_Data[2].nVertex_Count = tDragon.nVertex_Count;


			for (int i = 0; i < tDragon.nIndex_Count; i++)
			{
				if (i % 3 == 0)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tDragon.nIndicies[i]);
				}
				if (i % 3 == 1)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tDragon.nIndicies[i + 1]);
				}
				if (i % 3 == 2)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tDragon.nIndicies[i - 1]);
				}
			}
			tScene->tMesh_Skinned_Data[2].nIndex_Count = tDragon.nIndex_Count;

			tScene->tMaterials_Data[2] = cBinary_Read.Read_Material("Dragon_Flying2Material.bin");
			tScene->tMaterials_Data[2].tMats[0].szDiffuse_File_Path = "Dragon.fbm\\DarkDragon_D.png";

			tScene->tAnim_Clip[2][0] = cBinary_Read.Read_Skeleton("Dragon_Flying2Skeleton.bin");
			tScene->tAnim_Clip[2][1] = cBinary_Read.Read_Skeleton("Dragon_GetHit2Skeleton.bin");
			tScene->tAnim_Data[2] = Create_Inverse_Bind_Pose(tScene->tAnim_Clip[2][0].tKeyFrames[0]);

			tScene->currAnim[2] = 0;
		}
		// Anim Test

		// Fireball - 3
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, 500, 0));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[3] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;

				tFireball.tVerts[i].fPosition.fX = tFireball.tVerts[i].fPosition.fX * 5;
				tFireball.tVerts[i].fPosition.fY = tFireball.tVerts[i].fPosition.fY * 5;
				tFireball.tVerts[i].fPosition.fZ = tFireball.tVerts[i].fPosition.fZ * 5;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene->tMesh_Data[3].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene->tMesh_Data[3].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene->tMesh_Data[3].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene->tMesh_Data[3].nIndex_Count = tFireball.nIndex_Count;

			tScene->tMaterials_Data[3] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene->tMaterials_Data[3].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Fireball

		// Bullet - 4
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.1, -10.1, -0.1));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[4] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("fireballMesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene->tMesh_Data[4].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene->tMesh_Data[4].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene->tMesh_Data[4].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene->tMesh_Data[4].nIndex_Count = tFireball.nIndex_Count;

			tScene->tMaterials_Data[4] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene->tMaterials_Data[4].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Bullet

		// Snorlax - 5
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();

			tempMatrix = XMMatrixMultiply(XMMatrixTranslation(-5, -3, 0), tempMatrix);
			tempMatrix = XMMatrixMultiply(XMMatrixScaling(0.01, 0.01, 0.01), tempMatrix);

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[5] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tFireball = cBinary_Read.Read_Mesh("snorlax_mesh.bin");

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tFireball.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tFireball.nVertex_Count; i++)
			{
				tScene->tMesh_Data[5].tVerts.push_back(tFireball.tVerts[i]);
			}

			tScene->tMesh_Data[5].nVertex_Count = tFireball.nVertex_Count;


			for (int i = 0; i < tFireball.nIndex_Count; i++)
			{
				tScene->tMesh_Data[5].nIndicies.push_back(tFireball.nIndicies[i]);
			}
			tScene->tMesh_Data[5].nIndex_Count = tFireball.nIndex_Count;

			tScene->tMaterials_Data[5] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene->tMaterials_Data[5].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Snorlax

		// Red Dragon - 6
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, 589.0f, 589.0f));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[6] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tRedDragon = cBinary_Read.Read_Mesh("redDragonMesh.bin");

			for (int i = 0; i < tRedDragon.nVertex_Count; i++)
			{
				tRedDragon.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tRedDragon.nVertex_Count; i++)
			{
				tScene->tMesh_Data[6].tVerts.push_back(tRedDragon.tVerts[i]);
			}

			tScene->tMesh_Data[6].nVertex_Count = tRedDragon.nVertex_Count;


			for (int i = 0; i < tRedDragon.nIndex_Count; i++)
			{
				tScene->tMesh_Data[6].nIndicies.push_back(tRedDragon.nIndicies[i]);
			}
			tScene->tMesh_Data[6].nIndex_Count = tRedDragon.nIndex_Count;

			tScene->tMaterials_Data[6] = cBinary_Read.Read_Material("redDragonMaterial.bin");
			tScene->tMaterials_Data[6].tMats[0].szDiffuse_File_Path = "RedDragon.fbm\\armored.png";
		}
		// Red Dragon

		// Marker - 7
		{
			XMFLOAT4X4 temp;

			XMMATRIX tempMatrix = XMMatrixIdentity();
			tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-2.0f, 0.0f, 0.0f));

			XMStoreFloat4x4(&temp, tempMatrix);

			tScene->fWorld_Matrix[7] = XMFLOAT4x4_to_tFloat4x4(temp);
			tMesh tAlert = cBinary_Read.Read_Mesh("alertMesh.bin");

			for (int i = 0; i < tAlert.nVertex_Count; i++)
			{
				tAlert.tVerts[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < tAlert.nVertex_Count; i++)
			{
				tScene->tMesh_Data[7].tVerts.push_back(tAlert.tVerts[i]);
			}

			tScene->tMesh_Data[7].nVertex_Count = tAlert.nVertex_Count;


			for (int i = 0; i < tAlert.nIndex_Count; i++)
			{
				tScene->tMesh_Data[7].nIndicies.push_back(tAlert.nIndicies[i]);
			}
			for (int i = 0; i < tAlert.nIndex_Count; i++)
			{
				if (i % 3 == 0)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tAlert.nIndicies[i + 2]);
				}
				if (i % 3 == 1)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tAlert.nIndicies[i]);
				}
				if (i % 3 == 2)
				{
					tScene->tMesh_Skinned_Data[2].nIndicies.push_back(tAlert.nIndicies[i - 2]);
				}
			}
			tScene->tMesh_Data[7].nIndex_Count = tAlert.nIndex_Count;

			tScene->tMaterials_Data[7] = cBinary_Read.Read_Material("fireballMaterial.bin");
			tScene->tMaterials_Data[7].tMats[0].szDiffuse_File_Path = "Fireball.fbm\\Fireball_D.png";
		}
		// Marker

	}


	return tScene;
}

tScene_Objects* cScene_Manager::Get_Spell_Book()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 5;

	// Background
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, -0.1f, 0.0f));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.375f;
		spells[0].fPosition.fY = 0.375f;
		spells[0].fPosition.fZ = 1.0f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.375f;
		spells[1].fPosition.fY = 0.375;
		spells[1].fPosition.fZ = 1.0f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.375f;
		spells[2].fPosition.fY = -0.375f;
		spells[2].fPosition.fZ = 1.0f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.375f;
		spells[3].fPosition.fY = -0.375f;
		spells[3].fPosition.fZ = 1.0f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "spellbook.dds";
	}
	// Background

	// Spells
	{
		for (int obj_id = 1; obj_id < tScene->nObject_Count; obj_id++)
		{

			// World Position
			XMFLOAT4X4 temp;
			XMMATRIX tempMatrix = XMMatrixIdentity();
			switch (obj_id)
			{
			case 1:
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.175, 0.075, 0));
				break;
			case 2:
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.175, 0.075, 0));
				break;
			case 3:
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.175, -0.2, 0));
				break;
			case 4:
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.175, -0.2, 0));
				break;
			default:
				break;
			}
			XMStoreFloat4x4(&temp, tempMatrix);
			tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

			tVertex *spells = new tVertex[4];
			spells[0].fPosition.fX = -0.0625f;
			spells[0].fPosition.fY = 0.0625f;
			spells[0].fPosition.fZ = 0.75f;

			spells[0].fTexture_Coordinate.fX = 0.0f;
			spells[0].fTexture_Coordinate.fY = 0.0f;

			spells[1].fPosition.fX = 0.0625f;
			spells[1].fPosition.fY = 0.0625f;
			spells[1].fPosition.fZ = 0.75f;

			spells[1].fTexture_Coordinate.fX = 1.0f;
			spells[1].fTexture_Coordinate.fY = 0.0f;

			spells[2].fPosition.fX = -0.0625f;
			spells[2].fPosition.fY = -0.0625f;
			spells[2].fPosition.fZ = 0.75f;

			spells[2].fTexture_Coordinate.fX = 0.0f;
			spells[2].fTexture_Coordinate.fY = 1.0f;

			spells[3].fPosition.fX = 0.0625f;
			spells[3].fPosition.fY = -0.0625f;
			spells[3].fPosition.fZ = 0.75f;

			spells[3].fTexture_Coordinate.fX = 1.0f;
			spells[3].fTexture_Coordinate.fY = 1.0f;

			for (int i = 0; i < 4; i++)
			{
				spells[i].fPosition.fZ *= -1;
			}

			for (int i = 0; i < 4; i++)
			{
				tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
			}

			tScene->tMesh_Data[obj_id].nVertex_Count = 4;

			// INDEX BUFFER

			unsigned int spells_indicies[6] =
			{
				0,1,2,
				1,3,2
			};

			for (int i = 0; i < 6; i++)
			{
				tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
			}
			tScene->tMesh_Data[obj_id].nIndex_Count = 6;

			switch (obj_id)
			{
			case 1:
				tScene->szSRV_File_Path[obj_id] = "fireball.dds";
				break;
			case 2:
				tScene->szSRV_File_Path[obj_id] = "icebolt.dds";
				break;
			case 3:
				tScene->szSRV_File_Path[obj_id] = "shield.dds";
				break;
			case 4:
			default:
				tScene->szSRV_File_Path[obj_id] = "cancel.dds";
				break;
			}
		}
	}
	// Spells

	return tScene;
}

tScene_Objects * cScene_Manager::Get_Spell_Node_Fireball()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 4;

	// Background
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, -0.1f, 0.0f));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.375f;
		spells[0].fPosition.fY = 0.375f;
		spells[0].fPosition.fZ = 1.0f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.375f;
		spells[1].fPosition.fY = 0.375;
		spells[1].fPosition.fZ = 1.0f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.375f;
		spells[2].fPosition.fY = -0.375f;
		spells[2].fPosition.fZ = 1.0f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.375f;
		spells[3].fPosition.fY = -0.375f;
		spells[3].fPosition.fZ = 1.0f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "fireball.dds";
	}
	// Background

	// Node - 1
	{
		int obj_id = 1;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.1875, -0.1875, 0));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_01.dds";
	}
	// Node - 1

	// Node - 2
	{
		int obj_id = 2;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.225, -0.1875, 0.15));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_02.dds";
	}
	// Node - 2

	// Node - 3
	{
		int obj_id = 3;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.225, 0.1875, 0.15));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_03.dds";
	}
	// Node - 3

	return tScene;
}

tScene_Objects * cScene_Manager::Get_Spell_Node_Icebolt()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 4;

	// Background
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, -0.1f, 0.0f));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.375f;
		spells[0].fPosition.fY = 0.375f;
		spells[0].fPosition.fZ = 1.0f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.375f;
		spells[1].fPosition.fY = 0.375;
		spells[1].fPosition.fZ = 1.0f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.375f;
		spells[2].fPosition.fY = -0.375f;
		spells[2].fPosition.fZ = 1.0f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.375f;
		spells[3].fPosition.fY = -0.375f;
		spells[3].fPosition.fZ = 1.0f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "icebolt.dds";
	}
	// Background

	// Node - 1
	{
		int obj_id = 1;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, 0.1875, 0.15));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_01.dds";
	}
	// Node - 1

	// Node - 2
	{
		int obj_id = 2;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.2625, -0.2625, 0));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_02.dds";
	}
	// Node - 2

	// Node - 3
	{
		int obj_id = 3;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.2625, -0.2625, 0));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_03.dds";
	}
	// Node - 3

	return tScene;
}

tScene_Objects * cScene_Manager::Get_Spell_Node_Shield()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 4;

	// Background
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.0f, -0.1f, 0.0f));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.375f;
		spells[0].fPosition.fY = 0.375f;
		spells[0].fPosition.fZ = 1.0f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.375f;
		spells[1].fPosition.fY = 0.375;
		spells[1].fPosition.fZ = 1.0f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.375f;
		spells[2].fPosition.fY = -0.375f;
		spells[2].fPosition.fZ = 1.0f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.375f;
		spells[3].fPosition.fY = -0.375f;
		spells[3].fPosition.fZ = 1.0f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "shield.dds";
	}
	// Background

	// Node - 1
	{
		int obj_id = 1;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(-0.2, 0.1, 0.15));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_01.dds";
	}
	// Node - 1

	// Node - 2
	{
		int obj_id = 2;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0.2, 0.1, 0.15));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_02.dds";
	}
	// Node - 2

	// Node - 3
	{
		int obj_id = 3;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0, -0.375, 0));
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *spells = new tVertex[4];
		spells[0].fPosition.fX = -0.0625f;
		spells[0].fPosition.fY = 0.0625f;
		spells[0].fPosition.fZ = 0.75f;

		spells[0].fTexture_Coordinate.fX = 0.0f;
		spells[0].fTexture_Coordinate.fY = 0.0f;

		spells[1].fPosition.fX = 0.0625f;
		spells[1].fPosition.fY = 0.0625f;
		spells[1].fPosition.fZ = 0.75f;

		spells[1].fTexture_Coordinate.fX = 1.0f;
		spells[1].fTexture_Coordinate.fY = 0.0f;

		spells[2].fPosition.fX = -0.0625f;
		spells[2].fPosition.fY = -0.0625f;
		spells[2].fPosition.fZ = 0.75f;

		spells[2].fTexture_Coordinate.fX = 0.0f;
		spells[2].fTexture_Coordinate.fY = 1.0f;

		spells[3].fPosition.fX = 0.0625f;
		spells[3].fPosition.fY = -0.0625f;
		spells[3].fPosition.fZ = 0.75f;

		spells[3].fTexture_Coordinate.fX = 1.0f;
		spells[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			spells[i].fPosition.fZ *= -1;
		}

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(spells[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int spells_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(spells_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "node_03.dds";
	}
	// Node - 3

	return tScene;
}

tScene_Objects* cScene_Manager::Get_UI()
{
	tScene_Objects* tScene = new tScene_Objects;

	tScene->nObject_Count = 2;

	// Dragon Health Bar
	{
		int obj_id = 0;
		// World Position
		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *dragon_Health_Bar = new tVertex[4];
		dragon_Health_Bar[0].fPosition.fX = -150.0f;
		dragon_Health_Bar[0].fPosition.fY = 40.0f;
		dragon_Health_Bar[0].fPosition.fZ = 0.0f;

		dragon_Health_Bar[0].fTexture_Coordinate.fX = 0.0f;
		dragon_Health_Bar[0].fTexture_Coordinate.fY = 0.0f;

		dragon_Health_Bar[1].fPosition.fX = 150.0f;
		dragon_Health_Bar[1].fPosition.fY = 40.0f;
		dragon_Health_Bar[1].fPosition.fZ = 0.0f;

		dragon_Health_Bar[1].fTexture_Coordinate.fX = 1.0f;
		dragon_Health_Bar[1].fTexture_Coordinate.fY = 0.0f;

		dragon_Health_Bar[2].fPosition.fX = -150.0f;
		dragon_Health_Bar[2].fPosition.fY = -40.0f;
		dragon_Health_Bar[2].fPosition.fZ = 0.0f;

		dragon_Health_Bar[2].fTexture_Coordinate.fX = 0.0f;
		dragon_Health_Bar[2].fTexture_Coordinate.fY = 1.0f;

		dragon_Health_Bar[3].fPosition.fX = 150.0f;
		dragon_Health_Bar[3].fPosition.fY = -40.0f;
		dragon_Health_Bar[3].fPosition.fZ = 0.0f;

		dragon_Health_Bar[3].fTexture_Coordinate.fX = 1.0f;
		dragon_Health_Bar[3].fTexture_Coordinate.fY = 1.0f;

		/*for (int i = 0; i < 4; i++)
		{
			dragon_Health_Bar[i].fPosition.fZ *= -1;
		}*/

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(dragon_Health_Bar[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int drag_Health_Bar_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(drag_Health_Bar_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "Health_Bar.dds";
	}

	{
		int obj_id = 1;

		XMFLOAT4X4 temp;
		XMMATRIX tempMatrix = XMMatrixIdentity();
		XMStoreFloat4x4(&temp, tempMatrix);
		tScene->fWorld_Matrix[obj_id] = XMFLOAT4x4_to_tFloat4x4(temp);

		tVertex *dragon_Health_Bar_Bckgrnd = new tVertex[4];                       // modify to be the backdrop of the health bar
		dragon_Health_Bar_Bckgrnd[0].fPosition.fX = -150.0f;
		dragon_Health_Bar_Bckgrnd[0].fPosition.fY = 40.0f;
		dragon_Health_Bar_Bckgrnd[0].fPosition.fZ = -1.0f;

		dragon_Health_Bar_Bckgrnd[0].fTexture_Coordinate.fX = 0.0f;
		dragon_Health_Bar_Bckgrnd[0].fTexture_Coordinate.fY = 0.0f;

		dragon_Health_Bar_Bckgrnd[1].fPosition.fX = 150.5f;
		dragon_Health_Bar_Bckgrnd[1].fPosition.fY = 40.0f;
		dragon_Health_Bar_Bckgrnd[1].fPosition.fZ = -1.0f;

		dragon_Health_Bar_Bckgrnd[1].fTexture_Coordinate.fX = 1.0f;
		dragon_Health_Bar_Bckgrnd[1].fTexture_Coordinate.fY = 0.0f;

		dragon_Health_Bar_Bckgrnd[2].fPosition.fX = -150.0f;
		dragon_Health_Bar_Bckgrnd[2].fPosition.fY = -40.0f;
		dragon_Health_Bar_Bckgrnd[2].fPosition.fZ = -1.0f;

		dragon_Health_Bar_Bckgrnd[2].fTexture_Coordinate.fX = 0.0f;
		dragon_Health_Bar_Bckgrnd[2].fTexture_Coordinate.fY = 1.0f;

		dragon_Health_Bar_Bckgrnd[3].fPosition.fX = 150.0f;
		dragon_Health_Bar_Bckgrnd[3].fPosition.fY = -40.0f;
		dragon_Health_Bar_Bckgrnd[3].fPosition.fZ = -1.0f;

		dragon_Health_Bar_Bckgrnd[3].fTexture_Coordinate.fX = 1.0f;
		dragon_Health_Bar_Bckgrnd[3].fTexture_Coordinate.fY = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			tScene->tMesh_Data[obj_id].tVerts.push_back(dragon_Health_Bar_Bckgrnd[i]);
		}

		tScene->tMesh_Data[obj_id].nVertex_Count = 4;

		// INDEX BUFFER

		unsigned int dragon_Health_Bar_Bckgrnd_indicies[6] =
		{
			0,1,2,
			1,3,2
		};

		for (int i = 0; i < 6; i++)
		{
			tScene->tMesh_Data[obj_id].nIndicies.push_back(dragon_Health_Bar_Bckgrnd_indicies[i]);
		}
		tScene->tMesh_Data[obj_id].nIndex_Count = 6;

		tScene->szSRV_File_Path[obj_id] = "Neon_Green.dds";
	}
	// Dragon Health Bar
	//tScene->tMesh_Data[0].tVerts[1].fPosition.fX = 1.0f;  // NEW
	//tScene->tMesh_Data[0].tVerts[3].fPosition.fX = 1.0f;  // NEW

	return tScene;
}
