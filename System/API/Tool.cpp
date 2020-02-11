#include "Tool.h"

#include "Core/src/Line.hxx"

LineTool::LineTool() : m_currentShape(nullptr)
{
}

LineTool::~LineTool()
{
	if (m_currentShape)
	{
		delete m_currentShape;
	}
	m_currentShape = nullptr;
	for (auto& shape : m_shapes)
	{
		if (shape.second)
		{
			delete shape.second;
		}
		shape.second = nullptr;
	}
	m_shapes.clear();
}

void LineTool::BeginDrawing()
{
	if (m_currentShape)
		delete m_currentShape;

	m_currentShape = new Line();
	m_currentShape->BeginShape();
}

void LineTool::AddPoint(Vertex2 vertex)
{
	if (!m_currentShape)
		return;

	m_currentShape->AddVertex(vertex);

	if (m_currentShape->IsFinished())
		EndDrawing();	
}

void LineTool::EndDrawing()
{
	m_currentShape->EndShape();
	m_shapes[m_currentShape->GetId()] = m_currentShape;
	m_currentShape = nullptr;
}

bool LineTool::IsDrawing()
{
	return m_currentShape != nullptr;
}

void LineTool::GetShapes(std::vector<IShape*>& shapes) const
{
	shapes.reserve(m_shapes.size());
	for (const auto& shape : m_shapes)
	{
		shapes.emplace_back(shape.second);
	}
}

IShape* LineTool::GetLatestShape() const
{
	if (!m_shapes.size())
		return nullptr;
	return m_shapes.rbegin()->second;
}

IShape* LineTool::GetCurrentShape() const
{
	return m_currentShape;
}
