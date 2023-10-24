#include "EwECS/ConfigReader/ConfigReader.hpp"
#include <fstream>
#include <iostream>

void ConfigReader::loadConfig(const std::string &aJsonPath)
{
    std::ifstream f(aJsonPath);
    _data = json::parse(f);
}

json &ConfigReader::get()
{
    return _data;
}