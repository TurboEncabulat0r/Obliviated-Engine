#pragma once
#include "Vector2.h"
#include "Component.h"
#include <vector>
#include <string>
#include "rendering.h"

namespace obvl
{
	class GameObject
	{
		std::vector<Component*> components;
	public:
		Vector2 position;
		Vector2 size;

		Sprite sprite;

		float rotation;

		std::string name;
		
		GameObject();
		GameObject(Vector2 position, Vector2 size, float rotation);

		~GameObject();

		void Move(Vector2 position);

		void Rotate(float rotation);

		void SetPosition(Vector2 position);

		void SetSize(Vector2 size);

		void SetRotation(float rotation);

		void addComponent(Component* component);

		void removeComponent(Component* component);

		void Update();

		void Start();

		void Draw();

		void OnGUI();

		void Enable();

		void Disable();

		void Destroy();

		void DestroyAllComponents();

		void DestroyComponent(Component* component);

		void DestroyComponent(int index);




	};

	void G_GetAllGameobjects(void*);

	void DrawGameObjectsGUI();
}