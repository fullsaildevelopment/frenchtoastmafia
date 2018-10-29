#pragma once

#include "binary_reader.h"
#include "renderer_structs.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class cScene_Manager
{
private:
	CComPtr<ID3D11Device> d3dDevice;

	// OBJECTS
	cBinary_Reader cBinary_Read;

public:
	cScene_Manager();
	~cScene_Manager();

	tScene_Objects GetScene(int nScene_Id);
};

