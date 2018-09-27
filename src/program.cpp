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

#include <maguey/program.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>

namespace maguey {

Program::Program() { }

Program::Program(const Shader& vertex_shader, const Shader& fragment_shader,
                 std::vector<Uniform> uniforms)
                 : vertex_shader(vertex_shader),
                   fragment_shader(fragment_shader), uniforms(uniforms) { }

Program::Program(const std::string& vertex_shader,
                 const std::string&fragment_shader,
                 std::vector<Uniform> uniforms, bool is_file)
                 : vertex_shader(ShaderType::VERT_SHADER, vertex_shader,
                                 is_file),
                   fragment_shader(ShaderType::FRAG_SHADER, fragment_shader,
                                   is_file), uniforms(uniforms) { }

void Program::load() {
    GLint result;
    int log_len;

    vertex_shader.load();
    fragment_shader.load();

    int vsid = vertex_shader.get_program_id();
    int fsid = fragment_shader.get_program_id();

    // Link the program
    this->program_id = glCreateProgram();
    glAttachShader(this->program_id, vsid);
    glAttachShader(this->program_id, fsid);
    glLinkProgram(this->program_id);

    // Check the program
    glGetProgramiv(this->program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(this->program_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> error_msg(log_len + 1);
        glGetProgramInfoLog(this->program_id, log_len, NULL, &error_msg[0]);
        printf("%s\n", &error_msg[0]);
    }

    glDetachShader(this->program_id, vsid);
    glDetachShader(this->program_id, fsid);

    glDeleteShader(vsid);
    glDeleteShader(fsid);
}

void Program::enable() {
    glUseProgram(this->program_id);
    for (Uniform& uniform : uniforms)
        uniform.enable(this->program_id);
}

Program::~Program() { }

}  // namespace maguey
