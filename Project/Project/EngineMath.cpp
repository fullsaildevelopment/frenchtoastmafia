/**
* @file EngineMath.cpp
*
*/

#include "EngineMath.h"

//////////////////////////////////////////////////////////////////////////
// Common math functions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// General Utility functions
//////////////////////////////////////////////////////////////////////////

// Are two floating point numbers equal to each other
// Floating Point Error Safe
//
// IN:		a		The first number
//			b		The second number
//
// RETURN: TRUE iff |a-b| < Tolerance
//
// NOTE:	EPSILON is tolerance
bool IsEqual(float a, float b)
{
	// NOTE: Do not modify.
	return fabs(a - b) < EPSILON;
}

// Is a floating point value equal to zero
// Floating Point Error Safe
//
// IN:		a		The number to check
//
// RETURN:	TRUE iff |a| < Tolerance
//
// NOTE:	Tolerance set by EPSILON
bool IsZero(float a)
{
	// NOTE: Do not modify
	return (fabs(a))<EPSILON;
}

// RETURN: MAX of two numbers
float Max(float a, float b)
{
	// NOTE: Do not modify.
	return (a > b) ? a : b;
}

TVECTOR Max(TVECTOR a, TVECTOR b)
{
	TVECTOR ans;
	ans.x = Max(a.x, b.x);
	ans.y = Max(a.y, b.y);
	ans.z = Max(a.z, b.z);
	return ans;
}

float Max3(float a, float b, float c)
{
	float tmp;
	tmp = Max(a, b);
	tmp = Max(tmp, c);
	return tmp;
}

TVECTOR Max3(TVECTOR a, TVECTOR b, TVECTOR c)
{
	TVECTOR ans;
	ans.x = Max3(a.x, b.x, c.x);
	ans.y = Max3(a.y, b.y, c.y);
	ans.z = Max3(a.z, b.z, c.z);

	return ans;
}

float Max4(float a, float b, float c, float d)
{
	float tmp;
	tmp = Max(a, b);
	tmp = Max(tmp, c);
	tmp = Max(tmp, d);
	return tmp;
}

// RETURN: MIN of two numbers
float Min(float a, float b)
{
	// NOTE: Do not modify.
	return (a < b) ? a : b;
}

TVECTOR Min(TVECTOR a, TVECTOR b)
{
	TVECTOR ans;
	ans.x = Min(a.x, b.x);
	ans.y = Min(a.y, b.y);
	ans.z = Min(a.z, b.z);
	return ans;
}

float Min3(float a, float b, float c)
{
	float tmp;
	tmp = Min(a, b);
	tmp = Min(tmp, c);
	return tmp;
}

TVECTOR Min3(TVECTOR a, TVECTOR b, TVECTOR c)
{
	TVECTOR ans;
	ans.x = Min3(a.x, b.x, c.x);
	ans.y = Min3(a.y, b.y, c.y);
	ans.z = Min3(a.z, b.z, c.z);

	return ans;
}

float Min4(float a, float b, float c, float d)
{
	float tmp;
	tmp = Min(a, b);
	tmp = Min(tmp, c);
	tmp = Min(tmp, d);
	return tmp;
}

// RETURN: Converts input to radian measure
float Degrees_To_Radians(float Deg)
{
	// NOTE: Do not modify.
	return Deg * PI / 180.0f;
}

// RETURN: Converts input to degree measure
float Radians_To_Degrees(float Rad)
{
	// NOTE: Do not modify.
	return Rad * 180.0f / PI;
}
////////////////////////////////////////////////////////////////////////
// Linear Algebra Functions Day 1
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Vector Functions
//////////////////////////////////////////////////////////////////////////

// Check if two TVECTOR's are equal to each other
//
// IN:		v		First Vector
//			w		Second Vector
//
// RETURN:  True if v==w, False otherwise
//
// NOTE:	Use's all four components
//			Should be floating point error safe.
bool Vector_IsEqual(TVECTOR v, TVECTOR w)
{
	bool wCheck = fabs(v.w - w.w) <= EPSILON;
	bool xCheck = fabs(v.x - w.x) <= EPSILON;
	bool yCheck = fabs(v.y - w.y) <= EPSILON;
	bool zCheck = fabs(v.z - w.z) <= EPSILON;
	if (wCheck && xCheck && yCheck && zCheck)
		return true;
	else
		return false;
}

TVECTOR Vector_Abs(TVECTOR v)
{
	TVECTOR ans;
	ans.x = abs(v.x);
	ans.y = abs(v.y);
	ans.z = abs(v.z);
	ans.w = abs(v.w);

	return ans;
}

