#include <algorithm>
#include <fstream>
#include "RenderingEngine/API/Commons.h"
#include "API/DisplayEntity.h"
#include "ViewPort.hxx"
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
		m_renderer = new Renderer(*this);
	}

	ViewPort::~ViewPort()
	{
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
		Vertex2 target = { 0, 0 };
		Vertex2 offset = { screenWidth / 2.0f, screenHeight / 2.0f };

		m_camera.Reset(target, offset);

		SetConfigFlags(ConfigFlag::FLAG_WINDOW_RESIZABLE);
		InitWindow(screenWidth, screenHeight, "Quill");
		SetWindowPosition(0, 40);
		SetExitKey(KEY_GRAVE);
		SetTargetFPS(60);
	}

	void ViewPort::draw()
	{
		while (!WindowShouldClose())
		{
			handleEvents();
			BeginDrawing();
			BeginMode2D(m_camera.GetCamera());
			ClearBackground(DARKGRAY);

			const int screenWidth = GetScreenWidth();
			const int screenHeight = GetScreenHeight();

			for (auto& entity : m_entities)
			{
				entity.second->Render();
			}
			EndMode2D();
			drawInterface();
			EndDrawing();
		}
		CloseWindow();
	}

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
		auto pixel = m_camera.GetScreenToWorld({ windowPoint.x, windowPoint.y });
		return MousePosition({ pixel.x, pixel.y });
	}
}