/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** IGame
*/

#pragma once

#include <vector>
#include <string>
#include <tuple>
#include "../core/Pos.hpp"

class IGame {
    public:
        virtual ~IGame() = default;
        /**
        * Function for loop through the game
        * @return Nothing
        */
        virtual void gameLoop() = 0;
        /**
        * Function for manage the key pressed
        * @param int ASCII of the key pressed
        * @return Nothing
        */
        virtual void gameKeys(int) = 0;
        /**
        * Function for restart the game from the beginning
        * @return Nothing
        */
        virtual void gameRestart() = 0;
        /**
        * Function who return the score
        * @return size_t Actual score
        */
        virtual size_t getScore() = 0;
        /**
        * Return the state of the player
        * @return true if alive, false if dead
        */
        virtual bool isAlive() = 0;
        /**
        * Function for load the map directly in a class variable
        * @return Nothing
        */
        virtual void loadMap() = 0;
        /**
        * Function for parse the map and create enemies or player if you encounter the right ascii character
        * @return Nothing
        */
        virtual void parseMap() = 0;
        /**
        * Return the map
        * @return std::vector<std::string> map in ASCII
        */
        virtual std::vector<std::string> getMap() = 0;
        /**
        * Return a vector with all the info for the assets
        * @return vector of <ASCII in map, ASCII to print, path to image>
        */
        virtual std::vector<std::tuple<char, char, std::string>> getAssets() = 0;
        /**
        * Function for get the specific element to print
        * @return vector of <pair<ASCII to print, position to print>>
        */
        virtual std::vector<std::pair<char, pos_t>> getElements() = 0;
        /**
        * Function who will check if the player run into wall, ennemies, ...
        * @return Nothing
        */
        virtual void checkCollision() = 0;
        /**
        * Function who return Id of the game
        * @return std::string ID of the game
        */
        virtual std::string getId() = 0;

    protected:
    private:
};