// ADD two TVECTOR's togother
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v + w
//
// NOTE:	Use's all four components
TVECTOR Vector_Add(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	ans.w = v.w + w.w;
	ans.x = v.x + w.x;
	ans.y = v.y + w.y;
	ans.z = v.z + w.z;
	return ans;
}

// SUBTRACT one TVECTOR from another
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v - w
//
// NOTE:	Use's all four components
TVECTOR Vector_Sub(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	ans.w = v.w - w.w;
	ans.x = v.x - w.x;
	ans.y = v.y - w.y;
	ans.z = v.z - w.z;
	return ans;
}

// MULTIPLY all four components of a TVECTOR by a scalar
//
// IN:		v		The vector to scale
//			s		The value to scale by
//
// RETURN:  s * v
TVECTOR Vector_Scalar_Multiply(TVECTOR v, float s)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	ans.w = v.w * s;
	ans.x = v.x * s;
	ans.y = v.y * s;
	ans.z = v.z * s;
	return ans;
}

// NEGATE all the components of a TVECTOR
//
// IN:		v		The vector to negate
//
// RETURN:	-1 * v
//
// NOTE:	Use's all four components
TVECTOR Vector_Negate(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	ans.w = v.w * -1;
	ans.x = v.x * -1;
	ans.y = v.y * -1;
	ans.z = v.z * -1;
	return ans;
}

// Perform a Dot Product on two TVECTOR's
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v (DOT) w
//
// NOTE:	Use's all four components
float Vector_Dot(TVECTOR v, TVECTOR w)
{
	  
	// TODO LAB 1: Replace with your implementation.
	float ans;
	TVECTOR tmp;
	tmp.w = v.w * w.w;
	tmp.x = v.x * w.x;
	tmp.y = v.y * w.y;
	tmp.z = v.z * w.z;
	ans = tmp.w + tmp.x + tmp.y + tmp.z;
	return ans;
}

// Perform a Cross Product on two TVECTOR's
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v (CROSS) w
//
// NOTE:	The w-component of each vector is not used.
//			The resultant vector will have a w-component of zero.
TVECTOR Vector_Cross(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	ans.w = 0;
	ans.x = (v.y * w.z) - (v.z * w.y);
	ans.y = -((v.x * w.z) - (v.z * w.x));
	ans.z = (v.x * w.y) - (v.y * w.x);
	return ans;
}

