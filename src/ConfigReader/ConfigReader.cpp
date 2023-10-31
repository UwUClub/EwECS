#include "EwECS/ConfigReader/ConfigReader.hpp"
#include <fstream>
#include <iostream>
#include "Utils.hpp"

ConfigReader::ConfigReader(const std::string &aJsonPath)
{
    std::string path = ECS::Utils::getFilePathInstall() + aJsonPath;
    loadConfig(path);
}

json &ConfigReader::loadConfig(const std::string &aJsonPath)
{
    std::string path = ECS::Utils::getFilePathInstall() + aJsonPath;
    std::ifstream file(path);

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
