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

tScene_Objects cScene_Manager::GetScene(int nScene_Id)
{
	tScene_Objects tScene;
	// SCREEN
	if (nScene_Id < 2 || nScene_Id > 3)
	{
	}
	// GAME
	else
	{
		tScene.nObject_Count = 2;

		// GAME 1 with mage
		if (nScene_Id == 2)
		{
			// Battle Mage - 0
			{
				XMFLOAT4X4 temp;
				
				XMMATRIX tempMatrix = XMMatrixIdentity();
				tempMatrix = XMMatrixMultiply(XMMatrixRotationY(180), tempMatrix);
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(2, -3, 15));
				
				
				XMStoreFloat4x4(&temp, tempMatrix);
				
				tScene.fWorld_Matrix[0][0] = XMFLOAT4x4_to_tFloat4x4(temp);
				tScene.bMesh_Has_Skinned[0] = true;
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
				
				tScene.tMaterials_Data[0][0] = cBinary_Read.Read_Material("material.bin");
				tScene.bHas_Animation[0] = true;
				tScene.tAnim_Clip[0] = cBinary_Read.Read_Skeleton("skeleton.bin");
				tScene.tAnim_Data[0] = Create_Inverse_Bind_Pose(tScene.tAnim_Clip[0].tKeyFrames[0]);
			}
			// Battle Mage

			// Dragon - 3
			{
				XMFLOAT4X4 temp;

				XMMATRIX tempMatrix = XMMatrixIdentity();

				//tempMatrix = XMMatrixMultiply(XMMatrixRotationX(3.14 / 3), tempMatrix);
				//tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixRotationY(3.14 / 2));
				//
				tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixTranslation(0,-100,100));
				//
				//tempMatrix = XMMatrixMultiply(tempMatrix, XMMatrixRotationY(3.14));
				//
				//tempMatrix = XMMatrixMultiply(XMMatrixRotationZ(3.14/4), tempMatrix);


				XMStoreFloat4x4(&temp, tempMatrix);

				tScene.fWorld_Matrix[1][0] = XMFLOAT4x4_to_tFloat4x4(temp);
				tScene.bMesh_Has_Skinned[1] = true;
				tMesh_Skinned tDragon = cBinary_Read.Read_Mesh_Skinned("dragon_mesh.bin");

				for (int i = 0; i < tDragon.nVertex_Count; i++)
				{
					tDragon.tVerts[i].fPosition.fZ *= -1;
				}

				for (int i = 0; i < tDragon.nVertex_Count; i++)
				{
					tScene.tMesh_Skinned_Data[1].tVerts.push_back(tDragon.tVerts[i]);
				}

				tScene.tMesh_Skinned_Data[1].nVertex_Count = tDragon.nVertex_Count;


				for (int i = 0; i < tDragon.nIndex_Count; i++)
				{
					tScene.tMesh_Skinned_Data[1].nIndicies.push_back(tDragon.nIndicies[i]);
				}
				tScene.tMesh_Skinned_Data[1].nIndex_Count = tDragon.nIndex_Count;


				tScene.tMaterials_Data[1][0] = cBinary_Read.Read_Material("dragonMaterial.bin");
				tScene.tMaterials_Data[1][0].tMats[0].szDiffuse_File_Path = "Dragon.fbm\\DarkDragon_D.png";
				tScene.bHas_Animation[1] = true;
				tScene.tAnim_Clip[1] = cBinary_Read.Read_Skeleton("dragon_skeleton.bin");
				tScene.tAnim_Data[1] = Create_Inverse_Bind_Pose(tScene.tAnim_Clip[1].tKeyFrames[0]);
			}
			// Dragon

			

		}

		return tScene;
	}
}
