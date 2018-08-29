#pragma once

#include <string>

namespace maguey {

class Game {
public:
    Game();
    Game(const std::string& window_name, size_t width, size_t height);

    void run();

    virtual ~Game();

protected:
    virtual void load() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    std::string window_name;
    size_t window_width, window_height;
};

}   // namespace maguey