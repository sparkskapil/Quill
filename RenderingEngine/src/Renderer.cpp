#include "Renderer.hxx"
#include "API/ViewPort.h"
#include "SimpleEntity.hxx"
namespace RenderingEngine
{
	Renderer::Renderer(IViewPort& viewPort) :m_vp(&viewPort)
	{
	}

	void Renderer::draw(const std::vector<Vertex2>& vertices, ShapeId id, DrawModes mode)
	{
		SimpleEntity* entity = nullptr;
		if (mode == DrawModes::DRAWN)
		{
			entity = new SimpleEntity(id, vertices);
			entity->SetVertexColor(RED);
		}
		else
		{
			entity = new SimpleEntity(id, vertices);
			entity->SetVertexColor(SKYBLUE);
			entity->SetEdgeColor(DARKBLUE);
		}
		m_vp->Attach(*entity);
	}

	void Renderer::clear(ShapeId id)
	{
		DisplayEntity& entity = m_vp->GetEntityByShapeId(id);
		m_vp->Detach(entity);
	}
}