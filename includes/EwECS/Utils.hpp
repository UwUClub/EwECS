#ifndef UTILS_HPP
#define UTILS_HPP

#include <libgen.h>
#include <linux/limits.h>
#include <string>
#include <unistd.h>
namespace ECS::Utils {
    struct Vector2i
    {
            Vector2i();

            Vector2i(int aX, int aY);

            int x;
            int y;
    };

    struct Vector2f
    {
            Vector2f();

            Vector2f(float aX, float aY);

            float x;
            float y;
    };

    static std::string getFilePathInstall()
    {
#if defined(__linux__)
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count < 0 || count >= PATH_MAX) {
            return "./";
        }
        result[count] = '\0';
        char *dir = dirname(result);
        if (dir == nullptr) {
            return "./";
        }
        return (std::string(dir) + "/");
#else
        return "./";
#endif
    }
} // namespace ECS::Utils

#endif // !
