#include "core/Log.h"
#include "sandbox/Game.h"

int main()
{
    engine::Log::Info("Engine (Phase 2) initializing.");

    engine::Game game;
    game.Run();

    return 0;
}