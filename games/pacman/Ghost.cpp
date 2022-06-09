/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Ghost
*/

#include <bits/stdc++.h>
#include "Ghost.hpp"

Ghost::Ghost(pos_t pos, type_t type, int point, pos_t spawn)
{
    _pos = pos;
    _start = _pos;
    _alive = false;
    _type = type;
    _point = point;
    _spawn = spawn;
    _dir = NONE;
    _wait = 0;
    if (type == ONE)
        _wait = 10;
    else if (type == TWO)
        _wait = 15;
    else if (type == THREE)
        _wait = 20;
    else if (type == FOUR)
        _wait = 25;
}

Ghost::~Ghost()
{}

bool Ghost::isAlive()
{
    return _alive;
}

void Ghost::setAlive(bool alive)
{
    _alive = alive;
    _pos = (alive == false) ? _start : _spawn;
}

pos_t Ghost::getPos()
{
    return _pos;
}

int Ghost::getPoint()
{
    return _point;
}

void Ghost::waitSpawn()
{
    if (_alive == false) {
        if (_wait == 0) {
            setAlive(true);
            _wait = 15;
        } else
            _wait--;
    }
}

static bool randomBool()
{
    return (rand() % (INT_MAX - 1)) % 2 == 0;
}

void Ghost::pathFinding(std::vector<std::string> map)
{
    if (_dir == NONE) {
        setDirection(randomBool() ? LEFT : RIGHT);
        return;
    }
    if ((_dir == UP && map[_pos.y - 1][_pos.x] == '#') ||
        (_dir == DOWN && map[_pos.y + 1][_pos.x] == '#')) {
        if (map[_pos.y][_pos.x - 1] != '#' && map[_pos.y][_pos.x + 1] != '#')
            setDirection(randomBool() ? LEFT : RIGHT);
        else if (map[_pos.y][_pos.x + 1] != '#')
            setDirection(RIGHT);
        else if (map[_pos.y][_pos.x - 1] != '#')
            setDirection(LEFT);
    }
    if ((_dir == LEFT && map[_pos.y][_pos.x - 1] == '#') ||
        (_dir == RIGHT && map[_pos.y][_pos.x + 1] == '#')) {
        if (map[_pos.y - 1][_pos.x] != '#' && map[_pos.y + 1][_pos.x] != '#')
            setDirection(randomBool() ? UP : DOWN);
        else if (map[_pos.y + 1][_pos.x] != '#')
            setDirection(DOWN);
        else if (map[_pos.y - 1][_pos.x] != '#')
            setDirection(UP);
    }
    moveGhost();
}

type_t Ghost::getType()
{
    return _type;
}

void Ghost::moveGhost()
{
    switch (_dir) {
        case UP:
            _pos.y -= 1;
            break;
        case DOWN:
            _pos.y += 1;
            break;
        case LEFT:
            _pos.x -= 1;
            break;
        case RIGHT:
            _pos.x += 1;
            break;
    }
}

void Ghost::setDirection(direction_t dir)
{
    _dir = dir;
}
