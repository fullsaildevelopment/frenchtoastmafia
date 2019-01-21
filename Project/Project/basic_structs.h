/************************************************************************
* Filename:  		Basic_Structs.h
* Date:      		02/10/2018
* Mod. Date: 		08/11/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional basic structs to hold different datatype and make accessing them easier.
*************************************************************************/
#pragma once

#include <array>
#include <vector>

struct tFloat2
{
	float fX;
	float fY;

	float& operator[](int i) { return (&fX)[i]; }
	float operator[](int i)const { return (&fX)[i]; }
};

struct tFloat3
{
	union
	{
		struct
		{
			float fX;
			float fY;
			float fZ;
		};

		struct
		{
			float fA[3];
		};
	};

	float& operator[](int i) { return (&fX)[i]; }
	float operator[](int i)const { return (&fX)[i]; }
};

struct tFloat4
{
	union
	{
		struct
		{
			float fX;
			float fY;
			float fZ;
			float fW;
		};

		struct
		{
			float fA[4];
		};

		struct
		{
			tFloat3 fXYZ;
		};

		struct
		{
			tFloat2 fXY;
			tFloat2 fZW;
		};
	};

	float& operator[](int i) { return (&fX)[i]; }
	float operator[](int i)const { return (&fX)[i]; }
};

struct alignas(16) tFloat4_a : tFloat4 {};

struct tFloat4x4
{
	union
	{
		struct
		{
			tFloat4 tX;
			tFloat4 tY;
			tFloat4 tZ;
			tFloat4 tW;
		};

		struct
		{
			float fA[16];
		};
	};

	tFloat4& operator[](int i) { return (&tX)[i]; }
	tFloat4 operator[](int i)const { return (&tX)[i]; }
};

struct tVertex
{
	tFloat4 fPosition;
	tFloat4 fNormal;
	tFloat4 fColor;
	tFloat2 fTexture_Coordinate;
};

struct tVertex_Skinned
{
	tFloat4 fPosition;
	tFloat4 fNormal;
	tFloat4 fColor;
	tFloat2 fTexture_Coordinate;
	int nJoints[4];
	tFloat4 fWeights;
};
struct tJoint
{
	tFloat4x4 tData;
	int nParent_Index;
};

struct tKeyframe
{
	double dTime;
	std::vector<tJoint> tJoints;
};

struct tAnimation_Clip
{
	double dDuration;
	std::vector<tKeyframe> tKeyFrames;
};

struct tAnimation_Data
{
	tFloat4x4 tInverse[32]{};
	tFloat4x4 tTweened[32]{};
};

struct particle
{
	tFloat3 position;
	tFloat3 prev_Position;
	tFloat4 color;

	particle()
	{
		position.fX = 0;      // % / * by small #
		position.fY = 0;
		position.fZ = 0;

		prev_Position.fX = (float)(rand() % 10 + 1 - 5) / 10.0f;   // prev_Position.fX = (float)(rand() % 10 + 1 - 5) / 10.0f
		prev_Position.fY = (float)(rand() % 10 + 1 - 5) / 10.0f;   // prev_Position.fY = (float)(rand() % 10 + 1 - 5) / 10.0f
		prev_Position.fZ = (float)(rand() % 10 + 1 - 5) / 10.0f;   // prev_Position.fZ = (float)(rand() % 10 + 1 - 5) / 10.0f

		//color.fX = rand() % 10 * 0.10f;        // % / * by small #
		//color.fY = rand() % 10 * 0.10f;
		//color.fZ = rand() % 10 * 0.10f;
		//color.fW = 1.0f;

	}
};
