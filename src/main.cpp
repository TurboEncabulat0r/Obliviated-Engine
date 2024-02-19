#include "engine.h"

int main(int, char**)
{
  
    obvl::Engine engine = obvl::Engine();

    engine.setFramerateLimit(60);

    engine.runSyncronous();

    return 0;
}