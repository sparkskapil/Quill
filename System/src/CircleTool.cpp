#include "CircleTool.hxx"
#include "Core/src/Circle.hxx"

CircleTool::CircleTool() : m_currentShape(nullptr)
{
}

CircleTool::~CircleTool()
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

void CircleTool::BeginDrawing()
{
	if (m_currentShape)
		delete m_currentShape;

	m_currentShape = new Circle();
	m_currentShape->BeginShape();
}

void CircleTool::AddPoint(Vertex2 vertex)
{
	if (!m_currentShape)
		return;

	m_currentShape->AddVertex(vertex);

	if (m_currentShape->IsFinished())
		EndDrawing();
}

void CircleTool::EndDrawing()
{
	m_currentShape->EndShape();
	m_shapes[m_currentShape->GetId()] = m_currentShape;
	m_currentShape = nullptr;
}

bool CircleTool::IsDrawing()
{
	return m_currentShape != nullptr;
}

void CircleTool::GetShapes(std::vector<IShape*>& shapes) const
{
	shapes.reserve(m_shapes.size());
	for (const auto& shape : m_shapes)
	{
		shapes.emplace_back(shape.second);
	}
}

IShape* CircleTool::GetLatestShape() const
{
	if (!m_shapes.size())
		return nullptr;
	return m_shapes.rbegin()->second;
}

IShape* CircleTool::GetCurrentShape() const
{
	return m_currentShape;
}
