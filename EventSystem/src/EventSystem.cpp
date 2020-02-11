#include "EventSystem/API/EventSystem.h"
#include <assert.h>

bool isAlreadyRegistered(std::vector<IEventCallback*> dels, IEventCallback* callback)
{
	auto itr = std::find(dels.begin(), dels.end(), callback);
	if (itr != dels.end()) assert("Callback already registered.");
	return (itr != dels.end());
}
void EventSystem::RegisterMouseButtonPressedEvent(MouseButtonPressedEventHandler handler)
{
	m_handlers[EventType::MouseButtonPressed].emplace(handler);
}

void EventSystem::RegisteredMouseButtonReleasedEvent(MouseButtonReleasedEventHandler handler)
{
	m_handlers[EventType::MouseButtonReleased].emplace(handler);
}

void EventSystem::RegisterMouseMovedEvent(MouseMovedEventHandler handler)
{
	m_handlers[EventType::MouseMoved].emplace(handler);
}

void EventSystem::RegisterMouseScrolled(MouseScrolledEventHandler handler)
{
	m_handlers[EventType::MouseScrolled].emplace(handler);
}

void EventSystem::RegisterMouseButtonPressedEvent(IEventCallback& callback)
{
	RegisterCallback(EventType::MouseButtonPressed, callback);
}

void EventSystem::RegisteredMouseButtonReleasedEvent(IEventCallback& callback)
{
	RegisterCallback(EventType::MouseButtonReleased, callback);
}

void EventSystem::RegisterMouseMovedEvent(IEventCallback& callback)
{
	RegisterCallback(EventType::MouseMoved, callback);
}

void EventSystem::RegisterMouseScrolled(IEventCallback& callback)
{
	RegisterCallback(EventType::MouseScrolled, callback);
}

void EventSystem::UnregisterEventHandler(void* handler)
{
	for (auto& vHandler : m_handlers)
	{
		auto itr = vHandler.second.find(handler);
		if (itr != vHandler.second.end())
		{
			vHandler.second.erase(itr);
			break;
		}
	}
}

void EventSystem::UnregisterEventCallback(IEventCallback& callback)
{
	for (auto& itr : m_delegates)
	{
		auto cbToDelete = std::find(itr.second.begin(), itr.second.end(), &callback);
		if (cbToDelete != itr.second.end())
		{
			itr.second.erase(cbToDelete);
		}
	}
}

void EventSystem::RegisterCallback(EventType type, IEventCallback& callback)
{
	if (!isAlreadyRegistered(m_delegates[type], &callback))
		m_delegates[type].emplace_back(&callback);
}

void EventSystem::raiseEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	for (auto& vHandler : m_handlers[event.GetEventType()])
	{
		switch (event.GetEventType())
		{
		case EventType::MouseButtonPressed:
		{
			auto handler = static_cast<MouseButtonPressedEventHandler>(vHandler);
			dispatcher.Dispatch<MouseButtonPressedEvent>(handler);
			break;
		}
		case EventType::MouseButtonReleased:
		{
			auto handler = static_cast<MouseButtonReleasedEventHandler>(vHandler);
			dispatcher.Dispatch<MouseButtonReleasedEvent>(handler);
			break;
		}
		case EventType::MouseMoved:
		{
			auto handler = static_cast<MouseMovedEventHandler>(vHandler);
			dispatcher.Dispatch<MouseMovedEvent>(handler);
			break;
		}
		case EventType::MouseScrolled:
		{
			auto handler = static_cast<MouseScrolledEventHandler>(vHandler);
			dispatcher.Dispatch<MouseScrolledEvent>(handler);
			break;
		}
		default:
			break;

		}
	}

	for (auto& delegate : m_delegates[event.GetEventType()])
	{
		(*delegate)(event);
	}
}

void EventSystem::Unregister(Delegate* handler)
{
	UnregisterEventHandler(handler->function);
}

void EventSystem::Unregister(IEventCallback* callback)
{
	UnregisterEventCallback(*callback);
}

EventSystem& FetchEventSystem()
{
	static EventSystem eventSystem;
	return eventSystem;
}