// Find the squared length of a TVECTOR
//
// IN:		v		The vector to find the squared length of
//
// RETURN:	Squared Length of TVECTOR
//
// NOTE:	Use's all four components
float Vector_LengthSq(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	float ans = (v.w * v.w) + (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return ans;
}

// Find the length of a TVECTOR
//
// IN:		v		The vector to find the length of
//
// RETURN:	Length of TVECTOR
//
// NOTE:	Use's all four components
float Vector_Length(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	float ans = sqrt(Vector_LengthSq(v));
	return ans;
}

// Normalize a TVECTOR
//
// IN:		v		The vector to normalize
//
// RETURN:	Normalized version of v
//
// NOTE:	Use's all four components
TVECTOR Vector_Normalize(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	float tmp = Vector_Length(v);
	TVECTOR ans;

	ans.w = v.w / tmp;
	ans.x = v.x / tmp;
	ans.y = v.y / tmp;
	ans.z = v.z / tmp;

	return ans;
}

// Makes a TVECTOR's w-component normalized
//
// IN:		v		The vector (point object) to homogenise
//
// RETURN:	The homogenised vector (point)
//
// NOTE:	If the w-component of the vector is 0 then the
//			function will return a zero vector with a w-component
//			of 0.
TVECTOR Vector_Homogenise(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	
	if (v.w == 0)
	{
		ans.w = 0;
		ans.x = 0;
		ans.y = 0;
		ans.z = 0;
	}
	else
	{
		ans.w = v.w / v.w;
		ans.x = v.x / v.w;
		ans.y = v.y / v.w;
		ans.z = v.z / v.w;
	}

	return ans;
}

TVECTOR Perspective_Divide(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;

	if (v.w == 0)
	{
		ans.w = 0;
		ans.x = 0;
		ans.y = 0;
		ans.z = 0;
	}
	else
	{
		ans.w = v.w;
		ans.x = v.x / v.w;
		ans.y = v.y / v.w;
		ans.z = v.z / v.w;
	}

	return ans;
}

// Get a TVECTOR made from the maximun components of two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A maximized vector
//
// NOTE:	Use's all four components
TVECTOR Vector_Maximize(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	if (v.w > w.w)
		ans.w = v.w;
	else
		ans.w = w.w;

	if (v.x > w.x)
		ans.x = v.x;
	else	
		ans.x = w.x;

	if (v.y > w.y)
		ans.y = v.y;
	else	
		ans.y = w.y;

	if (v.z > w.z)
		ans.z = v.z;
	else
		ans.z = w.z;

	return ans;
}

// Get a TVECTOR made from the minimum components of two TVECTOR's
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A minimum vector
//
// NOTE:	Use's all four components
TVECTOR Vector_Minimize(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans;
	if (v.w < w.w)
		ans.w = v.w;
	else
		ans.w = w.w;

	if (v.x < w.x)
		ans.x = v.x;
	else
		ans.x = w.x;

	if (v.y < w.y)
		ans.y = v.y;
	else
		ans.y = w.y;

	if (v.z < w.z)
		ans.z = v.z;
	else
		ans.z = w.z;

	return ans;
}

// Get a TVECTOR made from the average of two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A vector made from the average of two vectors
//
// NOTE:	Use's all four components

TVECTOR Vector_Average(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR ans, tmp;
	tmp = Vector_Add(v, w);
	ans.w = tmp.w / 2;
	ans.x = tmp.x / 2;
	ans.y = tmp.y / 2;
	ans.z = tmp.z / 2;
	return ans;
}

// Find the angle between two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:  The angle in degrees between the two vectors
//
// NOTE:	If either vector is a zero vector then the return
//			value will be 0.
float Vector_AngleBetween(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	float dotted = Vector_Dot(v, w);
	float v_normie = Vector_Length(v);
	float w_normie = Vector_Length(w);
	float ans = Radians_To_Degrees(acos(dotted / (v_normie * w_normie)));
	return ans;
}

// Get the distance one TVECTOR points in the direction of another
// TVECTOR
//
// IN:		v		The first vector
//			w		The direction of the component
//
// RETURN:	The distance that v points in the direction of w.
//
// NOTE:	If w or v is a zero vector then the return value is zero.
float Vector_Component(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	float dotted = Vector_Dot(v, w);
	float w_normie = Vector_Length(w);
	float ans = dotted / w_normie;
	return ans;
}

// Get the TVECTOR that represents v projected on w.
//
// IN:		v		The first vector
//			w		The direction of the projection
//
// RETURN:	The projection of v onto w
//
// NOTE:	If w or v is a zero vector then the return value is zero.
TVECTOR Vector_Project(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	TVECTOR w_normie = Vector_Normalize(w);
	float dotted = Vector_Dot(v, w_normie);
	TVECTOR ans;
	ans.x = w_normie.x * dotted;
	ans.w = w_normie.w * dotted;
	ans.y = w_normie.y * dotted;
	ans.z = w_normie.z * dotted;
	return ans;
}

TVECTOR Vector_Divide(TVECTOR v, float w)
{
	v.x /= w;
	v.y /= w;
	v.z /= w;
	return v;
}

////////////////////////////////////////////////////////////////////////
// Functions Lab  #2
///////////////////////////////////////////////////////////////////////


// Get the reflection of v across w
//
// IN:		v		The vector to reflect
//			w		The "axis" to reflect across
//
// RETURN:	v reflected across w
//
// NOTE:	If w is a zero vector then return -v.
TVECTOR Vector_Reflect(TVECTOR v, TVECTOR w)
{
	// TODO LAB 2: Replace with your implementation.

	TVECTOR ans;
	if (w.w == 0 && w.x == 0 && w.y == 0 && w.z == 0)
	{
		ans = Vector_Negate(v);
	}
	else
	{
		TVECTOR tmp = Vector_Project(v, w);
		ans.w = (2 * tmp.w) - v.w;
		ans.x = (2 * tmp.x) - v.x;
		ans.y = (2 * tmp.y) - v.y;
		ans.z = (2 * tmp.z) - v.z;
	}
	
	return ans;
}

//////////////////////////////////////////////////////////////////////////
// Matrix Functions
//////////////////////////////////////////////////////////////////////////

// Get a [0] matrix
//
// RETURN: A 0 4x4 matrix
TMATRIX Matrix_Zero(void)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m;
	m._e11 = 0;
	m._e12 = 0;
	m._e13 = 0;
	m._e14 = 0;

	m._e21 = 0;
	m._e22 = 0;
	m._e23 = 0;
	m._e24 = 0;

	m._e31 = 0;
	m._e32 = 0;
	m._e33 = 0;
	m._e34 = 0;

	m._e41 = 0;
	m._e42 = 0;
	m._e43 = 0;
	m._e44 = 0;

	return m;
}

