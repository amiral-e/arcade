/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** Exception
*/

#pragma once

#include <string>
#include <exception>

class ExceptionGraphic : public std::exception {
    public:
        ExceptionGraphic(const std::string &message) noexcept { _message = message; };
        ~ExceptionGraphic() = default;
        const char *what() const noexcept override { return _message.c_str(); };

    protected:
    private:
        std::string _message;
};

class ExceptionGame : public std::exception {
    public:
        ExceptionGame(const std::string &message) noexcept { _message = message; };
        ~ExceptionGame() = default;
        const char *what() const noexcept override { return _message.c_str(); };

    protected:
    private:
        std::string _message;
};
