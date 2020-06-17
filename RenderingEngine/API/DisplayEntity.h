#pragma once

#include<vector>

#include "RenderingEngine/API/ExportSym.h"
#include "Core/API/Vertex2.h"
#include "Core/API/Shape.h"

namespace RenderingEngine
{
	typedef size_t DisplayId;

	class DisplayEntity
	{
		static DisplayId ENTITIES_COUNT;
	protected:
		DisplayId m_displayId;
		ShapeId m_shapeId;
		const std::vector<Vertex2>& m_vertices;

	public:
		DisplayEntity(ShapeId id, const std::vector<Vertex2>& vertices);
		virtual ~DisplayEntity() = default;

		ShapeId GetShapeId() const;
		DisplayId GetDisplayId() const;
		virtual void Render() = 0;
	};
}