// Get a [I] matrix
//
// RETURN: A 4x4 Identity matrix
TMATRIX Matrix_Identity(void)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = {
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
				};
	return m;
}

// Column Major
// Get a translation matrix
//
// IN:		x		Amount of translation in the x direction
//			y		Amount of translation in the y direction
//			z		Amount of translation in the z direction
//
// RETURN:	The translation matrix
TMATRIX Matrix_Create_Translation_Col_Major(float x, float y, float z)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return m;
}

// Row Major
// Get a translation matrix
//
// IN:		x		Amount of translation in the x direction
//			y		Amount of translation in the y direction
//			z		Amount of translation in the z direction
//
// RETURN:	The translation matrix
TMATRIX Matrix_Create_Translation_Row_Major(float x, float y, float z)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = {
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					x, y, z, 1
				};
	return m;
}

TMATRIX Matrix_Create_TVECTORs_Row_Major(TVECTOR x, TVECTOR y, TVECTOR z, TVECTOR w)
{
	TMATRIX res;

	res._e11 = x.x;
	res._e12 = x.y;
	res._e13 = x.z;
	res._e14 = 0.0f;

	res._e21 = y.x;
	res._e22 = y.y;
	res._e23 = y.z;
	res._e24 = 0.0f;

	res._e31 = z.x;
	res._e32 = z.y;
	res._e33 = z.z;
	res._e34 = 0.0f;

	res._e41 = w.x;
	res._e42 = w.y;
	res._e43 = w.z;
	res._e44 = 1.0f;

	return res;
}

TVECTOR Matrix_XAxis(TMATRIX m)
{
	TVECTOR x = { m._e11, m._e12, m._e13, m._e14 };
	return x;
}

TVECTOR Matrix_YAxis(TMATRIX m)
{
	TVECTOR y = { m._e21, m._e22, m._e23, m._e24 };
	return y;
}

TVECTOR Matrix_ZAxis(TMATRIX m)
{
	TVECTOR z = { m._e31, m._e32, m._e33, m._e34 };
	return z;
}

TVECTOR Matrix_WAxis(TMATRIX m)
{
	TVECTOR w = { m._e41, m._e42, m._e43, m._e44 };
	return w;
}

// Create a scale matrix
//
// IN:		x		Amount to scale in the x direction
//			y		Amount to scale in the y direction
//			z		Amount to scale in the z direction
//
// RETURN:	The scale matrix
TMATRIX Matrix_Create_Scale(float x, float y, float z)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = {
					x, 0, 0, 0,
					0, y, 0, 0,
					0, 0, z, 0,
					0, 0, 0, 1
				};
	return m;
}

// Get a rotation matrix for rotation about the x-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A X-Rotation Matrix
TMATRIX Matrix_Create_Rotation_X(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	float Rad = Degrees_To_Radians(Deg);
	TMATRIX m = {
					1, 0, 0, 0,
					0, cos(Rad), -sin(Rad), 0,
					0, sin(Rad), cos(Rad), 0,
					0, 0, 0, 1
				};
	return m;
}

// Get a rotation matrix for rotation about the y-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A Y-Rotation Matrix
TMATRIX Matrix_Create_Rotation_Y(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	float Rad = Degrees_To_Radians(Deg);
	TMATRIX m = {
					cos(Rad), 0, sin(Rad), 0,
					0, 1, 0, 0,
					-sin(Rad), 0, cos(Rad), 0,
					0, 0, 0, 1
				};
	return m;
}

// Get a rotation matrix for rotation about the z-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A Z-Rotation Matrix
TMATRIX Matrix_Create_Rotation_Z(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	float Rad = Degrees_To_Radians(Deg);
	TMATRIX m = {
					cos(Rad), -sin(Rad), 0, 0,
					sin(Rad), cos(Rad), 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
				};
	return m;
}

// ADD two matrices together
//
// IN:		m		The first matrix
//			n		The second matrix
//
// RETURN: m + n
TMATRIX Matrix_Matrix_Add(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	ans._e11 = m._e11 + n._e11;
	ans._e12 = m._e12 + n._e12;
	ans._e13 = m._e13 + n._e13;
	ans._e14 = m._e14 + n._e14;

	ans._e21 = m._e21 + n._e21;
	ans._e22 = m._e22 + n._e22;
	ans._e23 = m._e23 + n._e23;
	ans._e24 = m._e24 + n._e24;

	ans._e31 = m._e31 + n._e31;
	ans._e32 = m._e32 + n._e32;
	ans._e33 = m._e33 + n._e33;
	ans._e34 = m._e34 + n._e34;

	ans._e41 = m._e41 + n._e41;
	ans._e42 = m._e42 + n._e42;
	ans._e43 = m._e43 + n._e43;
	ans._e44 = m._e44 + n._e44;

	return ans;
}

