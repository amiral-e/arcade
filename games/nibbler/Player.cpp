/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int x, int y)
{
    for (int i = 0; i < 4; i++)
        _pos.push_back({x, y + i});
    _alive = true;
    _dir = UP;
}

Player::~Player()
{}

bool Player::isAlive()
{
    return _alive;
}

void Player::setAlive(bool alive)
{
    _alive = alive;
}

std::vector<pos_t> Player::getPos()
{
    return _pos;
}

void Player::updatePos()
{
    switch (_dir) {
        case UP:
            _pos.front().y -= 1;
            break;
        case DOWN:
            _pos.front().y += 1;
            break;
        case LEFT:
            _pos.front().x -= 1;
            break;
        case RIGHT:
            _pos.front().x += 1;
            break;
    }
}

void Player::movePlayer(pos_t apple)
{
    pos_t back = _pos.back();

    for (int i = _pos.size(); i > 0; --i)
        _pos[i] = _pos[i - 1];
    updatePos();
    if (_pos.front().x == apple.x && _pos.front().y == apple.y)
        _pos.push_back(back);
}

void Player::setDirection(direction_t dir)
{
    _dir = dir;
}

direction_t Player::getDirection()
{
    return _dir;
}
