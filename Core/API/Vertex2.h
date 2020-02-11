#pragma once
#include <initializer_list>

class Vertex2 {
public:
	float x;
	float y;

	inline Vertex2() : x(0.0), y(0.0) {}
	inline Vertex2(float _x, float _y) : x(_x), y(_y) {}
	inline Vertex2(std::initializer_list<float> list) : x(*list.begin()), y(*(list.begin() + 1)) {}

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