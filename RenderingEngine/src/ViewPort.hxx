#pragma once
#include <map>
#include "API/ViewPort.h"
#include "Core/API/Shape.h"
#include "raylib.h"
#include "EventSystem/API/EventSystem.h"

//Raylib ViewPort Class
class ViewPort :public IViewPort
{
public:
	ViewPort();
	~ViewPort();

	virtual void Attach(DisplayEntity& entity) override;
	virtual void Detach(DisplayEntity& entity) override;
	virtual void DetachByShapeId(ShapeId id) override;
	virtual void DetachByDisplayId(DisplayId id) override;
	virtual DisplayEntity& GetEntityByShapeId(ShapeId id) override;
	virtual DisplayEntity& GetEntityByDisplayId(DisplayId id) override;

	virtual void setup() override;
	virtual void draw() override;
	virtual void initInterface() override;
	virtual void drawInterface() override;

	virtual void handleEvents() override;
	virtual MousePosition WindowPointToPixel(const MousePosition& windowPoint) override;

private:
	void handleMouseEvents();

	Vector2 GetNormalizedMousePosition() const;
	Vector2 Vec2ToPixel(const Vector2& vertex) const;

	bool onMouseScrolled(MouseScrolledEvent& event);
	bool onMouseMoved(MouseMovedEvent& event);
	bool onMousePressed(MouseButtonPressedEvent& event);
	bool onMouseReleased(MouseButtonReleasedEvent& event);

private:
	std::map<ShapeId,DisplayEntity*> m_entities;
	Camera2D camera = {0}; 
	IRenderer* m_renderer;

	bool panMode = false;
	Vector2 panStart = { -1,-1 };

	//Event Delegates
	IEventCallback* MouseScrollCallback;
	IEventCallback* MouseMoveCallback;
	IEventCallback* MousePressedCallback;
	IEventCallback* MouseReleasedCallback;

};