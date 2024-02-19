#pragma once
#include "Vector2.h"


namespace obvl
{

	class Camera2D
	{
	public:
		Vector2 position;
		Vector2 size;
		float rotation;
		float zoom;

		Camera2D();
		Camera2D(Vector2 position, Vector2 size, float rotation, float zoom);

		~Camera2D();

		void Move(Vector2 position);

		void Rotate(float rotation);

		void Zoom(float zoom);

		void SetPosition(Vector2 position);



	};
}