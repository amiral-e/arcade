/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Player
*/

#pragma once

#include <vector>
#include <string>
#include "../../core/Pos.hpp"
#include "../Direction.hpp"

class Player {
    public:
        Player(int x, int y);
        ~Player();
        bool isAlive();
        void setAlive(bool);
        bool isPower();
        void setPower(bool);
        pos_t getPos();
        void movePlayer(std::vector<std::string>);
        void updatePos();
        void setPos(pos_t);
        pos_t getLastPos();
        void setDirection(direction_t);
        direction_t getDirection();
        int getPower();
        void setPower(int);

    protected:
    private:
        pos_t _pos;
        pos_t _lastPos;
        bool _alive;
        int _power;
        direction_t _dir;
};
