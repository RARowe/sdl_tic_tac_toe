#include <SDL2/SDL.h>
#include <list>
#include "graphics_context.h"

#ifndef SHAPE_TEXTURE_FACTORY_H
#define SHAPE_TEXTURE_FACTORY_H 
class ShapeTextureFactory
{
    public:
        ShapeTextureFactory(GraphicsContext& context);
        ~ShapeTextureFactory();
        SDL_Texture* getX();
        SDL_Texture* getO();
    private:
        std::list<SDL_Texture*> _xs;
        std::list<SDL_Texture*> _os;
};
#endif
