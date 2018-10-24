/**
* @file EngineMath.h <1ACDFF00-042016>
* This file is included in all files of the project so all major includes are
* included in this file for access by all other files and to prevent multiple
* includes and/or circular includes.

*/

#ifndef _ENGINEMATH_H_
#define _ENGINEMATH_H_

#include <cmath>
#include <math.h>

#include "basic_structs.h"

// Pie is not round, pie are squared :)
#define PI		3.14159f

// Roundoff error to be ignored in floating point number comparisons
#define EPSILON 0.00001f

/**
* Structure represents a 
* vector with 4 components
*/
typedef union TVECTOR
{
	// array access to vector elements
	float e[4];

	// individual component access
	struct  
	{
		float x,y,z,w;
	};
}*LPTVECTOR;

/**
* Constant world axis
*/
const TVECTOR gc_xAxis = {1.0f,0.0f,0.0f,0.0f};
const TVECTOR gc_yAxis = {0.0f,1.0f,0.0f,0.0f};
const TVECTOR gc_zAxis = {0.0f,0.0f,1.0f,0.0f};

/**
* Structure represents a 4x4 matrix 
* row major.
*/
typedef union TMATRIX
{
	// NOTE - first 4 are _e11 - _e14
	float e[16];

	// Single elements in row major format
	struct  
	{
		float _e11,_e12,_e13,_e14;
		float _e21,_e22,_e23,_e24;
		float _e31,_e32,_e33,_e34;
		float _e41,_e42,_e43,_e44;
	};
}*LPTMATRIX;

//////////////////////////////////////////////////////////////////////////
// All math functions. Comments in cpp file
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Data Type conversion functions
//////////////////////////////////////////////////////////////////////////


TVECTOR tFloat4_to_TVECTOR(tFloat4 in);

tFloat4 TVECTOR_To_tFloat4(TVECTOR in);

tFloat4x4 TMATRIX_To_tFloat4x4(TMATRIX in);

TMATRIX tFloat4x4_To_TMATRIX(tFloat4x4 in);

//////////////////////////////////////////////////////////////////////////
// General Utility functions
//////////////////////////////////////////////////////////////////////////


bool IsEqual(float a, float b);

bool IsZero(float a);

float Max(float a, float b);

TVECTOR Max(TVECTOR a, TVECTOR b);

float Max3(float a, float b, float c);

TVECTOR Max3(TVECTOR a, TVECTOR b, TVECTOR c);

float Max4(float a, float b, float c, float d);

float Min(float a, float b);

TVECTOR Min(TVECTOR a, TVECTOR b);

float Min3(float a, float b, float c);

TVECTOR Min3(TVECTOR a, TVECTOR b, TVECTOR c);

float Min4(float a, float b, float c, float d);

float Degrees_To_Radians(float Deg);

float Radians_To_Degrees(float Rad);

//////////////////////////////////////////////////////////////////////////
// Vector Functions
//////////////////////////////////////////////////////////////////////////

bool    Vector_IsEqual(TVECTOR v, TVECTOR w);

TVECTOR Vector_Abs(TVECTOR v);

TVECTOR Vector_Add(TVECTOR v, TVECTOR w);

TVECTOR Vector_Sub(TVECTOR v, TVECTOR w);

TVECTOR Vector_Scalar_Multiply(TVECTOR v, float s);

TVECTOR Vector_Negate(TVECTOR v);

float   Vector_Dot(TVECTOR v, TVECTOR w);

TVECTOR Vector_Cross(TVECTOR v, TVECTOR w);

float   Vector_LengthSq(TVECTOR v);

float   Vector_Length(TVECTOR v);

TVECTOR Vector_Normalize(TVECTOR v);

TVECTOR Vector_Homogenise(TVECTOR v);

TVECTOR Perspective_Divide(TVECTOR v);

TVECTOR Vector_Maximize(TVECTOR v, TVECTOR w);

TVECTOR Vector_Minimize(TVECTOR v, TVECTOR w);

TVECTOR Vector_Average(TVECTOR v, TVECTOR w);

float   Vector_AngleBetween(TVECTOR v, TVECTOR w);

float   Vector_Component(TVECTOR v, TVECTOR w);

TVECTOR Vector_Project(TVECTOR v, TVECTOR w);

TVECTOR Vector_Reflect(TVECTOR v, TVECTOR w);

TVECTOR Vector_Divide(TVECTOR v, float w);

//////////////////////////////////////////////////////////////////////////
// Matrix Functions
//////////////////////////////////////////////////////////////////////////

TMATRIX Matrix_Zero(void);

TMATRIX Matrix_Identity(void);

TMATRIX Matrix_Create_Translation_Col_Major(float x, float y, float z);

TMATRIX Matrix_Create_Translation_Row_Major(float x, float y, float z);

TMATRIX Matrix_Create_TVECTORs_Row_Major(TVECTOR x, TVECTOR y, TVECTOR z, TVECTOR w);

TVECTOR Matrix_XAxis(TMATRIX m);

TVECTOR Matrix_YAxis(TMATRIX m);

TVECTOR Matrix_ZAxis(TMATRIX m);

TVECTOR Matrix_WAxis(TMATRIX m);

TMATRIX Matrix_Create_Scale(float x, float y, float z);

TMATRIX Matrix_Create_Rotation_X(float Deg);

TMATRIX Matrix_Create_Rotation_Y(float Deg);

TMATRIX Matrix_Create_Rotation_Z(float Deg);

TMATRIX Matrix_Matrix_Add(TMATRIX m, TMATRIX n);

TMATRIX Matrix_Matrix_Sub(TMATRIX m, TMATRIX n);

TMATRIX Matrix_Scalar_Multiply(TMATRIX m, float s);

TMATRIX Matrix_Negate(TMATRIX m);

TMATRIX Matrix_Transpose(TMATRIX m);

TVECTOR Vector_Matrix_Multiply(TVECTOR v, TMATRIX m);

TVECTOR Matrix_Vector_Multiply(TMATRIX m, TVECTOR v);

TMATRIX Matrix_Matrix_Multiply(TMATRIX m, TMATRIX n);

float   Matrix_Determinant(TMATRIX m);

TMATRIX Matrix_Inverse(TMATRIX m);

//TMATRIX LookAt(end::float3 a, end::float3 b, end::float3 c);
//
//TMATRIX TurnTo(TMATRIX m, end::float3 t, float s);
//
//TMATRIX Matrix_Perspective_Projection();
#endif