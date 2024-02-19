#pragma once
#include "Vector2.h"
#include "Component.h"


namespace obvl
{

	class Camera2D : public Component
	{
		public:
		Camera2D(GameObject* owner);
		~Camera2D();

		Vector2 position;
		Vector2 size;

		void Update();
		void Start();
		void OnDraw();
		void OnGUI();
		void OnEnable();
		void OnDisable();
		void OnDestroy();

		static void setMainCamera(Camera2D camera);

		static Camera2D getMainCamera();
	};

	extern Camera2D mainCamera;
}