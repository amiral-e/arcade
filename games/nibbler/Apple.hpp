/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Apple
*/

#pragma once

#include <string>
#include <vector>
#include "../../core/Pos.hpp"

class Apple {
    public:
        Apple() = default;
        ~Apple() = default;
        void newPos(std::vector<pos_t>, std::vector<std::string>);
        pos_t getPos() const;

    protected:
    private:
        pos_t _pos;
};
