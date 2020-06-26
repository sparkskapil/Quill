#include "CircleEntity.hxx"

namespace RenderingEngine
{
	CircleEntity::CircleEntity(ShapeId id, const std::vector<Vertex2>& vertices) : DisplayEntity(id, vertices)
	{
		SetColors(RAYWHITE, RAYWHITE, RAYWHITE);
	}

	void CircleEntity::Render()
	{
		if (m_vertices.size() == 2)
		{
			auto center = m_vertices[0];
			auto point = m_vertices[1];
			// Center and Point on Circumference Mode 
			DrawCircle( (int)center.x, (int)center.y, 1.0f, m_vertexColor);
			DrawCircle( (int)center.x, (int)center.y, (float)point.Distance(center), m_edgeColor);
		}
	}

	void CircleEntity::SetColors(Color vertexColor, Color edgeColor, Color fillColor)
	{
		m_vertexColor = vertexColor;
		m_edgeColor = edgeColor;
		m_fillColor = fillColor;
	}

	void CircleEntity::SetVertexColor(Color vertexColor)
	{
		m_vertexColor = vertexColor;
	}

	void CircleEntity::SetEdgeColor(Color edgeColor)
	{
		m_edgeColor = edgeColor;
	}

	void CircleEntity::SetFillColor(Color fillColor)
	{
		m_fillColor = fillColor;
	}


}