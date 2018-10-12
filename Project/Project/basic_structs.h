/************************************************************************
* Filename:  		basic_structs.h
* Date:      		10/02/2018
* Mod. Date: 		10/09/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Additional structs to hold different datatype and make accessing them easier.
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