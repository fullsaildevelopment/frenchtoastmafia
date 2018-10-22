#pragma once

#include "renderer_structs.h"
#include "DDSTextureLoader.h"

class cScene_Manager
{
private:
	CComPtr<ID3D11Device> d3dDevice;

public:
	cScene_Manager();
	~cScene_Manager();

	void SetDevice(CComPtr<ID3D11Device> _d3dDevice);
	tScene_Objects GetScene(int nScene_Id);
};

