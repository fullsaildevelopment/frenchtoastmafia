#include "renderer_impl.h"
#include "renderer.h"


cRenderer::cRenderer(native_handle_t hwnd)
{
	pcRendererImpl = std::make_unique<cRenderer::tImpl>(hwnd);
	pcRendererImpl->initialize(cDefault_View);
}

cRenderer::~cRenderer() {}

void cRenderer::draw()
{
	pcRendererImpl->draw_view(cDefault_View);
}

