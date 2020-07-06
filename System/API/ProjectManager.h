#pragma once
#include <vector>

class Project;
class ProjectManager
{
protected:
	ProjectManager();

public: 
	Project& GetActiveProject();

	const std::vector<Project>& GetAllProjects();

	Project& CreateNewProject();

	friend ProjectManager& FetchProjectManager();

private:
	static ProjectManager* Instance;

	Project* m_activeProject;
	std::vector<Project> m_projects;
};

ProjectManager& FetchProjectManager();

