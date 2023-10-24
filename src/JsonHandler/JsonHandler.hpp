#ifndef ECS_JSONHANDLER_HPP
#define ECS_JSONHANDLER_HPP

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace ECS {
    class JsonHandler
    {
        public:
            /**
             * @brief Construct a new Json Handler object
             */
            JsonHandler() = default;

            /**
             * @brief Destroy the Json Handler object
             */
            ~JsonHandler() = default;

            /**
             * @brief Load a json file
             * @param path The path to the json file
             */
            void loadJson(const std::string &path);

            /**
             * @brief Get the json object
             * @return json& The json object
             * @note The json object is a reference
             */
            json &get();

        private:
            json m_json;
    }
} // namespace ECS

#endif // ECS_JSONHANDLER_HPP
