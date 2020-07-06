#include "Circle.hxx"

Circle::Circle() : isFinished(true)
{
	m_vertices.reserve(MAX_VERTICES);
}

Circle::Circle(ShapeId id) : IShape(id), isFinished(true)
{
	m_vertices.reserve(MAX_VERTICES);
}

Circle::Circle(std::initializer_list<Vertex2> list) : isFinished(true)
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

Circle::Circle(const Vertex2& vertex1, const Vertex2& vertex2) :
	isFinished(true)
{
	m_vertices.reserve(2);
	m_vertices.emplace_back(vertex1);
	m_vertices.emplace_back(vertex2);
}

void Circle::BeginShape()
{
	isFinished = false;
	m_vertices.clear();
}

void Circle::EndShape()
{
	isFinished = true;
}

void Circle::AddVertex(const Vertex2& vertex)
{
	if (m_vertices.size() == 0)
		BeginShape();

	m_vertices.push_back(vertex);
	if (m_vertices.size() == MAX_VERTICES)
		EndShape();
}

void Circle::RemoveVertex(size_t index)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices.erase(m_vertices.begin() + index, m_vertices.begin() + index + 1);
}

void Circle::ReplaceVertex(size_t index, Vertex2 newVertex)
{
	if (index >= m_vertices.size())
		throw std::exception("Invalid Index");
	m_vertices[index] = newVertex;
}

bool Circle::IsFinished() const
{
	return isFinished;
}

IShape* Circle::clone() const
{
	Circle* circle = new Circle(-1);
	circle->isFinished = isFinished;
	circle->m_vertices.insert(circle->m_vertices.begin(), m_vertices.begin(), m_vertices.end());
	return circle;
}

ShapeType Circle::GetType() const
{
	return ShapeType::Circle;
}
