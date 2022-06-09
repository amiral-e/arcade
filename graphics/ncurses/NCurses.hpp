/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** NCurses
*/

#pragma once

#include "../IGraphic.hpp"

class NCurses : public IGraphic {
    public:
        NCurses();
        ~NCurses();
        virtual void assetsLoad(std::vector<std::tuple<char, char, std::string>>);
        virtual void windowRefresh();
        virtual void windowClear();
        virtual void windowClose();
        virtual bool isRunning();
        virtual int getKey();
        virtual int getSize();
        virtual void printText(std::string, pos_t);
        virtual void printMap(std::vector<std::string>, pos_t);
        virtual void printElements(std::vector<std::pair<char, pos_t>>, pos_t);
        virtual int findTuple(char);

    protected:
    private:
        bool _open;
        std::vector<std::pair<char, char>> _assets;
};
