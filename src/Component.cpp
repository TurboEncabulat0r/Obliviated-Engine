#include "Component.h"

namespace obvl
{
	Component::Component(GameObject* owner)
	{
		this->owner = owner;
	}

	Component::~Component()
	{
	}
}
