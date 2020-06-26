#include "Polyline.hxx"

Polyline::Polyline() : isFinished(true)
{
}

Polyline::Polyline(ShapeId id) : IShape(id), isFinished(true)
{
}

Polyline::Polyline(std::initializer_list<Vertex2> list) : isFinished(true)
{
	m_vertices.reserve(list.size());
	m_vertices.insert(m_vertices.begin(), list.begin(), list.end());
}

Polyline::Polyline(const std::vector<Vertex2>& vertices)
{
	m_vertices.clear();
	m_vertices.insert(m_vertices.begin(), vertices.begin(), vertices.end());
	isFinished = true;
}

void Polyline::BeginShape()
{
	isFinished = false;
	m_vertices.clear();
}

void Polyline::EndShape()
{
	isFinished = true;
}

void Polyline::AddVertex(const Vertex2& vertex)
{
	if (m_vertices.size() == 0)
		BeginShape();

	m_vertices.push_back(vertex);
}

void Polyline::RemoveVertex(int index)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices.erase(m_vertices.begin() + index, m_vertices.begin() + index + 1);
}

void Polyline::ReplaceVertex(int index, Vertex2 newVertex)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices[index] = newVertex;
}

bool Polyline::IsFinished() const
{
	return isFinished;
}

ShapeType Polyline::GetType() const
{
	return ShapeType::Line;
}

IShape* Polyline::clone() const
{
	Polyline* line = new Polyline(-1);
	line->isFinished = isFinished;
	line->m_vertices.insert(line->m_vertices.begin(), m_vertices.begin(), m_vertices.end());
	return line;
}
