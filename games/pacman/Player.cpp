/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
    _alive = true;
    _power = 1;
    _dir = NONE;
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

bool Player::isPower()
{
    return _power > 0 ? true : false;
}

void Player::setPower(bool power)
{
    _power = power;
}

pos_t Player::getPos()
{
    return _pos;
}

void Player::updatePos()
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

void Player::movePlayer(std::vector<std::string> map)
{
    _lastPos = _pos;
    updatePos();
    if (_power > 0)
        _power--;
}

void Player::setDirection(direction_t dir)
{
    _dir = dir;
}

direction_t Player::getDirection()
{
    return _dir;
}

void Player::setPos(pos_t pos)
{
    _pos = pos;
}

pos_t Player::getLastPos()
{
    return _lastPos;
}

void Player::setPower(int power)
{
    _power = power;
}

int Player::getPower()
{
    return _power;
}