/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Libcaca
*/

#include <iostream>
#include "Libcaca.hpp"
#include "../../core/Exception.hpp"
#include "../../core/Keys.hpp"

extern "C" IGraphic *genGraphic()
{
    return new Libcaca;
}

extern "C" std::string getId()
{
    return "Libcaca";
}

Libcaca::Libcaca()
{
	_display = caca_create_display(NULL);
    if (_display == NULL)
        throw ExceptionGraphic("libcaca : couldn't create window");
    _canvas = caca_get_canvas(_display);
    caca_set_display_title(_display, "Arcade");
    _open = true;
}

Libcaca::~Libcaca()
{
    windowClear();
    windowClose();
    caca_free_display(_display);
}

void Libcaca::assetsLoad(std::vector<std::tuple<char, char, std::string>> assets)
{
    _assets.clear();
    for (auto& asset : assets)
        _assets.push_back({std::get<0>(asset), std::get<1>(asset)});
}

void Libcaca::windowRefresh()
{
    caca_refresh_display(_display);
}

void Libcaca::windowClear()
{
    caca_clear_canvas(_canvas);
}

void Libcaca::windowClose()
{
    _open = false;
}

bool Libcaca::isRunning()
{
    return _open;
}

static int convertLibcacaAscii(int key)
{
    if (key >= 'a' && key <= 'z')
        return key;
    else if (key >= 'A' && key <= 'Z')
        return key - 32;
    switch (key) {
        case CACA_KEY_RETURN:
            return KEY_ENTER;
        case CACA_KEY_BACKSPACE:
            return KEY_BACKSPACE;
        case CACA_KEY_ESCAPE:
            return KEY_ESCAPE;
        case CACA_KEY_UP:
            return KEY_UP;
        case CACA_KEY_DOWN:
            return KEY_DOWN;
        case CACA_KEY_LEFT:
            return KEY_LEFT;
        case CACA_KEY_RIGHT:
            return KEY_RIGHT;
        default:
            return -1;
    }
}

int Libcaca::getKey()
{
    caca_event_t event;
    caca_event_type type;

    caca_get_event(_display, CACA_EVENT_ANY, &event, 1000);
    type = caca_get_event_type(&event);
    if (type == CACA_EVENT_QUIT)
        windowClose();
    else if (type == CACA_EVENT_KEY_PRESS)
        return convertLibcacaAscii(caca_get_event_key_ch(&event));
    return -1;
}

int Libcaca::getSize()
{
    return caca_get_canvas_width(_canvas);
}

void Libcaca::printText(std::string text, pos_t pos)
{
    caca_put_str(_canvas, pos.x, pos.y, text.c_str());
}

void Libcaca::printMap(std::vector<std::string> map, pos_t tab)
{
    for (int y = 0; y < map.size(); ++y)
        for (int x = 0; x < map[y].size(); ++x)
            printText(std::string(1, map[y][x]), {x + tab.x, y + tab.y});
}

int Libcaca::findTuple(char id)
{
    for (int i = 0; i < _assets.size(); ++i)
        if (_assets[i].first == id)
            return i;
    return -1;
}

void Libcaca::printElements(std::vector<std::pair<char, pos_t>> elements, pos_t tab)
{
    int pos = -1;

    for (const auto& elem : elements) {
        pos = findTuple(elem.first);
        printText(std::string(1, (pos == -1) ? '?' : std::get<1>(_assets[pos])),
            {elem.second.x + tab.x, elem.second.y + tab.y});
    }
}
