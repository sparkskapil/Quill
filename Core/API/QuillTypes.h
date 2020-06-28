#pragma once

enum class DrawModes
{
	DRAWN,
	DRAWING,
	EDITING,
	SELECTED
};

enum class ShapeType
{
	Point,
	Line,
	Circle,
	Polygon
};

typedef size_t ShapeId;
typedef size_t DisplayId;