#pragma once
#include "Core/Events/Event.h"
#include "Core/Events/MouseEvent.h"
class IEventCallback
{
public:
	virtual bool operator() (Event&) = 0; 
	virtual bool operator == (IEventCallback* other) = 0;

	operator void* () = delete;
	operator void () = delete;
};

template< typename T, typename EventClass >
class EventCallback : public IEventCallback
{
public:
	EventCallback(T* instance, bool (T::* function)(EventClass&))
		: instance(instance), function(function) {}
	virtual bool operator () (Event& e) override { 
		EventClass& event = *static_cast<EventClass*>(&e);
		return (instance->*function)(event); 
	}

	virtual bool operator == (IEventCallback* other) override
	{
		EventCallback* otherEventCallback = dynamic_cast < EventCallback* > (other);
		if (otherEventCallback == nullptr)
			return false;

		return 	(this->function == otherEventCallback->function) &&
		(this->instance == otherEventCallback->instance);
	}

private:
	bool (T::* function)(EventClass&);
	T* instance;
};