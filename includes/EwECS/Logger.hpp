/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

namespace ECS {
    class Logger
    {
        public:
        private:
            Logger() = default;
            Logger(Logger &&) = default;
            Logger(const Logger &) = default;
            Logger &operator=(Logger &&) = default;
            Logger &operator=(const Logger &) = default;
            ~Logger() = default;
    };
} // namespace ECS

#endif /* !LOGGER_HPP_ */
