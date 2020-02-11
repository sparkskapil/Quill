#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>

#include "raylib.h"
#include "EventSystem/API/EventSystem.h"

namespace {

	//Raylib Global Helper Methods
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	template<typename ValueType>
	Vector2 operator*(const Vector2& lhs, ValueType value)
	{
		return { lhs.x * value, lhs.y * value };
	}

	template<typename ValueType>
	Vector2 operator/(const Vector2& lhs, ValueType value)
	{
		return { lhs.x / value, lhs.y / value };
	}


	void operator+=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	void operator-=(Vector2& lhs, const Vector2& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	MousePosition ToMousePosition(const Vector2& rhs)
	{
		return MousePosition({ rhs.x, rhs.y });
	}
}