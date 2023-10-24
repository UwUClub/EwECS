#ifndef CONFIG_READER_HPP_
#define CONFIG_READER_HPP_

#include <nlohmann/json.hpp>
#include <unordered_map>
using json = nlohmann::json;

static const std::string CONFIG_PATH = "assets/config/r-type.json";

/**
 * @brief ConfigReader class is used to read the config files
 */
class ConfigReader
{
    private:
        std::unordered_map<std::string, json> _configPaths;
        json _data;

    public:
        /**
         * @brief Construct a new ConfigReader object
         *
         */
        ConfigReader() = default;

        explicit ConfigReader(const std::string &);

        /**
         * @brief Destroy the ConfigReader object
         *
         */
        ~ConfigReader() = default;

        /**
         * @brief Get an Instance of the ConfigReader (singleton)
         *
         * @return ConfigReader&
         */
        static ConfigReader &getInstance()
        {
            static ConfigReader instance;

            return instance;
        }

        /**
         * @brief Load the config file
         *
         */
        void loadConfig(const std::string &jsonPath);

        /**
         * @brief Get all the config
         *
         * @return All the config
         */
        json &get(const std::string &configName);
};

#endif