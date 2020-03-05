#pragma once

#include "Core/API/QuillTypes.h"
#include "RenderingEngine/API/ExportSym.h"
#include "EventSystem/API/EventSystem.h"

class DisplayEntity;
class IRenderer;

class IViewPort
{
public:
	virtual void Attach(DisplayEntity& entity) = 0;
	virtual void Detach(DisplayEntity& entity) = 0;

	virtual void DetachByShapeId(ShapeId id) = 0;
	virtual void DetachByDisplayId(DisplayId id) = 0;
	
	virtual DisplayEntity& GetEntityByDisplayId(DisplayId id) = 0;
	virtual DisplayEntity& GetEntityByShapeId(ShapeId id) = 0;

	virtual void setup() = 0;
	virtual void draw() = 0;

	virtual void handleEvents() = 0;
	virtual void* GetFrameBuffer(int& width, int& height) = 0;

	virtual MousePosition WindowPointToPixel(MousePosition& windowPoint) = 0;
};

DLLEXPORT IViewPort& FetchViewPort();
DLLEXPORT IRenderer& FetchRenderer(IViewPort&);
