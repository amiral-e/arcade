
/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Apple
*/

#include "Apple.hpp"

static bool isPlayerHere(std::vector<pos_t> player, pos_t apple)
{
    for (const auto &pos : player)
        if (apple.x == pos.x && apple.y == pos.y)
            return true;
    return false;
}

void Apple::newPos(std::vector<pos_t> player, std::vector<std::string> map)
{
    do {
        _pos.x = rand() % (map.front().size() - 1) + 1;
        _pos.y = rand() % (map.size() - 1) + 1;
    } while (isPlayerHere(player, _pos) || map[_pos.y][_pos.x] == '#');
}

pos_t Apple::getPos() const
{
    return _pos;
}
