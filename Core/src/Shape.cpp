#include "API/Shape.h"
#include "API/Renderer.h"

const std::vector<Vertex2>& IShape::GetVertices() const
{
	return m_vertices;
}

ShapeId IShape::GetId() const
{
	return m_id;
}

void IShape::SetRenderer(IRenderer* renderer)
{
	m_renderer = renderer;
}

void IShape::ClearRenderer()
{
	m_renderer = nullptr;
}

void IShape::Render(DrawModes mode) const
{
	if(m_renderer)
		m_renderer->draw(m_vertices, m_id, mode);
}

IShape::IShape() :m_renderer(nullptr), m_vertices({}), m_id(++SHAPES_COUNT)
{
}

IShape::IShape(ShapeId id) : m_renderer(nullptr), m_vertices({}), m_id(id)
{
}

IShape::~IShape()
{
	if(m_renderer)
		m_renderer->clear(m_id);
	m_vertices.clear();
}

ShapeId IShape::SHAPES_COUNT = 0;
