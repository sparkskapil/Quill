#include "Polygon.hxx"

Polygon::Polygon() : isFinished(true)
{
}

Polygon::Polygon(ShapeId id) : IShape(id), isFinished(true)
{
}

Polygon::Polygon(std::initializer_list<Vertex2> list) : isFinished(true)
{
	m_vertices.reserve(list.size());
	m_vertices.insert(m_vertices.begin(), list.begin(), list.end());
}

Polygon::Polygon(const std::vector<Vertex2>& vertices)
{
	m_vertices.clear();
	m_vertices.insert(m_vertices.begin(), vertices.begin(), vertices.end());
	isFinished = true;
}

void Polygon::BeginShape()
{
	isFinished = false;
	m_vertices.clear();
}

void Polygon::EndShape()
{
	m_vertices.emplace_back(m_vertices.front());
	isFinished = true;
}

void Polygon::AddVertex(const Vertex2& vertex)
{
	if (m_vertices.size() == 0)
		BeginShape();

	m_vertices.push_back(vertex);
}

void Polygon::RemoveVertex(size_t index)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices.erase(m_vertices.begin() + index, m_vertices.begin() + index + 1);
}

void Polygon::ReplaceVertex(size_t index, Vertex2 newVertex)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices[index] = newVertex;
}

bool Polygon::IsFinished() const
{
	return isFinished;
}

ShapeType Polygon::GetType() const
{
	return ShapeType::Polygon;
}

IShape* Polygon::clone() const
{
	Polygon* line = new Polygon(-1);
	line->isFinished = isFinished;
	line->m_vertices.insert(line->m_vertices.begin(), m_vertices.begin(), m_vertices.end());
	return line;
}
