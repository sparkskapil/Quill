#pragma once
#include "Core/API/Renderer.h"
#include "Core/API/Vertex2.h"

#include "Quill/API/DisplayEntity.h"
class IViewPort;

class Renderer : public IRenderer
{

public:
	Renderer(IViewPort &viewPort);

	virtual void draw(const std::vector<Vertex2>& vertices, ShapeId id, DrawModes mode = DrawModes::DRAWN) override;
	virtual void clear(ShapeId id) override;

private:
	IViewPort* m_vp;

};