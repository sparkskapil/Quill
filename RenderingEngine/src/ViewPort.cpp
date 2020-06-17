#include <algorithm>
#include <fstream>
#include "RenderingEngine/API/Commons.h"
#include "API/DisplayEntity.h"
#include "ViewPort.hxx"
#include "SimpleEntity.hxx"
#include "Core/src/Line.hxx"
#include "Renderer.hxx"
#include <future>

namespace RayGUI
{
	// User Interface With RayRayGUI::Gui
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "vendor/raygui/src/raygui.h"

}
using namespace EventSystem;
auto& eventSystem = FetchEventSystem();


namespace RenderingEngine
{
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
		MouseReleasedCallback = new EventCallback<ViewPort, MouseButtonReleasedEvent>(this, &ViewPort::onMouseReleased);
		FetchEventSystem().RegisteredMouseButtonReleasedEvent(*MouseReleasedCallback);

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

		camera.target = { 0, 0 };
		camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		camera.rotation = 0.0f;
		camera.zoom = 1.0f;
		SetConfigFlags(ConfigFlag::FLAG_WINDOW_RESIZABLE);
		InitWindow(screenWidth, screenHeight, "Quill");
		SetWindowPosition(0, 40);
		SetExitKey(KEY_GRAVE);
		SetTargetFPS(60);

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

			const int screenWidth = GetScreenWidth();
			const int screenHeight = GetScreenHeight();
			DrawLine(camera.target.x, -screenHeight * 10, camera.target.x, screenHeight * 10, GREEN);
			DrawLine(-screenWidth * 10, camera.target.y, screenWidth * 10, camera.target.y, GREEN);

			for (auto& entity : m_entities)
			{
				entity.second->Render();
			}
			EndMode2D();
			drawInterface();
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
		return GetScreenToWorld2D(vertex, camera);
	}


	/* ==================================================================================================== */
	//Event handlers

	bool ViewPort::onMouseScrolled(MouseScrolledEvent& event)
	{
		const float MAX_ZOOM = 3;
		auto factor = event.GetYOffset() * 0.01f;
		auto zoom = camera.zoom + factor;

		auto oldWorldPosition = GetScreenToWorld2D(GetMousePosition(), camera);
		if (zoom > MAX_ZOOM)
			return false;
		if (zoom < 1)
			return false;
		camera.zoom = zoom;
		auto newWorldPosition = GetScreenToWorld2D(GetMousePosition(), camera);
		auto offset = camera.offset + newWorldPosition - oldWorldPosition;
		camera.offset = offset;
		return false;
	}

	bool ViewPort::onMouseMoved(MouseMovedEvent& event)
	{
		if (panMode)
		{
			auto pos = GetMousePosition();
			auto start = GetScreenToWorld2D(panStart, camera);
			auto end = GetScreenToWorld2D(pos, camera);
			auto panDistance = end - start;
			camera.target = camera.target - panDistance;
			panStart = pos;
		}
		return false;
	}

	bool ViewPort::onMousePressed(MouseButtonPressedEvent& event)
	{
		auto btn = event.GetMouseButton();
		if (MouseCode::RIGHT == btn)
		{
			panMode = true;
			panStart.x = event.GetMousePosition().x;
			panStart.y = event.GetMousePosition().y;
		}
		return false;
	}

	bool ViewPort::onMouseReleased(MouseButtonReleasedEvent& event)
	{
		auto btn = event.GetMouseButton();
		if (MouseCode::RIGHT == btn)
		{
			panMode = false;
			panStart.x = -1;
			panStart.y = -1;
		}
		return false;
	}

	void ViewPort::initInterface()
	{

	}

	void ViewPort::drawInterface()
	{
		RayGUI::GuiLock();
		RayGUI::GuiWindowBox(Rectangle({ 0,0, 1920, 60 }), "Tools");
		RayGUI::GuiButton(Rectangle({ 0,30, 40, 30 }), "Line");
		RayGUI::GuiButton(Rectangle({ 50,30, 40, 30 }), "Circle");
		RayGUI::GuiUnlock();
	}

	MousePosition ViewPort::WindowPointToPixel(const MousePosition& windowPoint)
	{
		auto pixel = GetScreenToWorld2D({ windowPoint.x, windowPoint.y }, camera);
		return MousePosition({ pixel.x, pixel.y });
	}
}