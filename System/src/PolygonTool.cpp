#include "PolygonTool.hxx"
#include "Core/src/Polygon.hxx"

PolygonTool::PolygonTool() : m_currentShape(nullptr)
{
}

PolygonTool::~PolygonTool()
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

void PolygonTool::BeginDrawing()
{
	if (m_currentShape)
		delete m_currentShape;

	m_currentShape = new Polygon();
	m_currentShape->BeginShape();
}

void PolygonTool::AddPoint(Vertex2 vertex)
{
	if (!m_currentShape)
		return;
	m_currentShape->AddVertex(vertex);
}

void PolygonTool::EndDrawing()
{
	m_currentShape->EndShape();
	m_shapes[m_currentShape->GetId()] = m_currentShape;
	m_currentShape = nullptr;
}

bool PolygonTool::IsDrawing()
{
	return m_currentShape != nullptr;
}

void PolygonTool::GetShapes(std::vector<IShape*>& shapes) const
{
	shapes.reserve(m_shapes.size());
	for (const auto& shape : m_shapes)
	{
		shapes.emplace_back(shape.second);
	}
}

IShape* PolygonTool::GetLatestShape() const
{
	if (!m_shapes.size())
		return nullptr;
	return m_shapes.rbegin()->second;
}

IShape* PolygonTool::GetCurrentShape() const
{
	return m_currentShape;
}
