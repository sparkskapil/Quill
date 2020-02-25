#pragma once
#pragma warning (disable: 4251)

#include <set>
#include "EventSystem/API/Event.h"
#include "EventSystem/API/MouseEvent.h"
#include "EventSystem/API/EventCallback.h"

namespace EventSystem
{
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

	class DLLAPI EventSystem
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
		void RegisterCallback(EventType type, IEventCallback& callback);

	private:
		std::map<EventType, std::set<void*>> m_handlers;
		std::map<EventType, std::vector<IEventCallback*>> m_delegates;
	};
 
	DLLAPI EventSystem& FetchEventSystem();
}
