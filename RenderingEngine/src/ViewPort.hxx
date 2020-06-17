#pragma once
#include <map>
#include "API/ViewPort.h"
#include "Core/API/Shape.h"
#include "raylib.h"
#include "EventSystem/API/EventSystem.h"
#include <src\Camera2D.hxx>

namespace RenderingEngine
{
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

	private:
		std::map<ShapeId, DisplayEntity*> m_entities;
		QuillCamera2D m_camera;

		IRenderer* m_renderer;
	};
}