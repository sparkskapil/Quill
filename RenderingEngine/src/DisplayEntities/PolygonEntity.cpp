
#include "PolygonEntity.hxx"

namespace RenderingEngine
{
	PolygonEntity::PolygonEntity(ShapeId id, const std::vector<Vertex2>& vertices) : DisplayEntity(id, vertices)
	{
		SetColors(RAYWHITE, RAYWHITE, RAYWHITE);
	}

	void PolygonEntity::Render()
	{
		const Vertex2* preVertex = nullptr;
		for (int i = 0; i < m_vertices.size(); i++)
		{
			const Vertex2& vertex = m_vertices[i];
			DrawCircleV(Vector2({ vertex.x, vertex.y }), 1.0f, m_vertexColor);
			if (preVertex)
			{
				DrawLine(preVertex->x, preVertex->y, vertex.x, vertex.y, m_edgeColor);
			}
			preVertex = &vertex;
		}
		if(m_vertices.back() != m_vertices.front())
			DrawLine(m_vertices.back().x, m_vertices.back().y, m_vertices.front().x, m_vertices.front().y, m_edgeColor);
	}

	void PolygonEntity::SetColors(Color vertexColor, Color edgeColor, Color fillColor)
	{
		m_vertexColor = vertexColor;
		m_edgeColor = edgeColor;
		m_fillColor = fillColor;
	}

	void PolygonEntity::SetVertexColor(Color vertexColor)
	{
		m_vertexColor = vertexColor;
	}

	void PolygonEntity::SetEdgeColor(Color edgeColor)
	{
		m_edgeColor = edgeColor;
	}

	void PolygonEntity::SetFillColor(Color fillColor)
	{
		m_fillColor = fillColor;
	}


}