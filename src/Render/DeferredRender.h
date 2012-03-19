#pragma once

#include "../Scene/Quad.h"
#include <memory>

namespace Render
{
	class GBuffer;
	typedef std::shared_ptr<GBuffer> GBufferPtr;

	class DeferredRender;
	typedef std::shared_ptr<DeferredRender> DeferredRenderPtr;

	class DeferredRender
	{
	public:
		DeferredRender(const GBufferPtr &g_buffer, unsigned int w, unsigned int h);
		void render();

		void reshape(unsigned int w, unsigned int h);

	private:
		unsigned int w;
		unsigned int h;

		GBufferPtr g_buffer;

		Scene::QuadPtr quad;
	};
}
