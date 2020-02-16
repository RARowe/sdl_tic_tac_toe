#include <SDL2/SDL.h>
#include "shape_texture_factory.h"

ShapeTextureFactory::ShapeTextureFactory(GraphicsContext& context)
{
    const char* xs[] = { "x_1.png", "x_2.png", "x_3.png", "x_4.png", "x_5.png" };
    const char* os[] = { "o_1.png", "o_2.png", "o_3.png", "o_4.png", "o_5.png" };
    for (auto xFile : xs)
    {
        _xs.push_back(context.getTexture(xFile));
    }
    for (auto oFile : os)
    {
        _os.push_back(context.getTexture(oFile));
    }
}

ShapeTextureFactory::~ShapeTextureFactory()
{
    for (auto texture : _xs)
    {
        SDL_DestroyTexture(texture);
    }

    for (auto texture : _os)
    {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* ShapeTextureFactory::getX()
{
    SDL_Texture* texture = _xs.front();
    _xs.pop_front();
    _xs.push_back(texture);

    return texture;
}

SDL_Texture* ShapeTextureFactory::getO()
{
    SDL_Texture* texture = _os.front();
    _os.pop_front();
    _os.push_back(texture);
    return texture;
}
