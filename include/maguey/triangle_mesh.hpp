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

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <maguey/renderable.hpp>
#include <maguey/program.hpp>

namespace maguey {

class TriangleMesh : public Renderable {
 public:
    TriangleMesh();

    void load(const std::vector<glm::vec3>& vpos, const Program& program);

    void render() override;

    virtual ~TriangleMesh();
 private:
    std::unique_ptr<std::vector<glm::vec3>> vertices;

    GLuint buffer, vao;
    Program program;
};

}  // namespace maguey
