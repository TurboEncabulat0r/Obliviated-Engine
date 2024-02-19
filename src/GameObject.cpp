#include "GameObject.h"

namespace obvl
{
	GameObject::GameObject()
	{
	}

	GameObject::GameObject(Vector2 position, Vector2 size, float rotation)
	{
		this->position = position;
		this->size = size;
		this->rotation = rotation;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Move(Vector2 position)
	{
		this->position = position;
	}

	void GameObject::Rotate(float rotation)
	{
		this->rotation = rotation;
	}

	void GameObject::SetPosition(Vector2 position)
	{
		this->position = position;
	}

	void GameObject::SetSize(Vector2 size)
	{
		this->size = size;
	}

	void GameObject::SetRotation(float rotation)
	{
		this->rotation = rotation;
	}

	void GameObject::addComponent(Component* component)
	{
		components.push_back(component);
	}

	void GameObject::removeComponent(Component* component)
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (components[i] == component)
			{
				components.erase(components.begin() + i);
				break;
			}
		}
	}

	void GameObject::Update()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->Update();
		}
	}

	void GameObject::Start()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->Start();
		}
	}

	void GameObject::Draw()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnDraw();
		}
	}

	void GameObject::OnGUI()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnGUI();
		}
	}

	void GameObject::Enable()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnEnable();
		}
	}

	void GameObject::Disable()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnDisable();
		}
	}

	void GameObject::Destroy()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnDestroy();
		}
	}

	void GameObject::DestroyAllComponents()
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->OnDestroy();
		}
		components.clear();
	}

	void GameObject::DestroyComponent(Component* component)
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (components[i] == component)
			{
				components[i]->OnDestroy();
				components.erase(components.begin() + i);
				break;
			}
		}
	}

	void GameObject::DestroyComponent(int index)
	{
		components[index]->OnDestroy();
		components.erase(components.begin() + index);
	}
}