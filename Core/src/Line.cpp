#include "Line.hxx"

Line::Line() : isFinished(true)
{
	m_vertices.reserve(MAX_VERTICES);
}

Line::Line(ShapeId id): IShape(id), isFinished(true)
{
	m_vertices.reserve(MAX_VERTICES);
}

Line::Line(std::initializer_list<Vertex2> list) : isFinished(true)
{
	if (list.size() == MAX_VERTICES) {
		m_vertices.reserve(MAX_VERTICES);
		m_vertices.insert(m_vertices.begin(), list.begin(), list.end());
	}
	else
	{
		throw std::exception("Invalid parameter count");
	}
}

Line::Line(const Vertex2& vertex1, const Vertex2& vertex2) :
	isFinished(true)
{
	m_vertices.reserve(2);
	m_vertices.emplace_back(vertex1);
	m_vertices.emplace_back(vertex2);
}

void Line::BeginShape()
{
	isFinished = false;
	m_vertices.clear();
}

void Line::EndShape()
{
	isFinished = true;
}

void Line::AddVertex(const Vertex2& vertex)
{
	if (m_vertices.size() == 0)
		BeginShape();

	m_vertices.push_back(vertex);
	if (m_vertices.size() == MAX_VERTICES)
		EndShape();
}

void Line::RemoveVertex(int index)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices.erase(m_vertices.begin() + index, m_vertices.begin() + index + 1);
}

void Line::ReplaceVertex(int index, Vertex2 newVertex)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices[index] = newVertex;
}

bool Line::IsFinished() const
{
	return isFinished;
}

IShape* Line::clone() const
{
	Line* line = new Line(-1);
	line->isFinished = isFinished;
	line->m_vertices.insert(line->m_vertices.begin(), m_vertices.begin(), m_vertices.end());
	return line;
}
