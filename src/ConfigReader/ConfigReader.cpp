#include "EwECS/ConfigReader/ConfigReader.hpp"
#include <fstream>
#include <iostream>

ConfigReader::ConfigReader(const std::string &aJsonPath)
{
    loadConfig(aJsonPath);
}

void ConfigReader::loadConfig(const std::string &aJsonPath)
{
    std::ifstream file(aJsonPath);

    if (!file.is_open()) {
        std::cerr << "Error: " << aJsonPath << " not found" << std::endl;
        return;
    }

    try {
        _data[aJsonPath] = json::parse(file);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

json &ConfigReader::get(const std::string &aConfigName)
{
    if (_data.find(aConfigName) == _data.end()) {
        loadConfig(aConfigName);
    }
    return _data[aConfigName];
}
