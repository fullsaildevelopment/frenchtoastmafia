/************************************************************************
* Filename:  		renderer.cpp
* Date:      		10/02/2018
* Mod. Date: 		10/09/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Class to pass data from game loop to renderer_impl
*************************************************************************/
#include "renderer_impl.h"
#include "renderer.h"


cRenderer::cRenderer(native_handle_t hwnd, cView cDefault_View_In)
{
	cDefault_View = cDefault_View_In;
	pcRendererImpl = std::make_unique<cRenderer::tImpl>(hwnd);
	pcRendererImpl->initialize(cDefault_View);
}

cRenderer::~cRenderer() {}

void cRenderer::draw()
{
	pcRendererImpl->draw_view(cDefault_View);
}

