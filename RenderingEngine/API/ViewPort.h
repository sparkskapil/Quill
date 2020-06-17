#pragma once

#include "Core/API/QuillTypes.h"
#include "RenderingEngine/API/ExportSym.h"
#include "EventSystem/API/EventSystem.h"

class IRenderer;

namespace RenderingEngine
{
	class DisplayEntity;

	class IViewPort
	{
	public:
		virtual ~IViewPort() = default;

		virtual void Attach(DisplayEntity& entity) = 0;
		virtual void Detach(DisplayEntity& entity) = 0;

		virtual void DetachByShapeId(ShapeId id) = 0;
		virtual void DetachByDisplayId(DisplayId id) = 0;

		virtual DisplayEntity& GetEntityByDisplayId(DisplayId id) = 0;
		virtual DisplayEntity& GetEntityByShapeId(ShapeId id) = 0;

		virtual void setup() = 0;
		virtual void draw() = 0;
		virtual void initInterface() = 0;
		virtual void drawInterface() = 0;

		virtual void handleEvents() = 0;

		virtual MousePosition WindowPointToPixel(const MousePosition& windowPoint) = 0;
	};
	DLLEXPORT RenderingEngine::IViewPort& FetchViewPort();
	DLLEXPORT IRenderer& FetchRenderer(RenderingEngine::IViewPort&);
}
