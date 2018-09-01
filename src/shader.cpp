#include <GL/glew.h>
#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>

#include <maguey/shader.hpp>


namespace maguey {

GLint shader_type_to_gl(maguey::ShaderType type) {
    switch(type) {
        case VERT_SHADER: return GL_VERTEX_SHADER;
        case GEOM_SHADER: return GL_GEOMETRY_SHADER;
        case FRAG_SHADER: return GL_FRAGMENT_SHADER;
        default: std::cerr << "SHADER TYPE DOES NOT MATCH UP TO OPENGL" << std::endl;
    }

    return 0;
}

Shader::Shader() {

}

Shader::Shader(ShaderType type, const std::string& content, bool is_file)
        : program(content), type(type) {
    if(is_file) {
        std::ifstream file(content);
        this->program = std::string(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
    }
}

void Shader::load() {
    GLint result = GL_FALSE;
    int log_len;

    this->program_id = glCreateShader(shader_type_to_gl(this->type));
    const char* source = this->program.c_str();
    glShaderSource(this->program_id, 1, &source, NULL);
    glCompileShader(this->program_id);

    // Check Vertex Shader
    glGetShaderiv(this->program_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(this->program_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> error_msg(log_len + 1);
        glGetShaderInfoLog(this->program_id, log_len, NULL, &error_msg[0]);
        printf("%s\n", &error_msg[0]);
    }
}

int32_t Shader::get_program_id() {
    return this->program_id;
}

Shader::~Shader() { }

}  // namespace maguey
