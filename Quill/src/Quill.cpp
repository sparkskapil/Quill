#include "RenderingEngine/API/ViewPort.h"
#include "System/API/ProjectManager.h"

using namespace RenderingEngine;
int main(void)
{
	FetchViewPort().setup();
	FetchProjectManager().CreateNewProject();
	FetchViewPort().draw();
	return 0;
}

