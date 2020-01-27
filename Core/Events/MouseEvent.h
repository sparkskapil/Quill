#pragma once
#include <sstream>
#include "Core/Events/Event.h"
#include "Core/API/Vertex2.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y) {}

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset) {}

	inline float GetXOffset() const { return m_XOffset; }
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
	inline MouseCode GetMouseButton() const { return m_Button; }
	inline Vertex2 GetMousePosition() const { return m_Position; }
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
	MouseButtonEvent(MouseCode button, Vertex2 position)
		: m_Button(button),m_Position(position) {}

	MouseCode m_Button;
	Vertex2 m_Position;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(MouseCode button, Vertex2 position)
		: MouseButtonEvent(button,position) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(MouseCode button, Vertex2 position)
		: MouseButtonEvent(button, position) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};