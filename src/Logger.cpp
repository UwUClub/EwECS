/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** Logger
*/

#include "Logger.hpp"
#include <iostream>

void ECS::Logger::log(const std::string &aMessage)
{
    std::cout << aMessage << std::endl;
}

void ECS::Logger::log(const std::string &aMessage, const std::string &aFile)
{
    std::cout << aFile << ": " << aMessage << std::endl;
}

void ECS::Logger::error(const std::string &aMessage)
{
    std::cerr << aMessage << std::endl;
}

void ECS::Logger::error(const std::string &aMessage, const std::string &aFile)
{
    std::cerr << aFile << ": " << aMessage << std::endl;
}

void ECS::Logger::warning(const std::string &aMessage)
{
    std::cout << "Warning: " << aMessage << std::endl;
}

void ECS::Logger::warning(const std::string &aMessage, const std::string &aFile)
{
    std::cout << aFile << ": Warning: " << aMessage << std::endl;
}

void ECS::Logger::info(const std::string &aMessage)
{
    std::cout << "Info: " << aMessage << std::endl;
}

void ECS::Logger::info(const std::string &aMessage, const std::string &aFile)
{
    std::cout << aFile << ": Info: " << aMessage << std::endl;
}
