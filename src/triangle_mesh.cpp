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

#include <maguey/triangle_mesh.hpp>

#include <memory>

#include <maguey/internal/debuggl.hpp>

namespace maguey {

TriangleMesh::TriangleMesh() { }

void TriangleMesh::load(const std::vector<glm::vec3>& pos,
                        const Program& program) {
    this->program = program;
    this->vertices = std::unique_ptr<std::vector<glm::vec3>>(
        new std::vector<glm::vec3>(pos));

    this->program.load();

    CHECK_GL_ERROR(glCreateVertexArrays(1, &this->vao));
    CHECK_GL_ERROR(glBindVertexArray(this->vao));

    CHECK_GL_ERROR(glGenBuffers(1, &this->buffer));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER,
                                this->vertices->size()*sizeof(glm::vec3),
                                this->vertices->data(), GL_STATIC_DRAW));
}

void TriangleMesh::render() {
    this->program.enable();

    CHECK_GL_ERROR(glEnableVertexAttribArray(this->vao));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
    CHECK_GL_ERROR(glVertexAttribPointer(this->vao, 3, GL_FLOAT, GL_FALSE, 0,
                                         nullptr));
    CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, this->vertices->size()));
    CHECK_GL_ERROR(glDisableVertexAttribArray(this->vao));
}

TriangleMesh::~TriangleMesh() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &this->vao));
    CHECK_GL_ERROR(glDeleteBuffers(1, &buffer));
}

}  // namespace maguey
