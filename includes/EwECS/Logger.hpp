/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
namespace ECS {
    class Logger
    {
        public:
            static void log(const std::string &aMessage);
            static void log(const std::string &aMessage, const std::string &aFile);
            static void error(const std::string &aMessage);
            static void error(const std::string &aMessage, const std::string &aFile);
            static void warning(const std::string &aMessage);
            static void warning(const std::string &aMessage, const std::string &aFile);
            static void info(const std::string &aMessage);
            static void info(const std::string &aMessage, const std::string &aFile);
    };
} // namespace ECS

#endif /* !LOGGER_HPP_ */
