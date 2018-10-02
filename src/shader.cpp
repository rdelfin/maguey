// Copyright 2018 Ricardo Delfin
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#define GLM_FORCE_RADIANS

#include <maguey/shader.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>

#include <maguey/internal/debuggl.hpp>


namespace maguey {

GLint shader_type_to_gl(maguey::ShaderType type) {
    switch (type) {
        case VERT_SHADER: return GL_VERTEX_SHADER;
        case GEOM_SHADER: return GL_GEOMETRY_SHADER;
        case FRAG_SHADER: return GL_FRAGMENT_SHADER;
        default: std::cerr << "SHADER TYPE DOES NOT MATCH UP TO OPENGL"
                           << std::endl;
    }

    return 0;
}

Shader::Shader() { }

Shader::Shader(ShaderType type, const std::string& content, bool is_file)
        : program(content), type(type) {
    if (is_file) {
        std::ifstream file(content);
        this->program = std::string(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
    }
}

void Shader::load() {
    GLint result = GL_FALSE;
    int log_len;

    CHECK_GL_ERROR(
        this->program_id = glCreateShader(shader_type_to_gl(this->type)));
    const char* source = this->program.c_str();
    CHECK_GL_ERROR(glShaderSource(this->program_id, 1, &source, NULL));
    CHECK_GL_ERROR(glCompileShader(this->program_id));

    // Check Vertex Shader
    CHECK_GL_ERROR(glGetShaderiv(this->program_id, GL_COMPILE_STATUS, &result));
    CHECK_GL_ERROR(
        glGetShaderiv(this->program_id, GL_INFO_LOG_LENGTH, &log_len));
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
