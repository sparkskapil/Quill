#pragma once
#include "Core/API/CoreSym.h"
#include "Core/API/Shape.h"
class MODELAPI Polygon : public IShape
{
public:
	Polygon();
	Polygon(ShapeId id);
	Polygon(std::initializer_list<Vertex2> list);
	Polygon(const std::vector<Vertex2>& vertices);

	// Inherited via IShape
	virtual void BeginShape() override;
	virtual void EndShape() override;
	virtual void AddVertex(const Vertex2& vertex) override;
	virtual void RemoveVertex(int index) override;
	virtual void ReplaceVertex(int index, Vertex2 newVertex) override;
	virtual bool IsFinished() const override;
	virtual ShapeType GetType() const override;

	virtual IShape* clone() const override;

protected:


private:
	bool isFinished;
};