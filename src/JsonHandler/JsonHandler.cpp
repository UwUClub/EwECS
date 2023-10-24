#include "JsonHandler.hpp"
#include <fstream>

namespace ECS {
    void JsonHandler::loadJson(const std::string &path)
    {
        std::ifstream file(path);
        m_json = json::parse(file);
    }

    json &JsonHandler::get()
    {
        return m_json;
    }
} // namespace ECS