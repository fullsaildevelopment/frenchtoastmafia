#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "binary_reader.h"

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
