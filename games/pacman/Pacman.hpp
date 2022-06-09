/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Pacman
*/

#pragma once

#include "../IGame.hpp"
#include "Player.hpp"
#include "Ghost.hpp"

class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();
        virtual void gameLoop();
        virtual void gameKeys(int);
        virtual void gameRestart();
        virtual size_t getScore();
        virtual bool isAlive();
        virtual void loadMap();
        virtual void parseMap();
        virtual std::vector<std::string> getMap();
        virtual std::vector<std::tuple<char, char, std::string>> getAssets();
        virtual std::vector<std::pair<char, pos_t>> getElements();
        virtual void checkCollision();
        virtual std::string getId();

    protected:
    private:
        size_t _score;
        Player *_player;
        std::vector<Ghost *> _ghost;
        std::vector<std::string> _map;
};
