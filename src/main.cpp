#include <SDL2/SDL.h>
#include "window.h"
#include "board.h"
#include "graphics_context.h"

int main(int argc, char* args[])
{
    GraphicsContext context("test", 400, 400, "resources/");
    Window window(context);
    Board board(context);

    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
            board.onEvent(windowEvent);
        }

        window.draw(board);
        SDL_Delay(1000 / 60);
    }

    return EXIT_SUCCESS;
}
