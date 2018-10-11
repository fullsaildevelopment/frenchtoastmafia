#pragma once
#include <vector>
#include "fbxsdk.h"
#include "Ben_structs.h"
#include "renderer_structs.h"

#include <d3d11.h>
//VARIABLES
graphics_system mySystem;

pipeline_state_t myMage = { 0,0,0,0,0,0 };
pipeline_state_t arena1 = { 0,1,1,1,0,0 };

//mage stuff

int polyCount;
int vertCount;

vector<float> myFloats;
vector<int> cpIndexes;

vector<myLam> lamVec;
vector<myPhong> phongVec;

PhongForShader mageMaterial;

ID3D11Texture2D* mageAmbientTex[1];
ID3D11ShaderResourceView* mageAmbientSRV[1];

ID3D11Texture2D* mageDiffuseTex[1];
ID3D11ShaderResourceView* mageDiffuseSRV[1];

ID3D11Texture2D* mageEmissiveTex[1];
ID3D11ShaderResourceView* mageEmissiveSRV[1];

ID3D11Texture2D* mageSpecularTex[1];
ID3D11ShaderResourceView* mageSpecularSRV[1];

ID3D11SamplerState* myLinearWrapSampler;

const char* filePath1 = "models\\test\\Idle.fbx";

//arena stuff
int arenaPolyCount;
int arenaVertCount;

vector<float> arenaPositions;
vector<float> arenaUVs;
vector<float> arenaNormals;
vector<int> arenaIndexes;

vector<myLam> arenaLamVec;
vector<myPhong> arenaPhongVec;

PhongForShader arenaMaterial;

ID3D11Texture2D* arenaAmbientTex[1];
ID3D11ShaderResourceView* arenaAmbientSRV[1];

ID3D11Texture2D* arenaDiffuseTex[1];
ID3D11ShaderResourceView* arenaDiffuseSRV[1];

ID3D11Texture2D* arenaEmissiveTex[1];
ID3D11ShaderResourceView* arenaEmissiveSRV[1];

ID3D11Texture2D* arenaSpecularTex[1];
ID3D11ShaderResourceView* arenaSpecularSRV[1];

const char* filePath2 = "models\\Arena\\Arena.fbx";