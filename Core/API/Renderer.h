#pragma once

#include <vector>
#include "Core/API/Vertex2.h"
#include "Shape.h"

class IRenderer
{

public:
	virtual void draw(const std::vector<Vertex2>& vertices, ShapeId id, DrawModes mode = DrawModes::DRAWN) = 0;
	virtual void clear(ShapeId id) = 0;

	virtual ~IRenderer() = default;
};