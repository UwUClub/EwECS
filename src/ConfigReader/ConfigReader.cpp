#include "EwECS/ConfigReader/ConfigReader.hpp"
#include <fstream>
#include <iostream>

ConfigReader::ConfigReader(const std::string &aJsonPath)
{
    loadConfig(aJsonPath);
}

json &ConfigReader::loadConfig(const std::string &aJsonPath)
{
    std::ifstream file(aJsonPath);

    if (!file.is_open()) {
        std::cerr << "Error: " << aJsonPath << " not found" << std::endl;
        throw std::runtime_error("Config file not found");
    }

    if (_data.find(aJsonPath) != _data.end()) {
        return _data[aJsonPath];
    }

    try {
        _data[aJsonPath] = json::parse(file);
        return _data[aJsonPath];
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Config file not found");
    }
}

json &ConfigReader::get(const std::string &aConfigName)
{
    if (_data.find(aConfigName) == _data.end()) {
        loadConfig(aConfigName);
    }
    return _data[aConfigName];
}
