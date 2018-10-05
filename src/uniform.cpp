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

#include<maguey/uniform.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <maguey/internal/debuggl.hpp>

namespace maguey {

struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};


std::unordered_map<UniformType, std::function<void(GLint, void*)>,
                   EnumClassHash>
    uniform_func_map = {
    {
        UNIFORM_FLOAT,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform1f(loc, *reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_INT,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform1i(loc, *reinterpret_cast<int*>(data)));
        },
    },
    {
        UNIFORM_FVEC_1,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform1fv(loc, 1,
                                        reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_FVEC_2,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform2fv(loc, 1,
                                        reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_FVEC_2,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform2fv(loc, 1,
                                        reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_FVEC_3,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform3fv(loc, 1,
                                        reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_IVEC_1,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform1iv(loc, 1, reinterpret_cast<int*>(data)));
        },
    },
    {
        UNIFORM_IVEC_2,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform2iv(loc, 1, reinterpret_cast<int*>(data)));
        },
    },
    {
        UNIFORM_IVEC_3,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform3iv(loc, 1, reinterpret_cast<int*>(data)));
        },
    },
    {
        UNIFORM_IVEC_4,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform4iv(loc, 1, reinterpret_cast<int*>(data)));
        },
    },
    {
        UNIFORM_UVEC_1,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform1uiv(loc, 1,
                                         reinterpret_cast<unsigned*>(data)));
        },
    },
    {
        UNIFORM_UVEC_2,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform2uiv(loc, 1,
                                         reinterpret_cast<unsigned*>(data)));
        },
    },
    {
        UNIFORM_UVEC_3,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform3uiv(loc, 1,
                                         reinterpret_cast<unsigned*>(data)));
        },
    },
    {
        UNIFORM_UVEC_4,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniform4uiv(loc, 1,
                                         reinterpret_cast<unsigned*>(data)));
        },
    },
    {
        UNIFORM_FMAT_2,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniformMatrix2fv(loc, 1, false,
                                              reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_FMAT_3,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniformMatrix3fv(loc, 1, false,
                                              reinterpret_cast<float*>(data)));
        },
    },
    {
        UNIFORM_FMAT_4,
        [](GLint loc, void* data) {
            CHECK_GL_ERROR(glUniformMatrix4fv(loc, 1, false,
                                              reinterpret_cast<float*>(data)));
        },
    },
};

Uniform::Uniform() {
}

Uniform::Uniform(void* data, UniformType type, const std::string& uniform_name)
                 : data(data), type(type), uniform_name(uniform_name),
                   loc_set(false) {
}

void Uniform::enable(GLint program_id) {
    if (!loc_set) {
        CHECK_GL_ERROR(this->loc = glGetUniformLocation(
                           program_id, uniform_name.c_str()));
        loc_set = true;
    }
    uniform_func_map[this->type](this->loc, this->data);
}

void Uniform::update_data_ptr(void* new_data) {
    this->data = new_data;
}

Uniform::~Uniform() {
}


}  // namespace maguey
