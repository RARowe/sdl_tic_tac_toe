#include <SDL2/SDL.h>
#include "drawable.h"
#include "shape_texture_factory.h"
#include "enums.h"

#ifndef BOARD_SPACE_H 
#define BOARD_SPACE_H 
class BoardSpace : public Drawable
{
    public:
        BoardSpace(int x, int y, int length, ShapeTextureFactory* factory);
        void draw(SDL_Renderer* renderer);
        void click(SpaceState state);
        SpaceState getState();
        void reset();
    private:
        ShapeTextureFactory* _factory;
        SDL_Rect _rect;
        SDL_Texture* _texture;
        SpaceState _state;
};
#endif
