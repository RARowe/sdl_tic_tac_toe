#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>
#include "graphics_context.h"

GraphicsContext::GraphicsContext(const char* title, int width, int height, const char* resourceFolderPath)
{
    _width = width;
    _height = height;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    _window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (_window == NULL) {
        std::cout << "Could not create window! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        std::cout << "Could not create renderer! SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    _resourceFolderPath = resourceFolderPath;
}

GraphicsContext::~GraphicsContext()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

SDL_Window* GraphicsContext::getWindow()
{
    return _window;
}

SDL_Renderer* GraphicsContext::getRenderer()
{
    return _renderer;
}

SDL_Texture* GraphicsContext::getTexture(const char* path)
{
    char buffer[256];
    strcpy(buffer, _resourceFolderPath);
    strcat(buffer, path);
    SDL_Surface* surface = IMG_Load(buffer);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

int GraphicsContext::getWidth()
{
    return _width;
}

int GraphicsContext::getHeight()
{
    return _height;
}
