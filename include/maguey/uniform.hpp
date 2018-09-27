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

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include <functional>
#include <string>
#include <unordered_map>

namespace maguey {

enum UniformType {
    UNIFORM_FLOAT,
    UNIFORM_INT,
    UNIFORM_FVEC_1,
    UNIFORM_FVEC_2,
    UNIFORM_FVEC_3,
    UNIFORM_FVEC_4,
    UNIFORM_IVEC_1,
    UNIFORM_IVEC_2,
    UNIFORM_IVEC_3,
    UNIFORM_IVEC_4,
    UNIFORM_UVEC_1,
    UNIFORM_UVEC_2,
    UNIFORM_UVEC_3,
    UNIFORM_UVEC_4,
    UNIFORM_FMAT_2,
    UNIFORM_FMAT_3,
    UNIFORM_FMAT_4,
};


class Uniform {
 public:
    Uniform();
    Uniform(void* data, UniformType type, const std::string& unifrom_name);

    void enable(GLint program_id);
    void update_data_ptr(void* new_data);

    virtual ~Uniform();

 private:
    void* data;
    UniformType type;
    std::string uniform_name;
    bool loc_set;
    int loc;
};

}  // namespace maguey
