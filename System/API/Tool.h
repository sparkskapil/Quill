#pragma once
#include "Core/API/Shape.h"
#include <map>

class ITool
{
public:
	virtual ~ITool() = default;
	virtual void BeginDrawing() = 0;
	virtual void AddPoint(Vertex2 vertex) = 0;
	virtual void EndDrawing() = 0;
	virtual bool IsDrawing() = 0;
	virtual void GetShapes(std::vector<IShape*>& shapes) const = 0;
	virtual IShape* GetLatestShape() const = 0;
	virtual IShape* GetCurrentShape() const = 0;
};