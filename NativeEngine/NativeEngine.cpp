#include "pch.h"

#include "NativeEngine.h"
#include "RenderingEngine/API/DisplayEntity.h"

namespace NativeEngine
{
	WpfViewPort::WpfViewPort() :vp(nullptr)
	{
		vp = &FetchViewPort();
	}

	void WpfViewPort::Attach(DisplayEntity& entity)
	{
		vp->Attach(entity);
	}

	void WpfViewPort::Detach(DisplayEntity& entity)
	{
		vp->Detach(entity);
	}

	void WpfViewPort::DetachByShapeId(ShapeId id)
	{
		vp->DetachByShapeId(id);
	}

	void WpfViewPort::DetachByDisplayId(DisplayId id)
	{
		vp->DetachByDisplayId(id);
	}

	DisplayEntity& WpfViewPort::GetEntityByDisplayId(DisplayId id)
	{
		return vp->GetEntityByDisplayId(id);
	}

	DisplayEntity& WpfViewPort::GetEntityByShapeId(ShapeId id)
	{
		return vp->GetEntityByShapeId(id);
	}

	void WpfViewPort::setup()
	{
		vp->setup();
	}

	void WpfViewPort::draw()
	{
		vp->draw();
	}

	int32_t* WpfViewPort::GetFramBuffer(Int32% width, Int32% height)
	{
		int w, h;
		return (int32_t*)vp->GetFrameBuffer(w, h);
		/*if (!buffer) return NULL;
		std::vector<uint32_t> pixels;

		pixels.reserve(w*h);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pixels.emplace_back(buffer[i*w + j]);
				int8_t R = buffer[i * w + j] & 0xFF000000;
				int8_t G = buffer[i * w + j] & 0x00FF0000;
				int8_t B = buffer[i * w + j] & 0x0000FF00;
				int8_t A = buffer[i * w + j] & 0x000000FF;
				int a = 0;
			}
		}*/
		//return (int32_t*)buffer;
	}

	void WpfViewPort::handleEvents()
	{
		vp->handleEvents();
	}

	MousePosition WpfViewPort::WindowPointToPixel(MousePosition& windowPoint)
	{
		return vp->WindowPointToPixel(windowPoint);
	}
		
}
