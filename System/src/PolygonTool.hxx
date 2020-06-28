#pragma once
#include "System/API/Tool.h"
#include <map>

class PolygonTool : public ITool
{
public:
	PolygonTool();
	~PolygonTool();

	void BeginDrawing();
	void AddPoint(Vertex2 vertex);
	void EndDrawing();
	bool IsDrawing();
	void GetShapes(std::vector<IShape*>& shapes) const;
	IShape* GetLatestShape() const;
	IShape* GetCurrentShape() const;

private:
	IShape* m_currentShape;
	std::map<ShapeId, IShape*> m_shapes;
};