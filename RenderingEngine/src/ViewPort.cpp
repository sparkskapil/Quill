#include <algorithm>
#include <fstream>
#include "RenderingEngine/API/Commons.h"
#include "API/DisplayEntity.h"
#include "ViewPort.hxx"
#include "SimpleEntity.hxx"
#include "Core/src/Line.hxx"
#include "Renderer.hxx"
#include <future>

using namespace EventSystem;
auto& eventSystem = FetchEventSystem();

IViewPort& FetchViewPort()
{
	static ViewPort vp;
	return vp;
}

IRenderer& FetchRenderer(IViewPort& vp)
{
	static Renderer renderer(vp);
	return renderer;
}

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
	Detach(entity);
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


void ViewPort::setup()
{
	const int screenWidth = 1920;
	const int screenHeight = 990;

	camera.target = { 0 };
	camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	InitWindow(screenWidth, screenHeight, "Quill");
	SetWindowPosition(0, 40);
	SetExitKey(KEY_GRAVE);

	/*auto mWidth = GetMonitorWidth(0);
	auto mHeight = GetMonitorHeight(0);
	auto mpWidth = GetMonitorPhysicalWidth(0);
	auto mpHeight = GetMonitorPhysicalHeight(0);

	dp = round(mpWidth*1000.0 / mWidth) / 1000;

	for (int i = 0; i < std::max(GetScreenWidth(), GetScreenHeight()); i++)
	{
		int mm = round(dp * i);
		if (millimeters.find(mm) == millimeters.end())
		{
			millimeters.insert(mm);
		}
	}*/

}

void ViewPort::draw()
{
	while (!WindowShouldClose())
	{
		handleEvents();
		BeginDrawing();
		BeginMode2D(camera);
		ClearBackground(DARKGRAY);
		for (auto& entity : m_entities)
		{
			entity.second->Render();
		}
		EndMode2D();
		EndDrawing();
	}
	CloseWindow();

	/*BeginDrawing();

	for (auto& mm : millimeters)
	{
		auto len = 15.0f;
		auto offset = 40.0f;
		if ((mm) % 10 == 0)
			len = 30.0f;

		int pixel = mm / dp;
		if (pixel <= GetScreenWidth())
			DrawLine(int(mm / dp) + offset, 0, int(mm / dp) + offset, 0 + len, RAYWHITE);
		if (pixel <= GetScreenHeight())
			DrawLine(0, offset + int(mm / dp), 0 + len, offset + int(mm / dp), RAYWHITE);
	}
	EndDrawing();*/
}



/* ==================================================================================================== */
// Event Dispatcher

void ViewPort::handleEvents()
{
	this->handleMouseEvents();
}

void ViewPort::handleMouseEvents()
{
	static MousePosition oldMousePosition;
	auto mousePosition = ToMousePosition(GetMousePosition());

	if (oldMousePosition != mousePosition)
	{
		MouseMovedEvent mmEvent(mousePosition.x, mousePosition.y);
		eventSystem.raiseEvent(mmEvent);
	}

	if (IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)) {
		MouseButtonPressedEvent mbpEvent(MouseCode::LEFT, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}
	if (IsMouseButtonPressed(MouseButton::MOUSE_MIDDLE_BUTTON)) {
		MouseButtonPressedEvent mbpEvent(MouseCode::MIDDLE, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}
	if (IsMouseButtonPressed(MouseButton::MOUSE_RIGHT_BUTTON)) {
		MouseButtonPressedEvent mbpEvent(MouseCode::RIGHT, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}

	if (IsMouseButtonReleased(MouseButton::MOUSE_LEFT_BUTTON)) {
		MouseButtonReleasedEvent mbpEvent(MouseCode::LEFT, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}
	if (IsMouseButtonReleased(MouseButton::MOUSE_MIDDLE_BUTTON)) {
		MouseButtonReleasedEvent mbpEvent(MouseCode::MIDDLE, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}
	if (IsMouseButtonReleased(MouseButton::MOUSE_RIGHT_BUTTON)) {
		MouseButtonReleasedEvent mbpEvent(MouseCode::RIGHT, mousePosition);
		eventSystem.raiseEvent(mbpEvent);
	}

	int mouseWheelMovement = GetMouseWheelMove();
	if (mouseWheelMovement != 0)
	{
		MouseScrolledEvent msEvent(0, mouseWheelMovement);
		eventSystem.raiseEvent(msEvent);
	}
}


/* ==================================================================================================== */
// Utilities

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


/* ==================================================================================================== */
//Event handlers

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
	Vector2 vertexA = Vector2{ event.GetX(), event.GetY() } -camera.offset;
	Vector2 vertexB = camera.target;

	Vector2 vec = vertexB - vertexA;
	double mag = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (fabs(vertexA.x - vertexB.x) > screenWidth / 3 ||
		fabs(vertexA.y - vertexB.y) > screenHeight / 3)
	{
		float maxX = screenWidth / 2.0f;
		float maxY = screenHeight / 2.0f;
		float panFactor = 0.04f * camera.zoom;
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
	if (event.GetMouseButton() == MouseCode::RIGHT)
	{
		auto screenBuffer = GetScreenData();
		return false;
	}

	Vector2 vertex = Vector2{ (float)event.GetMousePosition().x, (float)event.GetMousePosition().y };
	vertex -= camera.offset;
	vertex += (camera.target * (camera.zoom - 1));
	vertex = vertex / camera.zoom;

	return false;
}

MousePosition ViewPort::WindowPointToPixel(MousePosition& windowPoint)
{
	auto pixel = Vec2ToPixel({ windowPoint.x, windowPoint.y });
	return MousePosition({ pixel.x, pixel.y });
}
