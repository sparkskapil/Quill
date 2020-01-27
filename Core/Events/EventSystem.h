#pragma once
#include <set>
#include "Core/Events/Event.h"
#include "Core/Events/MouseEvent.h"
#include "Core/API/CoreSym.h"
#include "Core/Events/EventCallback.h"

typedef bool (*EventHandler)(Event&);
typedef bool (*MouseButtonPressedEventHandler)(MouseButtonPressedEvent&);
typedef bool (*MouseButtonReleasedEventHandler)(MouseButtonReleasedEvent&);
typedef bool (*MouseMovedEventHandler)(MouseMovedEvent&);
typedef bool (*MouseScrolledEventHandler)(MouseScrolledEvent&);

struct Delegate 
{
	void* function;

	Delegate(void* func)
	{
		function = func;
	}

	bool operator()(Event& event)
	{
		return static_cast<EventHandler>(function)(event);
	}
};

class MODELAPI EventSystem 
{
public:
	void RegisterMouseButtonPressedEvent(MouseButtonPressedEventHandler);
	void RegisteredMouseButtonReleasedEvent(MouseButtonReleasedEventHandler);
	void RegisterMouseMovedEvent(MouseMovedEventHandler);
	void RegisterMouseScrolled(MouseScrolledEventHandler);

	void RegisterMouseButtonPressedEvent(IEventCallback&);
	void RegisteredMouseButtonReleasedEvent(IEventCallback&);
	void RegisterMouseMovedEvent(IEventCallback&);
	void RegisterMouseScrolled(IEventCallback&);

	void raiseEvent(Event& event);
	
	//Should not be called from an EventHandler.
	void Unregister(Delegate* handler);
	void Unregister(IEventCallback* callback);

private:
	void UnregisterEventHandler(void*);
	void UnregisterEventCallback(IEventCallback& callback);

private:
	void RegisterCallback(EventType type, IEventCallback& callback);
	
	std::map<EventType, std::set<void*>> m_handlers;
	std::map<EventType, std::vector<IEventCallback*>> m_delegates;
};

MODELAPI EventSystem& FetchEventSystem();
