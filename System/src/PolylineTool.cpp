#include "PolylineTool.hxx"
#include "Core/src/Polyline.hxx"

PolylineTool::PolylineTool() : m_currentShape(nullptr)
{
}

PolylineTool::~PolylineTool()
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

void PolylineTool::BeginDrawing()
{
	if (m_currentShape)
		delete m_currentShape;

	m_currentShape = new Polyline();
	m_currentShape->BeginShape();
}

void PolylineTool::AddPoint(Vertex2 vertex)
{
	if (!m_currentShape)
		return;
	m_currentShape->AddVertex(vertex);
}

void PolylineTool::EndDrawing()
{
	m_currentShape->EndShape();
	m_shapes[m_currentShape->GetId()] = m_currentShape;
	m_currentShape = nullptr;
}

bool PolylineTool::IsDrawing()
{
	return m_currentShape != nullptr;
}

void PolylineTool::GetShapes(std::vector<IShape*>& shapes) const
{
	shapes.reserve(m_shapes.size());
	for (const auto& shape : m_shapes)
	{
		shapes.emplace_back(shape.second);
	}
}

IShape* PolylineTool::GetLatestShape() const
{
	if (!m_shapes.size())
		return nullptr;
	return m_shapes.rbegin()->second;
}

IShape* PolylineTool::GetCurrentShape() const
{
	return m_currentShape;
}
