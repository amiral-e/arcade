/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Sdl2
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../IGraphic.hpp"

class Sdl2 : public IGraphic {
    public:
        Sdl2();
        ~Sdl2();
        virtual void assetsLoad(std::vector<std::tuple<char, char, std::string>>);
        virtual void windowRefresh();
        virtual void windowClear();
        virtual void windowClose();
        virtual bool isRunning();
        virtual int getKey();
        virtual int getSize();
        virtual void printText(std::string, pos_t);
        virtual void printMap(std::vector<std::string>, pos_t);
        virtual void printElements(std::vector<std::pair<char, pos_t>>, pos_t);
        virtual int findTuple(char);
        void printImage(SDL_Texture *, pos_t, pos_t);

    protected:
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        TTF_Font *_font;
        bool _open;
        std::vector<std::pair<char, SDL_Texture *>> _assets;
};
