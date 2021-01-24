#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>

#include "Constants.h"
#include "Game.h"

int main(int argc, char* argv[]) 
{
    // setup Lua
    //sol::state lua;// create a lua state
    //lua.open_libraries(sol::lib::base, sol::lib::string); // specifying list of libs that we can use
    
    
    // create instance of game
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Shutdown();

    return 0;
}
