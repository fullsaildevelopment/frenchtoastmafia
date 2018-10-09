/************************************************************************
* Filename:  		renderer.cpp
* Date:      		10/02/2018
* Mod. Date: 		10/09/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Class to pass data from game loop to renderer_impl
*************************************************************************/
#pragma once
#include <memory>
#include "view.h"

class cRenderer
{
public:
	using native_handle_t = void*;

	cRenderer(native_handle_t hwnd);

	~cRenderer();

	cView cDefault_View;

	void draw();

private:

	struct tImpl;

	std::unique_ptr<cRenderer::tImpl> pcRendererImpl;
};
