#include "System/API/ProjectManager.h"


ProjectManager& FetchProjectManager()
{
	if (ProjectManager::Instance == nullptr)
	{
		ProjectManager::Instance = new ProjectManager();
	}
	return *ProjectManager::Instance;
}

ProjectManager* ProjectManager::Instance = nullptr;

ProjectManager::ProjectManager(): m_activeProject(nullptr)
{
}

Project& ProjectManager::GetActiveProject()
{
	return *m_activeProject;
}

const std::vector<Project>& ProjectManager::GetAllProjects()
{
	return m_projects;
}

Project& ProjectManager::CreateNewProject()
{
	Project project;
	m_projects.emplace_back(std::move(project));
	m_activeProject = &m_projects.back();
	return m_projects.back();
}