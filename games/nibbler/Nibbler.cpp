/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Nibbler
*/

#include <fstream>
#include <iostream>
#include "Nibbler.hpp"
#include "../../core/Exception.hpp"

extern "C" IGame *genGame()
{
    return new Nibbler;
}

extern "C" std::string getId()
{
    return "Nibbler";
}

Nibbler::Nibbler()
{
    _player = nullptr;
    _apple = nullptr;
    gameRestart();
}

Nibbler::~Nibbler()
{
    delete _player;
}

void Nibbler::checkCollision()
{
    std::vector<pos_t> playerPos = _player->getPos();
    pos_t applePos = _apple->getPos();

    if (applePos.x == playerPos.front().x && applePos.y == playerPos.front().y) {
        ++_score;
        _apple->newPos(playerPos, _map);
    }
    for (int i = 1; i < playerPos.size(); ++i)
        if (playerPos.front().x == playerPos[i].x && playerPos.front().y == playerPos[i].y)
            _player->setAlive(false);
    if (_map[playerPos.front().y][playerPos.front().x] == '#')
        _player->setAlive(false);
}

void Nibbler::gameLoop()
{
    _player->movePlayer(_apple->getPos());
    checkCollision();
    _move = true;
}

void Nibbler::gameKeys(int key)
{
    direction_t dir = _player->getDirection();

    if (_move == false)
        return;
    if (key == 'q' || key == 'd')
        if (dir == UP || dir == DOWN) {
            _player->setDirection(key == 'q' ? LEFT : RIGHT);
            _move = false;
        }
    if (key == 'z' || key == 's')
        if (dir == LEFT || dir == RIGHT) {
            _player->setDirection(key == 'z' ? UP : DOWN);
            _move = false;
        }
}

void Nibbler::gameRestart()
{
    if (_player != nullptr) {
        delete _player;
        _player = nullptr;
    }
    if (_apple != nullptr) {
        delete _apple;
        _apple = nullptr;
    }
    loadMap();
    parseMap();
    _apple = new Apple();
    _apple->newPos(_player->getPos(), _map);
    _move = true;
    _score = 0;
}

size_t Nibbler::getScore()
{
    return _score;
}

bool Nibbler::isAlive()
{
    return (_player != NULL) ? _player->isAlive() : false;
}

void Nibbler::loadMap()
{
    std::ifstream file("./assets/Nibbler/map");
    std::string line;

    _map.clear();
    if (!file)
        throw ExceptionGame("nibbler : ./assets/Nibbler/map file not found");
    while (std::getline(file, line))
        _map.push_back(line);
}

void Nibbler::parseMap()
{
    for (size_t y = 0; y < _map.size(); ++y)
        for (size_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == 'P') {
                if (_player != nullptr)
                    throw ExceptionGame("nibbler : to many players found in the map");
                _player = new Player(x, y);
                _map[y].replace(x, 1, " ");
            }
        }
    if (_player == nullptr)
        throw ExceptionGame("nibbler : no player found in the map");
}

std::vector<std::string> Nibbler::getMap()
{
    return _map;
}

std::vector<std::tuple<char, char, std::string>> Nibbler::getAssets()
{
    std::vector<std::tuple<char, char, std::string>> assets;

    assets.push_back({'P', 'S', "./assets/Nibbler/head.png"});
    assets.push_back({'T', 'T', "./assets/Nibbler/tail.png"});
    assets.push_back({'o', 'o', "./assets/Nibbler/apple.png"});
    assets.push_back({'#', '#', "./assets/wall.png"});
    assets.push_back({' ', ' ', "./assets/empty.png"});
    return assets;
}

std::vector<std::pair<char, pos_t>> Nibbler::getElements()
{
    std::vector<std::pair<char, pos_t>> elements;
    std::vector<pos_t> pos = _player->getPos();

    elements.push_back(std::make_pair('P', pos.front()));
    for (int i = 1;  i < pos.size(); ++i)
        elements.push_back(std::make_pair('T', pos[i]));
    elements.push_back(std::make_pair('o', _apple->getPos()));
    return elements;
}

std::string Nibbler::getId()
{
    return "Nibbler";
}
