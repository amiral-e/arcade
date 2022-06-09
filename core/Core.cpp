/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Core
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Core.hpp"
#include "Exception.hpp"

typedef IGraphic* (*LibGraphic)();
typedef IGame* (*LibGame)();
typedef std::string (*GetId)();

Core::Core()
{
    _handlGraphic = nullptr;
    _handlGame = nullptr;
    _libGraphic = NULL;
    _libGame = NULL;
    _name = "default";
    _choice.first = 0;
    _choice.second = 0;
    _state = MENU;
    srand(time(NULL));
}

Core::~Core()
{
    closeGraphic();
    closeGame();
    _graphics.clear();
    _games.clear();
}

void Core::loadGraphic(std::string file)
{
    LibGraphic lib = NULL;
    GetId id = NULL;

    if (file.find("./", 0) == std::string::npos)
        file.insert(0, "./");
    _handlGraphic = dlopen(file.c_str(), RTLD_LAZY);
    if (_handlGraphic == NULL)
        throw ExceptionGraphic(std::string("dlopen : ") + dlerror());
    lib = (LibGraphic)dlsym(_handlGraphic, "genGraphic");
    if (lib == NULL)
        throw ExceptionGraphic(std::string("dlsym : ") + dlerror());
    _libGraphic = lib();
    id = (GetId)dlsym(_handlGraphic, "getId");
    if (id == NULL)
        throw ExceptionGraphic(std::string("dlsym : ") + dlerror());
    if (_graphics.empty())
        _graphics.push_back({file, id()});
    if (_state == GAME)
        _libGraphic->assetsLoad(_libGame->getAssets());
}

void Core::loadGame(std::string file)
{
    LibGame lib = NULL;

    if (file.find("./", 0) == std::string::npos)
        file.insert(0, "./");
    _handlGame = dlopen(file.c_str(), RTLD_LAZY);
    if (_handlGame == NULL)
        throw ExceptionGame(std::string("dlopen : ") + dlerror());
    lib = (LibGame)dlsym(_handlGame, "genGame");
    if (lib == NULL)
        throw ExceptionGame(std::string("dlsym : ") + dlerror());
    _libGame = lib();
    _libGraphic->assetsLoad(_libGame->getAssets());
    _state = GAME;
}

void Core::closeGraphic()
{
    if (_libGraphic != NULL)
        delete _libGraphic;
    if (_handlGraphic != NULL)
        dlclose(_handlGraphic);
}

void Core::closeGame()
{
    if (_libGame != NULL)
        delete _libGame;
    if (_handlGame != NULL)
        dlclose(_handlGame);
}

void Core::switchGraphic(std::string path)
{
    if (_graphics.empty())
        throw ExceptionGraphic("you need at least 1 graphic library");
    if (_graphics.size() == 1)
        return;
    closeGraphic();
    loadGraphic(path);
}

void Core::switchGame(std::string path)
{
    if (_games.empty())
        throw ExceptionGraphic("you need at least 1 game library");
    if (_games.size() == 1)
        return;
    closeGame();
    loadGame(path);
}

bool findPair(std::vector<std::pair<std::string, std::string>> graphics, std::string path)
{
    for (const auto& graph : graphics)
        if (path == graph.first)
            return true;
    return false;
}

void Core::searchLibs()
{
    if (std::filesystem::exists("./lib/") == false)
        return;
    for (const auto &file : std::filesystem::directory_iterator("./lib/"))
        if (findPair(_graphics, file.path().string()) == false)
            saveLib(file.path());
}

void Core::saveLib(std::filesystem::path file)
{
    void *handl = dlopen(file.c_str(), RTLD_LAZY);
    GetId id = NULL;

    if (handl == NULL)
        return;
    id = (GetId)dlsym(handl, "getId");
    if (id == NULL)
        throw ExceptionGraphic(std::string("dlsym : ") + dlerror());
    if (dlsym(handl, "genGraphic") != NULL)
        _graphics.push_back({file.string(), id()});
    if (dlsym(handl, "genGame") != NULL)
        _games.push_back({file.string(), id()});
}

void Core::saveScore()
{
    bool updated = false;
    std::ofstream file(std::string("./assets/") + _libGame->getId() + "/scores");

    if (_scores.size() == 1 && _scores[0] == "none")
        _scores.clear();
    for (int i = 0; i < _scores.size(); ++i)
        if (_scores[i].rfind(_name + ":", 0) == 0) {
            _scores[i] = _name + ": " + std::to_string(_libGame->getScore());
            updated = true;
        }
    if (updated == false)
        _scores.push_back(_name + ": " + std::to_string(_libGame->getScore()));
    for (int i = 0; i < _scores.size(); ++i)
        file << _scores[i] << std::endl;
}

void Core::loadScore()
{
    std::ifstream file(std::string("./assets/") + _games[_choice.second].second + "/scores");
    std::string line;

    if (!file)
        _scores.push_back("none");
    while (std::getline(file, line))
        _scores.push_back(line);
    if (_scores.size() == 0)
        _scores.push_back("none");
}

