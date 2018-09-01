#pragma once

#include <string>
#include <cstdint>

namespace maguey {

enum ShaderType {
    VERT_SHADER,
    GEOM_SHADER,
    FRAG_SHADER,
};

class Shader {
public:
    Shader();
    Shader(ShaderType type, const std::string& content, bool is_file = true);

    void load();
    int32_t get_program_id();

    ~Shader();
private:
    int32_t program_id;
    std::string program;
    ShaderType type;
};

}  // namespace maguey
