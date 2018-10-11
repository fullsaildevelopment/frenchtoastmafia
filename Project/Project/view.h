#pragma once

#include "math_conversion.h"
#include "renderer.h"


class cView
{
	// stores properties of a view
	//	viewport(s)
	//	view and projection matrices
	//	type information ( Orthographics/Perspective/Cubemap/Shadowmap/etc)
	//	render target id(s) (optional)
	//	
	// maintains a visible-set of renderable objects in view (implemented in a future assignment)
private:
	tFloat4x4 tCamera_Matrix;

public:
	cView() {}
	~cView() {}

	tFloat4x4 getCamera_Matrix()
	{
		return tCamera_Matrix;
	}

	void setCamera_Matrix(XMFLOAT4X4 fCamera_Matrix)
	{
		tCamera_Matrix = XMFLOAT4x4_to_tFloat4x4(fCamera_Matrix);
	}
};
