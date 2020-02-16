#include <SDL2/SDL.h>
#include "board.h"
#include "graphics_context.h"
#include "shape_texture_factory.h"
#include "enums.h"

Board::Board(GraphicsContext& context)
{
    _texture = context.getTexture("board.bmp");
    _factory = new ShapeTextureFactory(context);
    _spaceWidth = context.getWidth() / 3;
    _spaceHeight = context.getHeight() / 3;
    
    _currentPlayer = Player::One;

    _winTextures[(int)WinLine::Top] = context.getTexture("top_win.png");
    _winTextures[(int)WinLine::HMiddle] = context.getTexture("h_middle_win.png");
    _winTextures[(int)WinLine::Bottom] = context.getTexture("bottom_win.png");
    _winTextures[(int)WinLine::Left] = context.getTexture("left_win.png");
    _winTextures[(int)WinLine::VMiddle] = context.getTexture("v_middle_win.png");
    _winTextures[(int)WinLine::Right] = context.getTexture("right_win.png");
    _winTextures[(int)WinLine::BLToTR] = context.getTexture("bl_to_tr_win.png");
    _winTextures[(int)WinLine::TLToBR] = context.getTexture("tl_to_br_win.png");
    _winTextures[(int)WinLine::Cat] = context.getTexture("cat.png");

    _winLine = WinLine::None;
    _gameOver = false;

    int y = 0;
    int x = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _spaces[i][j] = new BoardSpace(x, y, 100, _factory);
            x += _spaceWidth;
        }
        x = 0;
        y += _spaceHeight;
    }
}

Board::~Board()
{
    SDL_DestroyTexture(_texture);
    for (auto t : _winTextures)
    {
        SDL_DestroyTexture(t);
    }
    delete _factory;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            delete _spaces[i][j];
        }
    }
}

void Board::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, _texture, NULL, NULL);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _spaces[i][j]->draw(renderer);
        }
    }

    if (_winLine != WinLine::None)
    {
        SDL_RenderCopy(renderer, _winTextures[(int)_winLine], NULL, NULL);
    }
}

void Board::onEvent(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (_gameOver)
        {
            reset();
            return;
        }
        int x = event.motion.x / _spaceWidth;
        int y = event.motion.y / _spaceHeight;
        if (_spaces[y][x]->getState() == SpaceState::Empty)
        {
            _spaces[y][x]->click(_currentPlayer == Player::One ? SpaceState::X : SpaceState::O);
            _currentPlayer = _currentPlayer == Player::One ?
                Player::Two :
                Player::One;
            _gameOver = gameOver();
        }
    }
}

bool Board::gameOver()
{
    for (int i = 0; i < 3; i++)
    {
        SpaceState state = _spaces[i][0]->getState();
        for (int j = 1; j < 4; j++)
        {
            if (j == 3)
            {
                _winLine = (WinLine)i;
                return true;
            }
            if (_spaces[i][j]->getState() != state || _spaces[i][j]->getState() == SpaceState::Empty)
            {
                break;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SpaceState state = _spaces[0][i]->getState();
        for (int j = 1; j < 4; j++)
        {
            if (j == 3)
            {
                _winLine = (WinLine)(i + 3);
                return true;
            }
            if (_spaces[j][i]->getState() != state || _spaces[j][i]->getState() == SpaceState::Empty)
            {
                break;
            }
        }
    }
    auto topLeft = _spaces[0][0]->getState();
    auto middle = _spaces[1][1]->getState();
    auto bottomRight = _spaces[2][2]->getState();
    auto topRight = _spaces[0][2]->getState();
    auto bottomLeft = _spaces[2][0]->getState();

    if (middle != SpaceState::Empty)
    {
        if (topLeft == middle && middle == bottomRight)
        { 
            _winLine = WinLine::TLToBR;
            return true;
        }
        if (topRight == middle && middle == bottomLeft)
        {
            _winLine = WinLine::BLToTR;
            return true;
        }
    }

    bool emptySpace = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (_spaces[i][j]->getState() == SpaceState::Empty)
            {
                emptySpace = true;
            }
        }
    }
    if (!emptySpace)
    { 
        _winLine = WinLine::Cat;
        return true;
    }

    return false;
}

void Board::reset()
{
    _currentPlayer = Player::One;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _spaces[i][j]->reset();
        }
    }
    _winLine = WinLine::None;
    _gameOver = false;
}
