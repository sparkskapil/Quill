#include "Camera2D.hxx"
#include "EventSystem/API/EventSystem.h"
#include "API/Commons.h"

using namespace EventSystem;

namespace RenderingEngine
{
	QuillCamera2D::QuillCamera2D(Vertex2 target, Vertex2 offset, float zoom, float rotation)
	{
		m_camera.offset = {offset.x,offset.y};
		m_camera.target = { target.x, target.y };
		m_camera.zoom = zoom;
		m_camera.rotation = rotation;

		RegisterEvents();
	}

	void QuillCamera2D::Reset(Vertex2 target, Vertex2 offset, float zoom, float rotation)
	{
		m_camera.offset = { offset.x,offset.y };
		m_camera.target = { target.x, target.y };
		m_camera.zoom = zoom;
		m_camera.rotation = rotation;
	}

	QuillCamera2D::~QuillCamera2D()
	{
		DeregisterEvents();
	}

	Vertex2 QuillCamera2D::GetScreenToWorld(Vertex2 screenPosition)
	{
		auto position = GetScreenToWorld2D({ screenPosition.x, screenPosition.y }, m_camera);
		return { position.x, position.y };
	}

	Vertex2 QuillCamera2D::GetWorldToScreen(Vertex2 worldPosition)
	{
		auto position = GetWorldToScreen2D({ worldPosition.x, worldPosition.y }, m_camera);
		return { position.x, position.y };
	}

	const Camera2D& QuillCamera2D::GetCamera()
	{
		return m_camera;
	}

	//============================================================================================================*/	
	//						EVENTS						*/
	//============================================================================================================*/
	bool QuillCamera2D::onMouseScrolled(MouseScrolledEvent& event)
	{
		const float MAX_ZOOM = 3;
		auto factor = event.GetYOffset() * 0.01f;
		auto zoom = m_camera.zoom + factor;

		auto oldWorldPosition = GetScreenToWorld2D(GetMousePosition(), m_camera);
		if (zoom > MAX_ZOOM)
			return false;
		if (zoom < 1)
			return false;
		m_camera.zoom = zoom;
		auto newWorldPosition = GetScreenToWorld2D(GetMousePosition(), m_camera);
		auto offset = m_camera.offset + (newWorldPosition - oldWorldPosition)*zoom;
		m_camera.offset = offset;
		return false;
	}

	bool QuillCamera2D::onMouseMoved(MouseMovedEvent& event)
	{
		if (m_panModeEnabled)
		{
			Vector2 position = { event.GetX(), event.GetY() };
			auto start = GetScreenToWorld2D(m_panStartPosition, m_camera);
			auto end = GetScreenToWorld2D(position, m_camera);
			auto panDistance = end - start;
			m_camera.target = m_camera.target - panDistance;
			m_panStartPosition = position;
		}
		return false;
	}

	bool QuillCamera2D::onMousePressed(MouseButtonPressedEvent& event)
	{
		auto btn = event.GetMouseButton();
		if (MouseCode::RIGHT == btn)
		{
			m_panModeEnabled = true;
			m_panStartPosition = { event.GetMousePosition().x, event.GetMousePosition().y };
		}
		return false;
	}

	bool QuillCamera2D::onMouseReleased(MouseButtonReleasedEvent& event)
	{
		auto btn = event.GetMouseButton();
		if (MouseCode::RIGHT == btn)
		{
			m_panModeEnabled = false;
			m_panStartPosition = { -1,1 };
		}
		return false;
	}


	void QuillCamera2D::RegisterEvents()
	{
		MouseScrollCallback = new EventCallback<QuillCamera2D, MouseScrolledEvent>(this, &QuillCamera2D::onMouseScrolled);
		FetchEventSystem().RegisterMouseScrolled(*MouseScrollCallback);
		MouseMoveCallback = new EventCallback<QuillCamera2D, MouseMovedEvent>(this, &QuillCamera2D::onMouseMoved);
		FetchEventSystem().RegisterMouseMovedEvent(*MouseMoveCallback);
		MousePressedCallback = new EventCallback<QuillCamera2D, MouseButtonPressedEvent>(this, &QuillCamera2D::onMousePressed);
		FetchEventSystem().RegisterMouseButtonPressedEvent(*MousePressedCallback);
		MouseReleasedCallback = new EventCallback<QuillCamera2D, MouseButtonReleasedEvent>(this, &QuillCamera2D::onMouseReleased);
		FetchEventSystem().RegisteredMouseButtonReleasedEvent(*MouseReleasedCallback);
	}

	void QuillCamera2D::DeregisterEvents()
	{
		FetchEventSystem().Unregister(MouseScrollCallback);
		FetchEventSystem().Unregister(MouseMoveCallback);
		FetchEventSystem().Unregister(MousePressedCallback);
		FetchEventSystem().Unregister(MouseReleasedCallback);
	}

	//============================================================================================================*/
}