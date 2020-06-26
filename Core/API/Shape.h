#pragma once
#include <vector>
#include "Core/API/QuillTypes.h"
#include "Core/API/CoreSym.h"
#include "Core/API/Vertex2.h"

class IRenderer; 

class MODELAPI IShape
{
protected:
	static ShapeId SHAPES_COUNT;
	IRenderer* m_renderer;
	std::vector<Vertex2> m_vertices;
	ShapeId m_id;

public:
	IShape();
	IShape(ShapeId id);
	virtual ~IShape();

	virtual void BeginShape() = 0;
	virtual void EndShape() = 0;
	virtual void AddVertex(const Vertex2& vertex) = 0;
	virtual void RemoveVertex(int index) = 0;
	virtual void ReplaceVertex(int index, Vertex2 newVertex) = 0;
	virtual bool IsFinished() const = 0;
	virtual ShapeType GetType() const = 0;
	virtual const std::vector<Vertex2>& GetVertices() const;

	virtual IShape* clone() const = 0;

	ShapeId GetId() const;
	void SetRenderer(IRenderer* renderer);
	void ClearRenderer();
	void Render(DrawModes mode = DrawModes::DRAWN) const;
};