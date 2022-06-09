/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Player
*/

#pragma once

#include <vector>
#include "../../core/Pos.hpp"
#include "../Direction.hpp"

class Player {
    public:
        Player(int x, int y);
        ~Player();
        bool isAlive();
        void setAlive(bool);
        std::vector<pos_t> getPos();
        void movePlayer(pos_t);
        void setDirection(direction_t);
        direction_t getDirection();
        void updatePos();

    protected:
    private:
        std::vector<pos_t> _pos;
        bool _alive;
        direction_t _dir;
};
