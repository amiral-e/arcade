/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Sdl2
*/

#include <iostream>
#include "Sdl2.hpp"
#include "../../core/Exception.hpp"
#include "../../core/Keys.hpp"

extern "C" IGraphic *genGraphic()
{
    return new Sdl2;
}

extern "C" std::string getId()
{
    return "Sdl2";
}

Sdl2::Sdl2()
{
    SDL_DisplayMode DM;

    SDL_Init(SDL_INIT_VIDEO);
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG ))
        throw ExceptionGraphic("sdl2 : init png failed");
    TTF_Init();
    SDL_GetCurrentDisplayMode(0, &DM);
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        (DM.w < 1400 ? DM.w : 1400), (DM.h < 700 ? DM.h : 700), SDL_WINDOW_RESIZABLE);
    if (_window == NULL)
		throw ExceptionGraphic("sdl2 : window creation failed");
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (_renderer == NULL)
		throw ExceptionGraphic("sdl2 : renderer creation failed");
    _font = TTF_OpenFont("./assets/font.ttf", 25);
    if (_font == NULL)
        throw ExceptionGraphic("sdl2 : font creation failed");
    _open = true;
}

Sdl2::~Sdl2()
{
    windowClear();
    windowClose();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Sdl2::assetsLoad(std::vector<std::tuple<char, char, std::string>> assets)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, "./assets/unknown.png");

    _assets.clear();
    if (texture == NULL)
        throw ExceptionGraphic("sdl2 : can't load texture");
    _assets.push_back({'?', texture});
    for (auto& asset : assets) {
        texture = IMG_LoadTexture(_renderer, std::get<2>(asset).c_str());
        if (texture == NULL)
            throw ExceptionGraphic("sdl2 : can't load texture");
        _assets.push_back({std::get<0>(asset), texture});
    }
}

void Sdl2::windowRefresh()
{
    SDL_RenderPresent(_renderer);
}

void Sdl2::windowClear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
}

void Sdl2::windowClose()
{
    _open = false;
}

bool Sdl2::isRunning()
{
    return _open;
}

static int convertSdlAscii(int key)
{
    if (key >= 'a' && key <= 'z')
        return key;
    switch (key) {
        case SDLK_RETURN:
            return KEY_ENTER;
        case SDLK_BACKSPACE:
            return KEY_BACKSPACE;
        case SDLK_ESCAPE:
            return KEY_ESCAPE;
        case SDLK_UP:
            return KEY_UP;
        case SDLK_DOWN:
            return KEY_DOWN;
        case SDLK_LEFT:
            return KEY_LEFT;
        case SDLK_RIGHT:
            return KEY_RIGHT;
        default:
            return -1;
    }
}

int Sdl2::getKey()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) > 0) {
        if (event.type == SDL_QUIT)
            windowClose();
        else if (event.type == SDL_KEYDOWN) {
            if (event.type == SDL_TEXTINPUT)
                return convertSdlAscii(event.text.text[0]);
            else
                return convertSdlAscii(event.key.keysym.sym);
        }
    }
    return -1;
}

int Sdl2::getSize()
{
    return SDL_GetWindowSurface(_window)->w;
}

void Sdl2::printText(std::string text, pos_t pos)
{
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderText_Blended(_font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect rect = {.x = pos.x, .y = pos.y * 30 + 20};

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.h -= 5;
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
}

void Sdl2::printMap(std::vector<std::string> map, pos_t tab)
{
    int pos = -1;

    for (int y = 0; y < map.size(); ++y)
        for (int x = 0; x < map[y].size(); ++x) {
            pos = findTuple(map[y][x]);
            printImage((pos == -1) ? std::get<1>(_assets[0]) : std::get<1>(_assets[pos]),
                tab, {x, y});
        }
}

int Sdl2::findTuple(char id)
{
    for (int i = 0; i < _assets.size(); ++i)
        if (_assets[i].first == id)
            return i;
    return -1;
}

void Sdl2::printElements(std::vector<std::pair<char, pos_t>> elements, pos_t tab)
{
    int pos = -1;

    for (const auto& elem : elements) {
        pos = findTuple(elem.first);
        printImage((pos == -1) ? std::get<1>(_assets[0]) : std::get<1>(_assets[pos]),
            tab, {elem.second.x, elem.second.y});
    }
}

void Sdl2::printImage(SDL_Texture *texture, pos_t tab, pos_t pos)
{
    SDL_Rect rect = {tab.x + pos.x * 20, tab.y * 40 + pos.y * 20, 20, 20};

    SDL_RenderCopy(_renderer, texture, NULL, &rect);
}