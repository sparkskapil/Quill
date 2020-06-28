#pragma once
#include "raylib.h"
#include "API/DisplayEntity.h"


namespace RenderingEngine
{
	class PolygonEntity : public DisplayEntity
	{

	public:
		PolygonEntity(ShapeId id, const std::vector<Vertex2>& vertices);
		virtual void Render() override;

		virtual void SetColors(Color vertexColor, Color edgeColor, Color fillColor);
		virtual void SetVertexColor(Color vertexColor);
		virtual void SetEdgeColor(Color edgeColor);
		virtual void SetFillColor(Color fillColor);

	private:
		Color m_vertexColor;
		Color m_edgeColor;
		Color m_fillColor;
	};
}