#pragma once
#include <map>
#include "Quill/API/ViewPort.h"
#include "Core/API/Shape.h"
#include "raylib.h"
#include "Core/Events/EventSystem.h"

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

private:
	void drawPoint(Vertex2 vertex);
	void drawLine(Vertex2 startPoint, Vertex2 endPoint);
	Vector2 GetNormalizedMousePosition() const;
	Vector2 Vec2ToPixel(const Vector2& vertex) const;

	bool onMouseScrolled(MouseScrolledEvent& event);
	bool onMouseMoved(MouseMovedEvent& event);
	bool onMousePressed(MouseButtonPressedEvent& event);


private:
	std::map<ShapeId,DisplayEntity*> m_entities;
	Camera2D camera = {0};
	IRenderer* m_renderer;

	//Event Delegates
	IEventCallback* MouseScrollCallback;
	IEventCallback* MouseMoveCallback;
	IEventCallback* MousePressedCallback;
};