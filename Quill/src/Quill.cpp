#include "RenderingEngine/API/ViewPort.h"
#include "System/API/Project.h"

int main(void)
{
	FetchViewPort().setup();
	Project project;
	FetchViewPort().draw();
	return 0;
}

