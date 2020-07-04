#include "engine/core/Engine.h"

int main(void)
{
    // Engine engine = Engine(500, 500, "Snek");
    Engine::GetInstance()->MainLoop();

    return 0;
}