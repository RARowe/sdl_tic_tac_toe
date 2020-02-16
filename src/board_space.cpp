#include <SDL2/SDL.h>
#include "board_space.h"
#include "shape_texture_factory.h"
#include "enums.h"

BoardSpace::BoardSpace(int x, int y, int length, ShapeTextureFactory* factory)
{
    _factory = factory;
    _rect.x = x;
    _rect.y = y;
    _rect.h = length;
    _rect.w = length;
    _state = SpaceState::Empty;
}

void BoardSpace::draw(SDL_Renderer* renderer)
{
    if (_state != SpaceState::Empty)
    {
        SDL_RenderCopy(renderer, _texture, NULL, &_rect);
    }
}

void BoardSpace::click(SpaceState state)
{
    if (_state == SpaceState::Empty)
    {
        _state = state;
        _texture = state == SpaceState::X ?
            _factory->getX() :
            _factory->getO();
    }
}

SpaceState BoardSpace::getState()
{
    return _state;
}

void BoardSpace::reset()
{
    _state = SpaceState::Empty;
}
