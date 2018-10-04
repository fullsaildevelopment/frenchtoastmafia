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
