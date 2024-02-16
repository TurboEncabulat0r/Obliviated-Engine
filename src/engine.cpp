#include "engine.h"


namespace obvl
{



	class Engine {
	public:
		Engine(char* windowName);

		static Engine* instance;

		float getFramerate();

		float getFrameTime();

		void setFramerateLimit(float fps);

		
		
	};

}