#pragma once
#include <initializer_list>

class Vertex2 {
public:
	double x;
	double y;

	inline Vertex2() : x(0.0), y(0.0) {}
	inline Vertex2(double _x, double _y) : x(_x), y(_y) {}
	inline Vertex2(std::initializer_list<double> list) : x(*list.begin()), y(*(list.begin() + 1)) {}

	inline bool operator==(const Vertex2& rhs) 
	{ 
		return this->x == rhs.x && this->y == rhs.y; 
	}
	inline bool operator!=(const Vertex2& rhs)
	{
		return this->x != rhs.x || this->y != rhs.y;
	}
	~Vertex2() = default;
};