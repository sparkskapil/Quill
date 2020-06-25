#pragma once
#include "Core/API/Renderer.h"
#include "Core/API/Vertex2.h"

#include "API/DisplayEntity.h"
namespace RenderingEngine
{
	class IViewPort;

	class Renderer : public IRenderer
	{

	public:
		Renderer(IViewPort& viewPort);

		virtual void draw(const RenderProps& shapeProps) override;
		virtual void clear(ShapeId id) override;

	private:
		IViewPort* m_vp;

	};
}