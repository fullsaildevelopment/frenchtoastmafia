/************************************************************************
* Filename:  		Binary_Reader.h
* Date:      		12/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Reader for Binary file with data such as Meshs, Materials, Keyframe for Animations
*************************************************************************/
#pragma once

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "Binary_Reader.h"

cBinary_Reader::cBinary_Reader()
{
}

cBinary_Reader::~cBinary_Reader()
{
}

tMesh cBinary_Reader::Read_Mesh(const char * szRead_Path)
{
	tMesh tOutput;

	std::fstream fs;
	fs.open(szRead_Path, std::ios::in | std::ios::binary);
	uint32_t nVert_Size = 0;
	fs.read((char *)&nVert_Size, sizeof(uint32_t));
	vector<tVertex> tUnique_Verts;
	tUnique_Verts.resize(nVert_Size);
	fs.read((char*)tUnique_Verts.data(), sizeof(tVertex) * nVert_Size);
	uint32_t nInd_Size = 0;
	fs.read((char *)&nInd_Size, sizeof(uint32_t));
	vector<int> nIndicies;
	nIndicies.resize(nInd_Size);
	fs.read((char*)nIndicies.data(), sizeof(int) * nInd_Size);

	tOutput.nVertex_Count = nVert_Size;
	tOutput.tVerts = tUnique_Verts;
	tOutput.nIndex_Count = nInd_Size;
	tOutput.nIndicies = nIndicies;

	return tOutput;
}

tMaterials cBinary_Reader::Read_Material(const char * szRead_Path)
{
	tMaterials tOutput;

	std::fstream fs;
	fs.open(szRead_Path, std::ios::in | std::ios::binary);
	uint32_t nSize;
	fs.read((char *)&nSize, sizeof(uint32_t));
	vector<tMaterial> tMats;
	tMats.resize(nSize);
	int nFile_Path_Size = 0;
	char *szFile_Path = nullptr;
	for (uint32_t i = 0; i < nSize; i++)
	{
		fs.read((char*)&tMats[i].tAmbient, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szAmbient_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].tDiffuse, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szDiffuse_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].tEmissive, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szEmissive_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].tReflection, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szReflection_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].fShininess, sizeof(float));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szShininess_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].tSpecular, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szSpecular_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		fs.read((char*)&tMats[i].tTransparency, sizeof(tFloat4));
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		if (nFile_Path_Size > 0)
		{
			szFile_Path = new char[nFile_Path_Size + 1];
			fs.read((char*)szFile_Path, nFile_Path_Size);
			szFile_Path[nFile_Path_Size] = '\0';
			tMats[i].szTransparency_File_Path = szFile_Path;
			delete[] szFile_Path;
		}

		szFile_Path = nullptr;
	}

	tOutput.tMats = tMats;

	return tOutput;
}

tAnimation_Clip cBinary_Reader::Read_Skeleton(const char * read_path)
{
	tAnimation_Clip tOutput;

	std::fstream fs;
	fs.open(read_path, std::ios::in | std::ios::binary);

	double dDuration = 0.0;
	fs.read((char *)&dDuration, sizeof(double));
	tOutput.dDuration = dDuration;

	int nFrames = 0;
	fs.read((char *)&nFrames, sizeof(int));

	for (int i = 0; i < nFrames; i++)
	{
		tKeyframe tKey;

		double dJoint_Time = 0.0;
		fs.read((char *)&dJoint_Time, sizeof(double));
		tKey.dTime = dJoint_Time;

		int nJoint_Size = 0;
		fs.read((char *)&nJoint_Size, sizeof(int));

		for (int j = 0; j < nJoint_Size; j++)
		{
			tJoint tJoint_Data;

			fs.read((char *)&tJoint_Data, sizeof(tJoint));

			tKey.tJoints.push_back(tJoint_Data);
		}

		tOutput.tKeyFrames.push_back(tKey);
	}

	return tOutput;
}

