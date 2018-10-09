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
	float m_x;
	float m_y;

	float& operator[](int i) { return (&m_x)[i]; }
	float operator[](int i)const { return (&m_x)[i]; }
};

struct tFloat3
{
	union
	{
		struct
		{
			float m_x;
			float m_y;
			float m_z;
		};

		struct
		{
			float m_a[3];
		};
	};

	float& operator[](int i) { return (&m_x)[i]; }
	float operator[](int i)const { return (&m_x)[i]; }
};

struct tFloat4
{
	union
	{
		struct
		{
			float m_x;
			float m_y;
			float m_z;
			float m_w;
		};

		struct
		{
			float m_a[4];
		};

		struct
		{
			tFloat3 m_xyz;
		};

		struct
		{
			tFloat2 m_xy;
			tFloat2 m_zw;
		};
	};

	float& operator[](int i) { return (&m_x)[i]; }
	float operator[](int i)const { return (&m_x)[i]; }
};

struct alignas(16) tFloat4_a : tFloat4 {};

struct tFloat4x4
{
	union
	{
		struct
		{
			tFloat4 m_x;
			tFloat4 m_y;
			tFloat4 m_z;
			tFloat4 m_w;
		};

		struct
		{
			float m_a[16];
		};
	};

	tFloat4& operator[](int i) { return (&m_x)[i]; }
	tFloat4 operator[](int i)const { return (&m_x)[i]; }
};

struct tVertex
{
	tFloat4 fPosition;
	tFloat4 fNormal;
	tFloat4 fColor;
	tFloat2 fTexture_Coordinate;
};

