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
