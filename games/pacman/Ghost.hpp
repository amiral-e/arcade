/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Ghost
*/

#pragma once

#include <vector>
#include <string>
#include "../../core/Pos.hpp"
#include "Type.hpp"
#include "../Direction.hpp"

class Ghost {
    public:
        Ghost(pos_t, type_t, int , pos_t);
        ~Ghost();
        bool isAlive();
        void setAlive(bool);
        int getPoint();
        void waitSpawn();
        pos_t getPos();
        void pathFinding(std::vector<std::string>);
        type_t getType();
        void moveGhost();
        void setDirection(direction_t);

    protected:
    private:
        pos_t _pos;
        pos_t _start;
        pos_t _spawn;
        bool _alive;
        type_t _type;
        direction_t _dir;
        int _wait;
        int _point;
};
