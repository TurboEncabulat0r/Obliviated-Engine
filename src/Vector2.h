#pragma once

#define VECTOR2_ZERO Vector2(0, 0)
#define VECTOR2_UP Vector2(0, 1)
#define VECTOR2_DOWN Vector2(0, -1)
#define VECTOR2_LEFT Vector2(-1, 0)
#define VECTOR2_RIGHT Vector2(1, 0)

namespace obvl
{

	class Vector2;


	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);

		Vector2(const Vector2& other);
		~Vector2();

		float x;
		float y;

		Vector2 operator+(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2 operator*(const Vector2& other);
		Vector2 operator/(const Vector2& other);

		Vector2 operator+(const float& other);
		Vector2 operator-(const float& other);
		Vector2 operator*(const float& other);
		Vector2 operator/(const float& other);

		Vector2 operator+=(const Vector2& other);
		Vector2 operator-=(const Vector2& other);
		Vector2 operator*=(const Vector2& other);
		Vector2 operator/=(const Vector2& other);

		Vector2 operator+=(const float& other);
		Vector2 operator-=(const float& other);
		Vector2 operator*=(const float& other);
		Vector2 operator/=(const float& other);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		float Magnitude();
		Vector2 Normalize();
		float Dot(const Vector2& other);
		float Distance(const Vector2& other);
	};
}