#include "raylib.h"
#include <vector>
#include "Quill/API/ViewPort.h"

#include "Core/Events/EventSystem.h"
#include "Core/Events/MouseEvent.h"

EventSystem& eventSystem = FetchEventSystem();

Vertex2 ToVertex(const Vector2& rhs)
{
	return Vertex2(rhs.x, rhs.y);
}

bool MousePressed(MouseButtonPressedEvent& e)
{
	auto name = e.GetName();
	auto button = e.GetMouseButton();
	return true;
}

void CheckForMouseEvents()
{
	static Vertex2 oldMousePosition = { 0 };
	auto mousePosition = ToVertex(GetMousePosition());
	
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
int main(void)
{
	FetchViewPort().setup();
	while (!WindowShouldClose())
	{
		CheckForMouseEvents();
		FetchViewPort().draw();
	}
	CloseWindow();
	return 0;
}

