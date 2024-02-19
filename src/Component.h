#pragma once
#include "definition.h"
#include "Vector2.h"
#include "GameObject.h"
#include <string>


namespace obvl
{
	class Component
	{

	public:
		GameObject* owner;
		Component(GameObject* owner);
		~Component();

		std::string name;

		virtual void Update() = 0;
		virtual void Start() = 0;
		virtual void OnDraw() = 0;
		virtual void OnGUI() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnDestroy() = 0;
	};
}