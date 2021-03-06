#pragma once
#include "Core/API/CoreSym.h"
#include "Core/API/Shape.h"
class MODELAPI Line : public IShape 
{
public:
	Line();
	Line(ShapeId id);
	Line(std::initializer_list<Vertex2> list);
	Line(const Vertex2& vertex1, const Vertex2& vertex2);

	// Inherited via IShape
	virtual void BeginShape() override;
	virtual void EndShape() override;
	virtual void AddVertex(const Vertex2& vertex) override;
	virtual void RemoveVertex(size_t index) override;
	virtual void ReplaceVertex(size_t index, Vertex2 newVertex) override;
	virtual bool IsFinished() const override;
	virtual ShapeType GetType() const override;

	virtual IShape* clone() const override;

protected:


private:
	bool isFinished;
	static const size_t MAX_VERTICES = 2;
};