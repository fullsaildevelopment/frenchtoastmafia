#pragma once
#include <vector>
#include "fbxsdk.h"

using namespace std;

//STRUCTURES

class myPhong
{

public:

	double ambient[3];
	const char* ambientFilePath = nullptr;

	double diffuse[3];
	const char* diffuseFilePath = nullptr;

	double emissive[3];
	const char* emissiveFilePath = nullptr;

	double specular[3];
	const char* specularFilePath = nullptr;

	double transparency;

	double shininess;

	double reflection;
	const char* reflectionFilePath = nullptr;
};

class myLam
{

public:

	double ambient[3];
	const char* ambientFilePath = nullptr;

	double diffuse[3];
	const char* diffuseFilePath = nullptr;

	double emissive[3];
	const char* emissiveFilePath = nullptr;

	double transparency;

};

struct myJoint
{
	float global_xform[16];
	int parent_index;
};

struct	my_fbx_joint
{
	FbxNode* node;
	int parent_index;
};

struct custom4X4
{
	//float x[4];
	//float y[4];
	//float z[4];
	//float w[4];

	float global_xform[16];

	int parent;
};

//struct influence
//{
//	int joint;
//	float weight;
//};
//
//struct influenceSet
//{
//	vector<influence> infs;
//};

//struct keyframe
//{
//	double time;
//	vector<custom4X4> joints;
//};
//
//struct anim_clip
//{
//	double duration;
//	vector<keyframe> frames;
//
//	vector<custom4X4> bindPose;
//};