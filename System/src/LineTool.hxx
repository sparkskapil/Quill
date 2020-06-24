#pragma once
#include "System/API/Tool.h"
#include <map>

class LineTool : public ITool
{
public:
	LineTool();
	~LineTool();

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