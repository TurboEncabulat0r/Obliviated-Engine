#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>

namespace obvl {
	class Serializeable {
	public:
		virtual void serialize(std::ofstream& out) = 0;
		virtual void deserialize(std::ifstream& in) = 0;
	};


}