// SUBTRACT two matrices
//
// IN:		m		The first matrix (left hand side)
//			n		The second matrix (right hand side)
//
// RETURN: m - n
TMATRIX Matrix_Matrix_Sub(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	ans._e11 = m._e11 - n._e11;
	ans._e12 = m._e12 - n._e12;
	ans._e13 = m._e13 - n._e13;
	ans._e14 = m._e14 - n._e14;

	ans._e21 = m._e21 - n._e21;
	ans._e22 = m._e22 - n._e22;
	ans._e23 = m._e23 - n._e23;
	ans._e24 = m._e24 - n._e24;

	ans._e31 = m._e31 - n._e31;
	ans._e32 = m._e32 - n._e32;
	ans._e33 = m._e33 - n._e33;
	ans._e34 = m._e34 - n._e34;

	ans._e41 = m._e41 - n._e41;
	ans._e42 = m._e42 - n._e42;
	ans._e43 = m._e43 - n._e43;
	ans._e44 = m._e44 - n._e44;

	return ans;
}

// Multiply a matrix by a scalar
//
// IN:		m		The matrix to be scaled (right hand side)
//			s		The value to scale by   (left hand side)
//
// RETURN:	The matrix formed by s*[m]
TMATRIX Matrix_Scalar_Multiply(TMATRIX m, float s)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	ans._e11 = m._e11 * s;
	ans._e12 = m._e12 * s;
	ans._e13 = m._e13 * s;
	ans._e14 = m._e14 * s;
					  
	ans._e21 = m._e21 * s;
	ans._e22 = m._e22 * s;
	ans._e23 = m._e23 * s;
	ans._e24 = m._e24 * s;
					  
	ans._e31 = m._e31 * s;
	ans._e32 = m._e32 * s;
	ans._e33 = m._e33 * s;
	ans._e34 = m._e34 * s;
					  
	ans._e41 = m._e41 * s;
	ans._e42 = m._e42 * s;
	ans._e43 = m._e43 * s;
	ans._e44 = m._e44 * s;

	return ans;
}

// Negate a matrix
//
// IN:		m		The matrix to negate
//
// RETURN:  The negation of m
TMATRIX Matrix_Negate(TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	ans._e11 = m._e11 * -1;
	ans._e12 = m._e12 * -1;
	ans._e13 = m._e13 * -1;
	ans._e14 = m._e14 * -1;
					  	
	ans._e21 = m._e21 * -1;
	ans._e22 = m._e22 * -1;
	ans._e23 = m._e23 * -1;
	ans._e24 = m._e24 * -1;
					  	
	ans._e31 = m._e31 * -1;
	ans._e32 = m._e32 * -1;
	ans._e33 = m._e33 * -1;
	ans._e34 = m._e34 * -1;
					  	
	ans._e41 = m._e41 * -1;
	ans._e42 = m._e42 * -1;
	ans._e43 = m._e43 * -1;
	ans._e44 = m._e44 * -1;

	return ans;
}

// Transpose a matrix
//
// IN:		m		The matrix to transpose
//
// RETURN:	The transpose of m
TMATRIX Matrix_Transpose(TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	ans._e11 = m._e11;
	ans._e12 = m._e21;
	ans._e13 = m._e31;
	ans._e14 = m._e41;

	ans._e21 = m._e12;
	ans._e22 = m._e22;
	ans._e23 = m._e32;
	ans._e24 = m._e42;

	ans._e31 = m._e13;
	ans._e32 = m._e23;
	ans._e33 = m._e33;
	ans._e34 = m._e43;

	ans._e41 = m._e14;
	ans._e42 = m._e24;
	ans._e43 = m._e34;
	ans._e44 = m._e44;

	return ans;
}

