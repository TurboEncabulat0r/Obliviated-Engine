#pragma once
#include "definition.h"


namespace obvl 
{
	void HandleKeyDown(int key);

	void HandleKeyUp(int key);

	void HandleMouseButtonDown(int button);

	void HandleMouseButtonUp(int button);

	void HandleMouseMove(int x, int y);

	void HandleMouseWheel(int delta);
}