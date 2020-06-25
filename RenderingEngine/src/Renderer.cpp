#include "Renderer.hxx"
#include "API/ViewPort.h"
#include "DisplayEntities/EntityFactory.hxx"

namespace RenderingEngine
{
	Renderer::Renderer(IViewPort& viewPort) :m_vp(&viewPort)
	{
	}

	void Renderer::draw(const RenderProps& shapeProps)
	{
		DisplayEntity& entity = EntityGenerator::CreateEntity(shapeProps);
		m_vp->Attach(entity);
	}

	void Renderer::clear(ShapeId id)
	{
		DisplayEntity& entity = m_vp->GetEntityByShapeId(id);
		m_vp->Detach(entity);
	}
}