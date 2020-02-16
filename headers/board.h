#include <SDL2/SDL.h>
#include "board_space.h"
#include "enums.h"
#include "drawable.h"
#include "shape_texture_factory.h"
#include "graphics_context.h"

#ifndef BOARD_H 
#define BOARD_H 
class Board : public Drawable
{
    public:
        Board(GraphicsContext& context);
        ~Board();
        void draw(SDL_Renderer* renderer);
        void onEvent(SDL_Event& event);
    private:
        bool gameOver();
        void reset();
        bool _gameOver;
        SDL_Texture* _texture;
        SDL_Texture* _winTextures[8];
        WinLine _winLine;
        ShapeTextureFactory* _factory;
        BoardSpace* _spaces[3][3];
        Player _currentPlayer;
        int _spaceHeight;
        int _spaceWidth;
};
#endif
