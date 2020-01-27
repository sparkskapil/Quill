#pragma once
#include "API/DisplayEntity.h"
#include "Core/API/Renderer.h"

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
};

IViewPort& FetchViewPort();