#include "EntityFactory.hxx"
#include "LineEntity.hxx"
#include "CircleEntity.hxx"

namespace RenderingEngine
{
	DisplayEntity& EntityGenerator::CreateEntity(const RenderProps& shapeProps)
	{
		switch (shapeProps.type)
		{
		case  ShapeType::Line:
			return CreateLineEntity(shapeProps);
		case  ShapeType::Circle:
			return CreateCircleEntity(shapeProps);
		default:
			return CreateLineEntity(shapeProps);
		}
	}

	DisplayEntity& EntityGenerator::CreateLineEntity(const RenderProps& shapeProps)
	{
		auto entity = new LineEntity(shapeProps.id, shapeProps.vertices);
		auto edgeColor = RAYWHITE;
		auto vertexColor = RED;
		if (shapeProps.mode == DrawModes::DRAWING)
		{
			edgeColor = DARKBLUE;
			vertexColor = SKYBLUE;
		}
		entity->SetEdgeColor(edgeColor);
		entity->SetVertexColor(vertexColor);

		return *entity;
	}

	DisplayEntity& EntityGenerator::CreateCircleEntity(const RenderProps& shapeProps)
	{
		auto entity = new CircleEntity(shapeProps.id, shapeProps.vertices);
		auto edgeColor = RAYWHITE;
		auto vertexColor = RED;
		if (shapeProps.mode == DrawModes::DRAWING)
		{
			edgeColor = DARKBLUE;
			vertexColor = SKYBLUE;
		}
		entity->SetEdgeColor(edgeColor);
		entity->SetVertexColor(vertexColor);
		entity->SetFillColor(BLANK);

		return *entity;
	}
}
