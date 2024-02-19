#include "Vector2.h"
#include <cmath>


namespace obvl
{
	Vector2::Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2(const Vector2& other)
	{
		x = other.x;
		y = other.y;
	}

	Vector2::~Vector2()
	{
	}

	Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	Vector2 operator*(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x * right.x, left.y * right.y);
	}

	Vector2 operator/(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x / right.x, left.y / right.y);
	}

	Vector2 operator+(const Vector2& left, const float& right)
	{
		return Vector2(left.x + right, left.y + right);
	}

	bool Vector2::operator==(const Vector2& other)
	{
		return x == other.x && y == other.y;
	}

	bool Vector2::operator!=(const Vector2& other)
	{
		return x != other.x || y != other.y;
	}

	float Vector2::Magnitude()
	{
		return sqrt(x * x + y * y);
	}

	Vector2 Vector2::Normalize()
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	float Vector2::Dot(const Vector2& other)
	{
		return x * other.x + y * other.y;
	}

	float Vector2::Distance(const Vector2& other)
	{
		float a = x - other.x;
		float b = y - other.y;
		return sqrt(a * a + b * b);
	}




}