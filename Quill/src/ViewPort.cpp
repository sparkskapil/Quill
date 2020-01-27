#include "ViewPort.hxx"
#include "SimpleEntity.hxx"
#include "Core/src/Line.hxx"
#include "Renderer.hxx"

//Raylib Global Helper Methods
Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

template<typename ValueType>
Vector2 operator*(const Vector2& lhs, ValueType value)
{
	return { lhs.x * value, lhs.y * value };
}

template<typename ValueType>
Vector2 operator/(const Vector2& lhs, ValueType value)
{
	return { lhs.x / value, lhs.y / value };
}


void operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

void operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
}



/***************************/

//Raylib Viewport Utils

void ViewPort::drawPoint(Vertex2 vertex)
{
	DrawPixel(vertex.x, vertex.y, WHITE);
}

void ViewPort::drawLine(Vertex2 startPoint, Vertex2 endPoint)
{
}


Vector2 ViewPort::GetNormalizedMousePosition() const
{
	return Vec2ToPixel(GetMousePosition());
}

Vector2 ViewPort::Vec2ToPixel(const Vector2& vertex) const
{
	Vector2 pixelVertex = vertex - camera.offset;
	pixelVertex += (camera.target * (camera.zoom - 1));
	pixelVertex = pixelVertex / camera.zoom;

	return pixelVertex;
}

bool ViewPort::onMouseScrolled(MouseScrolledEvent& event)
{
	Vector2 newTarget = GetNormalizedMousePosition();
	const float MAX_ZOOM = 3;
	camera.zoom += event.GetYOffset() * 0.05f;
	bool clipped = false;
	if (camera.zoom >= MAX_ZOOM)
	{
		camera.zoom = MAX_ZOOM;

		clipped = true;
	}
	if (camera.zoom <= 1)
	{
		camera.zoom = 1;
		clipped = true;
	}
	if (!clipped)
		camera.target = newTarget;
	return false;
}

bool ViewPort::onMouseMoved(MouseMovedEvent& event)
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();
	Vector2 vertexA = Vector2{ event.GetX(), event.GetY() } - camera.offset;
	Vector2 vertexB = camera.target;

	Vector2 vec = vertexB - vertexA;
	double mag = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (fabs(vertexA.x - vertexB.x) > screenWidth / 3 ||
		fabs(vertexA.y - vertexB.y) > screenHeight / 3)
	{
		float maxX = screenWidth / 2;
		float maxY = screenHeight / 2;
		float panFactor = 0.04 * camera.zoom;
		float xOffset = camera.target.x - (vec.x > 0 ? panFactor : -panFactor);
		float yOffset = camera.target.y - (vec.y > 0 ? panFactor : -panFactor);
		if (fabs(xOffset) < maxX)
			camera.target.x = xOffset;
		if (fabs(xOffset) < maxY)
			camera.target.y = yOffset;
	}
	
	return false;
}

bool ViewPort::onMousePressed(MouseButtonPressedEvent& event)
{
	Vector2 vertex = Vector2{ (float)event.GetMousePosition().x, (float)event.GetMousePosition().y };
	vertex -= camera.offset;
	vertex += (camera.target * (camera.zoom - 1));
	vertex = vertex / camera.zoom;

	return false;
}

void ViewPort::setup()
{
	const int screenWidth = 1024;
	const int screenHeight = 768;

	camera.target = { 0 };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	InitWindow(screenWidth, screenHeight, "Quill");
}

void ViewPort::draw()
{
	BeginDrawing();
	BeginMode2D(camera);
	ClearBackground(DARKGRAY);
	for(auto& entity: m_entities)
	{
		entity.second->Render();
	}
	EndMode2D();
	EndDrawing();
}

/***************************/

ViewPort::ViewPort()
{
	MouseScrollCallback = new EventCallback<ViewPort, MouseScrolledEvent>(this, &ViewPort::onMouseScrolled);
	FetchEventSystem().RegisterMouseScrolled(*MouseScrollCallback);
	MouseMoveCallback = new EventCallback<ViewPort, MouseMovedEvent>(this, &ViewPort::onMouseMoved);
	FetchEventSystem().RegisterMouseMovedEvent(*MouseMoveCallback);
	MousePressedCallback = new EventCallback<ViewPort, MouseButtonPressedEvent>(this, &ViewPort::onMousePressed);
	FetchEventSystem().RegisterMouseButtonPressedEvent(*MousePressedCallback);

	m_renderer = new Renderer(*this);
}

ViewPort::~ViewPort()
{
	FetchEventSystem().Unregister(MouseScrollCallback);
	FetchEventSystem().Unregister(MouseMoveCallback);
	FetchEventSystem().Unregister(MousePressedCallback);
}

void ViewPort::Attach(DisplayEntity& entity)
{
	auto itr = m_entities.find(entity.GetShapeId());
	if (itr != m_entities.end());
	{
		Detach(entity);
	}
	m_entities[entity.GetShapeId()] = &entity;
}

void ViewPort::Detach(DisplayEntity& entity)
{
	ShapeId id = entity.GetShapeId();
	auto itr = m_entities.find(entity.GetShapeId());
	if (itr != m_entities.end())
	{
		delete itr->second;
		itr->second = nullptr;
	}
	m_entities.erase(id);
}

void ViewPort::DetachByShapeId(ShapeId id)
{
	m_entities.erase(id);
}

void ViewPort::DetachByDisplayId(DisplayId id)
{
	//Not very efficient search
	for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
	{
		if (itr->second->GetDisplayId() == id)
		{
			m_entities.erase(itr);
			break;
		}
	}
}

DisplayEntity& ViewPort::GetEntityByDisplayId(DisplayId id)
{
	for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
	{
		if (itr->second->GetDisplayId() == id)
		{
			return *(itr->second);
		}
	}
	throw std::exception("Invalid Display Id provided.");
}

DisplayEntity& ViewPort::GetEntityByShapeId(ShapeId id)
{
	if (m_entities.find(id) == m_entities.end())
		throw std::exception("Invalid Display Id provided.");
	return *m_entities[id];
}

IViewPort& FetchViewPort()
{
	static ViewPort vp;
	return vp;
}
