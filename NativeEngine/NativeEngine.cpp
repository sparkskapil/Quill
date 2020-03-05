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

	void WpfViewPort::handleEvents()
	{
		vp->handleEvents();
	}

	MousePosition WpfViewPort::WindowPointToPixel(MousePosition& windowPoint)
	{
		return vp->WindowPointToPixel(windowPoint);
	}
		
}
