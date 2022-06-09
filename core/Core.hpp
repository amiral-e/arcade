/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Core
*/

#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "../graphics/IGraphic.hpp"
#include "../games/IGame.hpp"
#include "Keys.hpp"

typedef enum state_e {
    MENU,
    GAME,
    OVER
} state_t;

typedef enum tclock_e {
    DISP,
    PLAY
} tclock_t;

class Core {
    public:
        Core();
        ~Core();
        void loadGraphic(std::string);
        void loadGame(std::string);
        void closeGraphic();
        void closeGame();
        void switchGraphic(std::string);
        void switchGame(std::string);
        void searchLibs();
        void saveLib(std::filesystem::path);
        void saveScore();
        void loadScore();
        void displayMenu();
        void displayGame();
        void displayOver();
        void keyMan(int);
        void keyLib(int);
        void keyMenu(int);
        void keyGame(int);
        void keyOver(int);
        void loop();

    protected:
    private:
        std::vector<std::pair<std::string, std::string>> _graphics;
        std::vector<std::pair<std::string, std::string>> _games;
        std::vector<std::string> _scores;
        void *_handlGraphic;
        void *_handlGame;
        IGraphic *_libGraphic;
        IGame *_libGame;
        std::string _name;
        std::pair<int, int> _choice;
        state_t _state;
};
