#include "System/API/Project.h"
#include "System/API/Tool.h"

using namespace EventSystem;

auto& eventSystem = FetchEventSystem();

Project::Project()
{
	RegisterEvents();

	m_vp = &RenderingEngine::FetchViewPort();
	m_Renderer = &RenderingEngine::FetchRenderer(*m_vp);
	m_tmpShape = nullptr;
}

Project::~Project()
{
	eventSystem.Unregister(m_MousePressedDelegate);
	eventSystem.Unregister(m_MouseMovedDelegate);
	m_vp = nullptr;
}

Project::Project(Project&& project)
{
	RegisterEvents();
	m_vp = project.m_vp;
	m_Renderer = project.m_Renderer;
	m_tmpShape = project.m_tmpShape;

	project.m_vp = nullptr;
	project.m_Renderer = nullptr;
	project.m_tmpShape = nullptr;
}

bool Project::onDrawPoint(MouseButtonPressedEvent& event)
{
	if (event.GetMouseButton() != MouseCode::LEFT)
		return false;

	MousePosition pos = event.GetMousePosition();
	pos = m_vp->WindowPointToPixel(pos);

	if (!tool.IsDrawing())
		tool.BeginDrawing();

	tool.AddPoint({ pos.x, pos.y });

	if (!tool.IsDrawing())
	{
		auto shape = tool.GetLatestShape();
		if (shape)
		{
			shape->SetRenderer(m_Renderer);
			shape->Render();
		}
	}

	return false;
}

bool Project::WhileDrawing(MouseMovedEvent& event)
{
	if (!tool.IsDrawing())
	{
		if (m_tmpShape)
			delete m_tmpShape;
		m_tmpShape = nullptr;
		return false;
	}

	MousePosition pos(event.GetX(), event.GetY());
	pos = m_vp->WindowPointToPixel(pos);

	if (!m_tmpShape)
	{
		m_tmpShape = tool.GetCurrentShape()->clone();
		m_tmpShape->AddVertex({pos.x, pos.y});
	}
	m_tmpShape->ReplaceVertex(1,{ pos.x, pos.y });
	m_tmpShape->SetRenderer(m_Renderer);
	m_tmpShape->Render(DrawModes::DRAWING);
	return false;
}

void Project::RegisterEvents()
{
	m_MousePressedDelegate = new EventCallback<Project, MouseButtonPressedEvent>(this, &Project::onDrawPoint);
	eventSystem.RegisterMouseButtonPressedEvent(*m_MousePressedDelegate);

	m_MouseMovedDelegate = new EventCallback<Project, MouseMovedEvent>(this, &Project::WhileDrawing);
	eventSystem.RegisterMouseMovedEvent(*m_MouseMovedDelegate);
}