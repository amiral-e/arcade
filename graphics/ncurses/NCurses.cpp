/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NCurses
*/

#include <iostream>
#include <curses.h>
#include "NCurses.hpp"

extern "C" IGraphic *genGraphic()
{
    return new NCurses;
}

extern "C" std::string getId()
{
    return "Ncurses";
}

NCurses::NCurses()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    _open = true;
}

NCurses::~NCurses()
{
    windowClear();
    windowClose();
    curs_set(1);
    endwin();
}

void NCurses::assetsLoad(std::vector<std::tuple<char, char, std::string>> assets)
{
    _assets.clear();
    for (auto& asset : assets)
        _assets.push_back({std::get<0>(asset), std::get<1>(asset)});
}

void NCurses::windowRefresh()
{
    refresh();
}

void NCurses::windowClear()
{
    clear();
}

void NCurses::windowClose()
{
    _open = false;
}

bool NCurses::isRunning()
{
    return _open;
}

#include <fstream>

int NCurses::getKey()
{
    int key = getch();

    if (key == KEY_BACKSPACE || key == KEY_DC || key == 127)
        return 8;
    return key;
}

int NCurses::getSize()
{
    return COLS;
}

void NCurses::printText(std::string text, pos_t pos)
{
    mvprintw(pos.y, pos.x, text.c_str());
}

void NCurses::printMap(std::vector<std::string> map, pos_t tab)
{
    for (int y = 0; y < map.size(); ++y)
        for (int x = 0; x < map[y].size(); ++x)
            printText(std::string(1, map[y][x]), {x + tab.x, y + tab.y});
}

int NCurses::findTuple(char id)
{
    for (int i = 0; i < _assets.size(); ++i)
        if (_assets[i].first == id)
            return i;
    return -1;
}

void NCurses::printElements(std::vector<std::pair<char, pos_t>> elements, pos_t tab)
{
    int pos = -1;

    for (const auto& elem : elements) {
        pos = findTuple(elem.first);
        printText(std::string(1, (pos == -1) ? '?' : std::get<1>(_assets[pos])),
            {elem.second.x + tab.x, elem.second.y + tab.y});
    }
}