tMesh_Skinned cBinary_Reader::Read_Mesh_Skinned(const char * szRead_Path)
{
	tMesh_Skinned tOutput;

	std::fstream fs;
	fs.open(szRead_Path, std::ios::in | std::ios::binary);
	uint32_t nVert_Size = 0;
	fs.read((char *)&nVert_Size, sizeof(uint32_t));
	vector<tVertex_Skinned> tUnique_Verts;
	tUnique_Verts.resize(nVert_Size);
	fs.read((char*)tUnique_Verts.data(), sizeof(tVertex_Skinned) * nVert_Size);
	uint32_t nInd_Size = 0;
	fs.read((char *)&nInd_Size, sizeof(uint32_t));
	vector<int> nIndicies;
	nIndicies.resize(nInd_Size);
	fs.read((char*)nIndicies.data(), sizeof(int) * nInd_Size);

	tOutput.nVertex_Count = nVert_Size;
	tOutput.tVerts = tUnique_Verts;
	tOutput.nIndex_Count = nInd_Size;
	tOutput.nIndicies = nIndicies;

	return tOutput;
}


tBinary_Screen cBinary_Reader::Read_Screen_Binary(const char* read_file_name)
{
	tBinary_Screen tOutput;
	std::fstream fs;
	fs.open(read_file_name, std::ios::in | std::ios::binary);
	int obj_count = 0;
	uint32_t nVert_Size = 0;
	uint32_t nInd_Size = 0;
	int nFile_Path_Size = 0;
	char *szFile_Path = nullptr;
	int nVS_Check, nPS_Check, nSRV_Check = 0;
	std::string szVS_FP, szPS_FP, szSRV_FP;
	
	// Object Count
	fs.read((char *)&obj_count, sizeof(uint32_t));
	// tMesh.nVertex_Count
	fs.read((char *)&nVert_Size, sizeof(uint32_t));
	// tMesh.tVerts
	vector<tVertex> tUnique_Verts;
	tUnique_Verts.resize(nVert_Size);
	fs.read((char*)tUnique_Verts.data(), sizeof(tVertex) * nVert_Size);
	// tMesh.nIndex_Count
	fs.read((char *)&nInd_Size, sizeof(uint32_t));
	// tMesh.nIndicies
	vector<int> nIndicies;
	nIndicies.resize(nInd_Size);
	fs.read((char*)nIndicies.data(), sizeof(int) * nInd_Size);
	// vs_check
	fs.read((char*)&nVS_Check, sizeof(int));
	if (nVS_Check != 0)
	{
		// vs_fp
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		szFile_Path = new char[nFile_Path_Size + 1];
		fs.read((char*)szFile_Path, nFile_Path_Size);
		szFile_Path[nFile_Path_Size] = '\0';
		szVS_FP = szFile_Path;
		delete[] szFile_Path;
	}
	// ps_check
	fs.read((char*)&nPS_Check, sizeof(int));
	if (nPS_Check != 0)
	{
		// ps_fp
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		szFile_Path = new char[nFile_Path_Size + 1];
		fs.read((char*)szFile_Path, nFile_Path_Size);
		szFile_Path[nFile_Path_Size] = '\0';
		szPS_FP = szFile_Path;
		delete[] szFile_Path;
	}
	// srv_check
	fs.read((char*)&nSRV_Check, sizeof(int));
	if (nSRV_Check != 0)
	{
		// srv_fp
		fs.read((char*)&nFile_Path_Size, sizeof(int));
		szFile_Path = new char[nFile_Path_Size + 1];
		fs.read((char*)szFile_Path, nFile_Path_Size);
		szFile_Path[nFile_Path_Size] = '\0';
		szSRV_FP = szFile_Path;
		delete[] szFile_Path;
	}
	bool vs_check;
	std::string vs_name;
	bool ps_check;
	std::string ps_name;
	bool srv_check;
	std::string srv_name;

	tOutput.nObject_Count = obj_count;
	tOutput.tMes.nVertex_Count = nVert_Size;
	tOutput.tMes.tVerts = tUnique_Verts;
	tOutput.tMes.nIndex_Count = nInd_Size;
	tOutput.tMes.nIndicies = nIndicies;
	tOutput.vs_check = nVS_Check;
	if (nVS_Check != 0)
		tOutput.vs_name = szVS_FP;
	tOutput.ps_check = nPS_Check;
	if (nPS_Check != 0)
		tOutput.ps_name = szPS_FP;
	tOutput.srv_check = nSRV_Check;
	if (nSRV_Check != 0)
		tOutput.srv_name = szSRV_FP;

	return tOutput;
}