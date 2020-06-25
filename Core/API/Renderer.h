#pragma once

#include <vector>
#include "Core/API/Vertex2.h"
#include "Shape.h"

typedef std::vector<Vertex2> Vertices;

struct RenderProps
{
	const Vertices& vertices;
	ShapeId id;
	ShapeType type;
	DrawModes mode = DrawModes::DRAWN;	
};

class IRenderer
{

public:
	virtual void draw(const RenderProps& shapeProps) = 0;
	virtual void clear(ShapeId id) = 0;

	virtual ~IRenderer() = default;
};