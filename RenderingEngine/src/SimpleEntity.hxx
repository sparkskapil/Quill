#pragma once
#include "raylib.h"
#include "API/DisplayEntity.h"

class SimpleEntity : public DisplayEntity
{

public:
	SimpleEntity(ShapeId id, const std::vector<Vertex2>& vertices);
	virtual void Render() override;
	void SetColors(Color vertexColor, Color edgeColor = RAYWHITE, Color fillColor = RAYWHITE);
	void SetVertexColor(Color vertexColor);
	void SetEdgeColor(Color edgeColor);
	void SetFillColor(Color fillColor);

private:
	Color m_vertexColor;
	Color m_edgeColor;
	Color m_fillColor;

};