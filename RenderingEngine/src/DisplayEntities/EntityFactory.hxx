#pragma once
#include "RenderingEngine/API/DisplayEntity.h"
#include "Core/API/Renderer.h"

namespace RenderingEngine
{
	class EntityGenerator
	{
	public:
		static DisplayEntity& CreateEntity(const RenderProps& shapeProps);

	private:
		static DisplayEntity& CreateLineEntity(const RenderProps& shapeProps);
		static DisplayEntity& CreateCircleEntity(const RenderProps& shapeProps);
	};
}