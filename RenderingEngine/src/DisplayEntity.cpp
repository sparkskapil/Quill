#include "API/DisplayEntity.h"

DisplayId DisplayEntity::ENTITIES_COUNT = 0;
DisplayEntity::DisplayEntity(ShapeId id, const std::vector<Vertex2>& vertices) :
	m_displayId(++ENTITIES_COUNT), m_shapeId(id), m_vertices(vertices)
{
}

ShapeId DisplayEntity::GetShapeId() const
{
	return m_shapeId;
}

DisplayId DisplayEntity::GetDisplayId() const
{
	return m_displayId;
}