void Core::displayMenu()
{
    int x = _libGraphic->getSize() / 2;
    std::string filename;

    _libGraphic->printText("  GRAPHICALS LIBS :", {x / 10, 0});
    for (int i = 0; i < _graphics.size(); ++i)
        _libGraphic->printText((_choice.first == i ? "> " : "  ") + _graphics[i].second, {x / 10, i + 2});
    _libGraphic->printText("  Player name : " + _name, {x / 10, 3 + (int)_graphics.size()});
    if (_state == MENU) {
        _libGraphic->printText("  GAMES LIBS :", {x + x / 10, 0});
        for (int i = 0; i < _games.size(); ++i)
            _libGraphic->printText((_choice.second == i ? "> " : "  ") + _games[i].second,
                {x + x / 10, i + 2});
        if (_scores.size() == 0)
            loadScore();
        _libGraphic->printText("  ALL SCORES :", {x + x / 10, 3 + (int)_games.size()});
        for (int i = 0; i < _scores.size(); ++i)
            _libGraphic->printText("  " + _scores[i], {x + x / 10, i + 5 + (int)_games.size()});
    }
    else if (_state == GAME)
        displayGame();
    else if (_state == OVER)
        displayOver();
}

void Core::displayGame()
{
    int x = _libGraphic->getSize() / 3;

    _libGraphic->printText("Score : " + std::to_string(_libGame->getScore()), {x + x / 10, 0});
    _libGraphic->printMap(_libGame->getMap(), {x + x / 10, 2});
    _libGraphic->printElements(_libGame->getElements(), {x + x / 10, 2});
}

void Core::displayOver()
{
    int x = _libGraphic->getSize() / 3;

    _libGraphic->printText("Game over", {x + x / 10, 0});
    _libGraphic->printText("Your Score : " + std::to_string(_libGame->getScore()), {x + x / 10, 1});
    _libGraphic->printText("press r to restart the game", {x + x / 10, 3});
    _libGraphic->printText("press m to go to main menu", {x + x / 10, 4});
}

void Core::keyLib(int key)
{
    if (key == KEY_DOWN) {
        _choice.first++;
        if (_choice.first > _graphics.size() - 1)
            _choice.first = 0;
    } else if (key == KEY_UP) {
        _choice.first--;
        if (_choice.first < 0)
            _choice.first = _graphics.size() - 1;
    }
    if (key == KEY_LEFT) {
        _choice.second++;
        if (_choice.second > _games.size() - 1)
            _choice.second = 0;
        _scores.clear();
    } else if (key == KEY_RIGHT) {
        _choice.second--;
        if (_choice.second < 0)
            _choice.second = _games.size() - 1;
        _scores.clear();
    }
    if (key == KEY_DOWN || key == KEY_UP)
        switchGraphic(_graphics[_choice.first].first);
    if (_state == MENU && key == KEY_ENTER) {
        if (_libGame != NULL && _libGame->getId() == _games[_choice.second].second) {
            _libGame->gameRestart();
            _state = GAME;
        } else
            switchGame(_games[_choice.second].first);
    }
    return;
}

void Core::keyMenu(int key)
{
    if (key >= 'a' && key <= 'z')
        _name.push_back(key);
    else if (key == KEY_BACKSPACE && _name.size() != 0)
        _name.pop_back();
}

void Core::keyGame(int key)
{
    if (key == 'r')
        _libGame->gameRestart();
    else if (key == 'm')
        _state = MENU;
    else if (key == 'z' || key == 'q' || key == 's' || key == 'd')
        _libGame->gameKeys(key);
    return;
}

void Core::keyOver(int key)
{
    if (key == 'r') {
        _libGame->gameRestart();
        _state = GAME;
    } else if (key == 'm')
        _state = MENU;
    return;
}

void Core::keyMan(int key)
{
    if (key == KEY_ESCAPE)
        _libGraphic->windowClose();
    if ((key >= KEY_DOWN && key <= KEY_RIGHT) ||
        key == KEY_ENTER || key == KEY_BACKSPACE)
        keyLib(key);
    if (_state == MENU)
        keyMenu(key);
    else if (_state == GAME)
        keyGame(key);
    else if (_state == OVER)
        keyOver(key);
    return;
}

static bool validClock(std::chrono::time_point<std::chrono::high_resolution_clock> clock, tclock_t timer)
{
    if (timer == DISP && std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::high_resolution_clock::now() - clock).count() > 10000)
        return true;
    else if (timer == PLAY && std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::high_resolution_clock::now() - clock).count() > 400000)
        return true;
    else
        return false;
}

void Core::loop()
{
    auto refresh = std::chrono::high_resolution_clock::now();
    auto play = std::chrono::high_resolution_clock::now();
    int key = -1;

    while (_libGraphic->isRunning()) {
        if (validClock(refresh, DISP)) {
            _libGraphic->windowClear();
            displayMenu();
            _libGraphic->windowRefresh();
            refresh = std::chrono::high_resolution_clock::now();
        }
        if (_state == GAME && validClock(play, PLAY)) {
            _libGame->gameLoop();
            if (!_libGame->isAlive()) {
                saveScore();
                _state = OVER;
            }
            play = std::chrono::high_resolution_clock::now();
        }
        keyMan(_libGraphic->getKey());
    }
    closeGraphic();
}