// Multipy a matrix and a vector
//
// IN:		m		The matrix (left hand side)
//			v		The vector (right hand side)
//
// RETURN:	[m]*v
TVECTOR Matrix_Vector_Multiply(TMATRIX m, TVECTOR v)
{
	// TODO LAB 2: Replace with your implementation.
	TVECTOR ans;

	ans.x = m._e11 * v.x;
	ans.x += m._e12 * v.y;
	ans.x += m._e13 * v.z;
	ans.x += m._e14 * v.w;
					  	
	ans.y = m._e21 * v.x;
	ans.y += m._e22 * v.y;
	ans.y += m._e23 * v.z;
	ans.y += m._e24 * v.w;
					  	
	ans.z = m._e31 * v.x;
	ans.z += m._e32 * v.y;
	ans.z += m._e33 * v.z;
	ans.z += m._e34 * v.w;
					  	
	ans.w = m._e41 * v.x;
	ans.w += m._e42 * v.y;
	ans.w += m._e43 * v.z;
	ans.w += m._e44 * v.w;

	return ans;
}

// Multipy a vector and a matrix
//
// IN:		v		The vector ( left hand side)
//			m		The matrix (right hand side)
//
// RETURN:	v*[m]
TVECTOR Vector_Matrix_Multiply(TVECTOR v, TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	TVECTOR ans;

	ans.x = v.x  * m._e11;
	ans.x += v.y * m._e21;
	ans.x += v.z * m._e31;
	ans.x += v.w * m._e41;

	ans.y = v.x  * m._e12;
	ans.y += v.y * m._e22;
	ans.y += v.z * m._e32;
	ans.y += v.w * m._e42;

	ans.z = v.x  * m._e13;
	ans.z += v.y * m._e23;
	ans.z += v.z * m._e33;
	ans.z += v.w * m._e43;

	ans.w = v.x  * m._e14;
	ans.w += v.y * m._e24;
	ans.w += v.z * m._e34;
	ans.w += v.w * m._e44;

	return ans;
}
// Multiply a matrix by a matrix
//
// IN:		m		First Matrix (left hand side)
//			n		Second Matrix (right hand side)
//
// RETURN:	[m]*[n]
TMATRIX Matrix_Matrix_Multiply(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX ans;

	// 11
	ans._e11 = m._e11 * n._e11;
	ans._e11 += m._e12 * n._e21;
	ans._e11 += m._e13 * n._e31;
	ans._e11 += m._e14 * n._e41;
	
	// 12
	ans._e12 = m._e11 * n._e12;
	ans._e12 += m._e12 * n._e22;
	ans._e12 += m._e13 * n._e32;
	ans._e12 += m._e14 * n._e42;
	
	// 13
	ans._e13 = m._e11 * n._e13;
	ans._e13 += m._e12 * n._e23;
	ans._e13 += m._e13 * n._e33;
	ans._e13 += m._e14 * n._e43;
	
	// 14
	ans._e14 = m._e11 * n._e14;
	ans._e14 += m._e12 * n._e24;
	ans._e14 += m._e13 * n._e34;
	ans._e14 += m._e14 * n._e44;

	// 21
	ans._e21 = m._e21 * n._e11;
	ans._e21 += m._e22 * n._e21;
	ans._e21 += m._e23 * n._e31;
	ans._e21 += m._e24 * n._e41;

	// 22
	ans._e22 = m._e21 * n._e12;
	ans._e22 += m._e22 * n._e22;
	ans._e22 += m._e23 * n._e32;
	ans._e22 += m._e24 * n._e42;

	// 23
	ans._e23 = m._e21 * n._e13;
	ans._e23 += m._e22 * n._e23;
	ans._e23 += m._e23 * n._e33;
	ans._e23 += m._e24 * n._e43;

	// 24
	ans._e24 = m._e21 * n._e14;
	ans._e24 += m._e22 * n._e24;
	ans._e24 += m._e23 * n._e34;
	ans._e24 += m._e24 * n._e44;

	// 31
	ans._e31 = m._e31 * n._e11;
	ans._e31 += m._e32 * n._e21;
	ans._e31 += m._e33 * n._e31;
	ans._e31 += m._e34 * n._e41;

	// 32
	ans._e32 = m._e31 * n._e12;
	ans._e32 += m._e32 * n._e22;
	ans._e32 += m._e33 * n._e32;
	ans._e32 += m._e34 * n._e42;

	// 33
	ans._e33 = m._e31 * n._e13;
	ans._e33 += m._e32 * n._e23;
	ans._e33 += m._e33 * n._e33;
	ans._e33 += m._e34 * n._e43;

	// 34
	ans._e34 = m._e31 * n._e14;
	ans._e34 += m._e32 * n._e24;
	ans._e34 += m._e33 * n._e34;
	ans._e34 += m._e34 * n._e44;

	// 41
	ans._e41 = m._e41 * n._e11;
	ans._e41 += m._e42 * n._e21;
	ans._e41 += m._e43 * n._e31;
	ans._e41 += m._e44 * n._e41;

	// 42
	ans._e42 = m._e41 * n._e12;
	ans._e42 += m._e42 * n._e22;
	ans._e42 += m._e43 * n._e32;
	ans._e42 += m._e44 * n._e42;

	// 43
	ans._e43 = m._e41 * n._e13;
	ans._e43 += m._e42 * n._e23;
	ans._e43 += m._e43 * n._e33;
	ans._e43 += m._e44 * n._e43;

	// 44
	ans._e44 = m._e41 * n._e14;
	ans._e44 += m._e42 * n._e24;
	ans._e44 += m._e43 * n._e34;
	ans._e44 += m._e44 * n._e44;

	return ans;
}

