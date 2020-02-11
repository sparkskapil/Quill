
#include "SimpleEntity.hxx"

SimpleEntity::SimpleEntity(ShapeId id, const std::vector<Vertex2>& vertices) : DisplayEntity(id, vertices)
{
	SetColors(RAYWHITE);
}

void SimpleEntity::Render()
{
	const Vertex2* preVertex = nullptr;
	for (int i = 0; i < m_vertices.size(); i++)
	{
		const Vertex2& vertex = m_vertices[i];
		DrawCircleV(Vector2({ vertex.x, vertex.y }), 1.0f, m_vertexColor);
		if (preVertex)
		{
			DrawLineV(Vector2({ preVertex->x, preVertex->y }), Vector2({ vertex.x, vertex.y }), m_edgeColor);
		}
		preVertex = &vertex;
	}
}

void SimpleEntity::SetColors(Color vertexColor, Color edgeColor, Color fillColor)
{
	m_vertexColor = vertexColor;
	m_edgeColor = edgeColor;
	m_fillColor = fillColor;
}

void SimpleEntity::SetVertexColor(Color vertexColor)
{
	m_vertexColor = vertexColor;
}

void SimpleEntity::SetEdgeColor(Color edgeColor)
{
	m_edgeColor = edgeColor;
}

void SimpleEntity::SetFillColor(Color fillColor)
{
	m_fillColor = fillColor;
}


