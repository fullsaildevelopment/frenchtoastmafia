#pragma once

#include "basic_structs.h"
#include "math_conversion.h"
#include "renderer_structs.h"

class cCamera
{
private:
	tFloat4x4 fView_Matrix;
public:
	cCamera();
	~cCamera();

	void SetPosition(tFloat4 fPosition);
	void SetPosition(tFloat4x4 fPosition);
	tFloat4x4 GetPosition();

	void Translation(tFloat4 fMovement_Vect);
	void Rotation(tFloat4 fRotation_Vect);
	void Normalize();
	tFloat4x4 Normalize2(tFloat4x4 temp_MATRIX);
};

