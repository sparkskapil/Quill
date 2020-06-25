
#include "LineEntity.hxx"

namespace RenderingEngine
{
	LineEntity::LineEntity(ShapeId id, const std::vector<Vertex2>& vertices) : DisplayEntity(id, vertices)
	{
		SetColors(RAYWHITE, RAYWHITE, RAYWHITE);
	}

	void LineEntity::Render()
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

	void LineEntity::SetColors(Color vertexColor, Color edgeColor, Color fillColor)
	{
		m_vertexColor = vertexColor;
		m_edgeColor = edgeColor;
		m_fillColor = fillColor;
	}

	void LineEntity::SetVertexColor(Color vertexColor)
	{
		m_vertexColor = vertexColor;
	}

	void LineEntity::SetEdgeColor(Color edgeColor)
	{
		m_edgeColor = edgeColor;
	}

	void LineEntity::SetFillColor(Color fillColor)
	{
		m_fillColor = fillColor;
	}


}