////////////////////////////////////////////////////////////////////////
// Matrix Functions Lab # 3
///////////////////////////////////////////////////////////////////////

// HELPER FUNCTION  *** NOT GRADED, ONLY SUGGESTED ***
// USE THIS FUNCTION TO FIND THE DETERMINANT OF A 3*3
// MATRIX. IT CAN BE USED IN THE MATRIX DETERMINANT
// AND MATRIX INVERSE FUNCTIONS BELOW
// 
// RETURN:	The determinant of a 3x3 matrix
float Matrix_Determinant(float e_11,float e_12,float e_13,
						 float e_21,float e_22,float e_23,
						 float e_31,float e_32,float e_33)
{
	float ans = (e_11 * ((e_22 * e_33) - (e_23 * e_32))) - (e_12 * ((e_21 * e_33) - (e_23 * e_31))) + (e_13 * ((e_21 * e_32) - (e_22 * e_31)));
	return ans;
}

// Get the determinant of a matrix
//
// IN:		m		The ONE!
//
// RETURN:	It's deterinant
float Matrix_Determinant(TMATRIX m)
{
	// TODO LAB 3: Replace with your implementation.
	float m11 = m._e11 * Matrix_Determinant(m._e22, m._e23, m._e24, m._e32, m._e33, m._e34, m._e42, m._e43, m._e44);
	float m12 = m._e12 * Matrix_Determinant(m._e21, m._e23, m._e24, m._e31, m._e33, m._e34, m._e41, m._e43, m._e44);
	float m13 = m._e13 * Matrix_Determinant(m._e21, m._e22, m._e24, m._e31, m._e32, m._e34, m._e41, m._e42, m._e44);
	float m14 = m._e14 * Matrix_Determinant(m._e21, m._e22, m._e23, m._e31, m._e32, m._e33, m._e41, m._e42, m._e43);
	float ans = m11 - m12 + m13 - m14;
	return ans;
}

