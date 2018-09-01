#pragma once

#include <maguey/shader.hpp>

#include <cstdint>

namespace maguey {

class Program {
public:
    Program();
    Program(const Shader& vertex_shader, const Shader& fragment_shader);
    Program(const std::string& vertex_shader, const std::string&fragment_shader,
            bool is_file = true);

    void load();

    void enable();

    ~Program();
private:
    Shader vertex_shader, fragment_shader;
    int32_t program_id;
};

}  // namespace maguey
