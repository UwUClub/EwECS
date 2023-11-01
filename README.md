# EwECS

## Contents

- [Requirements](#requirements)
- [Dependencies](#dependencies)
- [Communication](#communication)
- [Installation from source](#installation-from-source)
- [Compilation](#compilation)
- [Credits](#credits)
- [License](#license)

## Requirements

- [GCC](https://gcc.gnu.org/) 13.2+ is required
- [CMake](https://cmake.org/) 3.16+ is required
- [Git](https://git-scm.com/) 2.25+ is required&

## Dependencies (automatically installed)

- [SFML](https://www.sfml-dev.org/)
- [Boost](https://www.boost.org/)

## Communication

- If you have a bug or an issue, please contact us.
- If you want to contribute, please contact us.

## Installation in your project

### SSH

```bash
git submodule add --init --recursive --remote
```

And add the following lines to your CMakeLists.txt

```cmake
add_subdirectory(EwECS)
target_link_libraries(${PROJECT_NAME} PRIVATE EwECS)
```

## Compilation

### Using CMake

```bash
cmake -S . -B build && cmake --build build -j
```

## Credits

- Valentin Gegoux
- Baptiste Laran
- Mathéo Martin
- Maxence Labourel

## License

EwECS is developped by the UwUClub for Epitech.