// Get the inverse of a matrix
//
// IN:		m		The matrix to inverse
//
// RETURN:	The Inverse of [m]
//
// NOTE: Returns the matrix itself if m is not invertable.
TMATRIX Matrix_Inverse(TMATRIX m)
{
	// TODO LAB 3: Replace with your implementation.
	float Det = Matrix_Determinant(m);

	if (Det == 0)
		return m;
	else
	{
		float m11 = Matrix_Determinant(m._e22, m._e23, m._e24, m._e32, m._e33, m._e34, m._e42, m._e43, m._e44);
		float m12 = (-1) * (Matrix_Determinant(m._e21, m._e23, m._e24, m._e31, m._e33, m._e34, m._e41, m._e43, m._e44));
		float m13 = Matrix_Determinant(m._e21, m._e22, m._e24, m._e31, m._e32, m._e34, m._e41, m._e42, m._e44);
		float m14 = (-1) * (Matrix_Determinant(m._e21, m._e22, m._e23, m._e31, m._e32, m._e33, m._e41, m._e42, m._e43));

		float m21 = (-1) * (Matrix_Determinant(m._e12, m._e13, m._e14, m._e32, m._e33, m._e34, m._e42, m._e43, m._e44));
		float m22 = Matrix_Determinant(m._e11, m._e13, m._e14, m._e31, m._e33, m._e34, m._e41, m._e43, m._e44);
		float m23 = (-1) * (Matrix_Determinant(m._e11, m._e12, m._e14, m._e31, m._e32, m._e34, m._e41, m._e42, m._e44));
		float m24 = Matrix_Determinant(m._e11, m._e12, m._e13, m._e31, m._e32, m._e33, m._e41, m._e42, m._e43);

		float m31 = Matrix_Determinant(m._e12, m._e13, m._e14, m._e22, m._e23, m._e24, m._e42, m._e43, m._e44);
		float m32 = (-1) * (Matrix_Determinant(m._e11, m._e13, m._e14, m._e21, m._e23, m._e24, m._e41, m._e43, m._e44));
		float m33 = Matrix_Determinant(m._e11, m._e12, m._e14, m._e21, m._e22, m._e24, m._e41, m._e42, m._e44);
		float m34 = (-1) * (Matrix_Determinant(m._e11, m._e12, m._e13, m._e21, m._e22, m._e23, m._e41, m._e42, m._e43));

		float m41 = (-1) * (Matrix_Determinant(m._e12, m._e13, m._e14, m._e22, m._e23, m._e24, m._e32, m._e33, m._e34));
		float m42 = Matrix_Determinant(m._e11, m._e13, m._e14, m._e21, m._e23, m._e24, m._e31, m._e33, m._e34);
		float m43 = (-1) * (Matrix_Determinant(m._e11, m._e12, m._e14, m._e21, m._e22, m._e24, m._e31, m._e32, m._e34));
		float m44 = Matrix_Determinant(m._e11, m._e12, m._e13, m._e21, m._e22, m._e23, m._e31, m._e32, m._e33);

		TMATRIX Adj;
		Adj._e11 = m11;
		Adj._e12 = m21;
		Adj._e13 = m31;
		Adj._e14 = m41;

		Adj._e21 = m12;
		Adj._e22 = m22;
		Adj._e23 = m32;
		Adj._e24 = m42;

		Adj._e31 = m13;
		Adj._e32 = m23;
		Adj._e33 = m33;
		Adj._e34 = m43;

		Adj._e41 = m14;
		Adj._e42 = m24;
		Adj._e43 = m34;
		Adj._e44 = m44;

		TMATRIX Inv;

		Inv._e11 = Adj._e11 / Det;
		Inv._e12 = Adj._e12 / Det;
		Inv._e13 = Adj._e13 / Det;
		Inv._e14 = Adj._e14 / Det;

		Inv._e21 = Adj._e21 / Det;
		Inv._e22 = Adj._e22 / Det;
		Inv._e23 = Adj._e23 / Det;
		Inv._e24 = Adj._e24 / Det;

		Inv._e31 = Adj._e31 / Det;
		Inv._e32 = Adj._e32 / Det;
		Inv._e33 = Adj._e33 / Det;
		Inv._e34 = Adj._e34 / Det;

		Inv._e41 = Adj._e41 / Det;
		Inv._e42 = Adj._e42 / Det;
		Inv._e43 = Adj._e43 / Det;
		Inv._e44 = Adj._e44 / Det;

		return Inv;
	}
}
/*
TMATRIX LookAt(end::float3 a, end::float3 b, end::float3 c)
{
	TVECTOR pos = endFloat3ToTVECTOR(a);
	TVECTOR tar = endFloat3ToTVECTOR(b);
	TVECTOR up = endFloat3ToTVECTOR(c);
	TVECTOR newX, newY, newZ;

	newZ = Vector_Sub(tar, pos);
	newZ = Vector_Normalize(newZ);

	newX = Vector_Cross(up, newZ);
	newX = Vector_Normalize(newX);

	newY = Vector_Cross(newZ, newX);
	newY = Vector_Normalize(newY);

	TMATRIX res = Matrix_Create_TVECTORs_Row_Major(newX, newY, newZ, pos);
	return res;
}

TMATRIX TurnTo(TMATRIX m, end::float3 t, float s)
{
	TVECTOR x = Matrix_XAxis(m);
	TVECTOR y = Matrix_YAxis(m);
	TVECTOR w = Matrix_WAxis(m);
	TVECTOR v = Vector_Sub(w, endFloat3ToTVECTOR(t));
	float x_rotate = Vector_Dot(v, y) * s;
	float y_rotate = Vector_Dot(v, x) * s;

	TMATRIX res = Matrix_Matrix_Multiply(Matrix_Create_Rotation_X(x_rotate), Matrix_Matrix_Multiply(Matrix_Create_Rotation_Y(y_rotate), m));
	
	return res;
}

TMATRIX Matrix_Perspective_Projection()
{
	TMATRIX m;
	float yScale = 1.0f / tanf(Degrees_To_Radians(FOV) / 2.0F);
	float xScale = yScale * AR;

	m =
	{
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, zFar / (zFar - zNear), 1,
		0, 0, -(zFar * zNear) / (zFar - zNear), 0
	};

	return m;
};
*/