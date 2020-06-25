#pragma once
#include "System/API/Tool.h"
#include "EventSystem/API/EventSystem.h"
#include "RenderingEngine/API/ViewPort.h"

class Project
{
public:
	Project();
	~Project();

	Project(Project&&);
	
	bool onDrawPoint(MouseButtonPressedEvent& event);
	bool WhileDrawing(MouseMovedEvent& event);

private:
	void RegisterEvents();

private:
	IEventCallback* m_MousePressedDelegate;
	IEventCallback* m_MouseMovedDelegate;
	RenderingEngine::IViewPort* m_vp;
	
	IShape* m_tmpShape;
	
	std::shared_ptr<ITool> m_tool = nullptr;

	IRenderer* m_Renderer;
};