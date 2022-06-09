/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** IGraphic
*/

#pragma once

#include <vector>
#include <tuple>
#include <string>
#include "../core/Pos.hpp"

class IGraphic {
    public:
        virtual ~IGraphic() = default;
        /**
        * Function for load the assets (in ASCII or path for image)
        * @param std::vector<std::tuple<c ,d, std::string>>
        * @param c Char in the ASCII map
        * @param d Char to print if in ASCII
        * @param std::string path to image
        * @return nothing
        */
        virtual void assetsLoad(std::vector<std::tuple<char, char, std::string>>) = 0;
        /**
        * Function for refresh the window
        * @return nothing
        */
        virtual void windowRefresh() = 0;
        /**
        * Function for clear the window
        * @return nothing
        */
        virtual void windowClear() = 0;
        /**
        * Function for close the window
        * @return nothing
        */
        virtual void windowClose() = 0;
        /**
        * Return the window state as a boolean
        * @return true if open, false if closed
        */
        virtual bool isRunning() = 0;
        /**
        * Get the ASCII code of the key pressed
        * @return ASCII of the key pressed
        */
        virtual int getKey() = 0;
        /**
        * Get the window width
        * @return window's width
        */
        virtual int getSize() = 0;
        /**
        * Function for print a text on the window at precisse coordonate
        * @param std::string String to print
        * @param pos_t Position of the text
        * @return Nothing
        */
        virtual void printText(std::string, pos_t) = 0;
        /**
        * Function for print map
        * @param std::string Path to map
        * @param pos_t Corner top left of the start to print
        * @return Nothing
        */
        virtual void printMap(std::vector<std::string>, pos_t) = 0;
        /**
        * Function for print a text on the window at precisse coordonate
        * @param std::vector<std::pair<char, pos>>
        * @param char ID of the element
        * @param pos Position for the element
        * @param pos_t Corner top left of the start to print
        * @return Nothing
        */
        virtual void printElements(std::vector<std::pair<char, pos_t>>, pos_t) = 0;
        /**
        * Function for find specific ID in a list of assets
        * @param char ID
        * @return Position of this ID in assets list
        */
        virtual int findTuple(char) = 0;

    protected:
    private:
};
