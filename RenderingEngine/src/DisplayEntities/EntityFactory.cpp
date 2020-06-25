#include "EntityFactory.hxx"
#include "LineEntity.hxx"
#include "Core/API/QuillTypes.h"

namespace RenderingEngine
{
	DisplayEntity& EntityGenerator::CreateEntity(const RenderProps& shapeProps)
	{
		switch (shapeProps.type)
		{
		case  ShapeType::Line:
			return CreateLineEntity(shapeProps);
		default:
			break;
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
}
