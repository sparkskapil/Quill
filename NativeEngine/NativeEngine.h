#pragma once
using namespace System;
#include "RenderingEngine/API/ViewPort.h"

namespace NativeEngine {
	
	public ref class WpfViewPort
	{
		IViewPort* vp;

	public:
		WpfViewPort();
		void Attach(DisplayEntity& entity);
		void Detach(DisplayEntity& entity);

		void DetachByShapeId(ShapeId id);
		void DetachByDisplayId(DisplayId id);

		DisplayEntity& GetEntityByDisplayId(DisplayId id);
		DisplayEntity& GetEntityByShapeId(ShapeId id);

		void setup();
		void draw();
		int32_t* GetFramBuffer(Int32% width, Int32% height);

		void handleEvents();
		MousePosition WindowPointToPixel(MousePosition& windowPoint);
	};
}
