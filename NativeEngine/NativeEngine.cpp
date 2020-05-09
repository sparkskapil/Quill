#include "pch.h"

#include "NativeEngine.h"
#include "RenderingEngine/API/DisplayEntity.h"
#include <chrono>
#include <fstream>

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

	bool WpfViewPort::frame()
	{
		return vp->frame();
	}

	int32_t* WpfViewPort::GetFrameBuffer(Int32% width, Int32% height)
	{
		int w, h;
		auto data = (int32_t*)vp->GetFrameBuffer(w, h);
		width = w;
		height = h;
		return data;
	}

	void WpfViewPort::GetFrameBuffer(IntPtr% ptr, Int32% width, Int32% height)
	{
		Byte* bytes = (Byte*)ptr.ToPointer();

		int w, h;

		auto data = (int32_t*)vp->GetFrameBuffer(w, h);
		
		width = w;
		height = h;
		if (!data) return;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				auto color = data[i * width + j];
				bytes[2] = (Byte)(Int32)((0xFF000000 & color) >> 24);
				bytes[1] = (Byte)(Int32)((0x00FF0000 & color) >> 16);
				bytes[0] = (Byte)(Int32)((0x0000FF00 & color) >> 8);
				bytes += 3;
			}
		}
		delete ((void*)data);
		data = nullptr;
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
