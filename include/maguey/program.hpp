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

#include <cstdint>
#include <string>
#include <vector>

#include <maguey/shader.hpp>
#include <maguey/uniform.hpp>

namespace maguey {

class Program {
 public:
    Program();
    Program(const Shader& vertex_shader, const Shader& fragment_shader,
            std::vector<Uniform> uniforms = {});
    Program(const std::string& vertex_shader, const std::string&fragment_shader,
            std::vector<Uniform> uniforms = {}, bool is_file = true);

    void load();

    void enable();

    ~Program();
 private:
    Shader vertex_shader, fragment_shader;
    std::vector<Uniform> uniforms;
    int32_t program_id;
};

}  // namespace maguey
