#pragma once
#include "Tool.h"
#include "EventSystem/API/EventSystem.h"
#include "RenderingEngine/API/ViewPort.h"

class Project
{
public:
	Project();
	~Project();
	bool onDrawPoint(MouseButtonPressedEvent& event);
	bool WhileDrawing(MouseMovedEvent& event);

private:
	IEventCallback* m_MousePressedDelegate;
	IEventCallback* m_MouseMovedDelegate;
	IViewPort* m_vp;
	
	IShape* m_tmpShape;
	
	LineTool tool;
	IRenderer* m_Renderer;
};