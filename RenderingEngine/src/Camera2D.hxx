#pragma once
#include "Core/API/Vertex2.h"
#include "EventSystem/API/EventCallback.h"
#include "vendor/raylib/include/raylib.h"
#include "EventSystem/API/MouseEvent.h"

namespace RenderingEngine
{
	class QuillCamera2D 
	{
	public:
		QuillCamera2D(Vertex2 target = { 0,0 }, Vertex2 offset = { 0,0 }, float zoom = 1, float rotation = 0);
		void Reset(Vertex2 target = { 0,0 }, Vertex2 offset = { 0,0 }, float zoom = 1, float rotation = 0);

		~QuillCamera2D();

		Vertex2 GetScreenToWorld(Vertex2 screenPosition);
		Vertex2 GetWorldToScreen(Vertex2 worldPosition);
		const Camera2D& GetCamera();

		// Event Handlers
		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onMouseMoved(MouseMovedEvent& event);
		bool onMousePressed(MouseButtonPressedEvent& event);
		bool onMouseReleased(MouseButtonReleasedEvent& event);
	private:
		void RegisterEvents();
		void DeregisterEvents();

	private:
		Camera2D m_camera;
		bool m_panModeEnabled;
		Vector2 m_panStartPosition;

		IEventCallback* MouseScrollCallback;
		IEventCallback* MouseMoveCallback;
		IEventCallback* MousePressedCallback;
		IEventCallback* MouseReleasedCallback;

	};
}