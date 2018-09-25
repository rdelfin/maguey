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

#include <maguey/triangle_mesh.hpp>

#include <memory>

namespace maguey {

TriangleMesh::TriangleMesh() { }

void TriangleMesh::load(const std::vector<glm::vec3>& pos) {
    this->vertices = std::unique_ptr<std::vector<glm::vec3>>(
        new std::vector<glm::vec3>(pos));
    glCreateVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices->size()*sizeof(glm::vec3),
                 this->vertices->data(), GL_STATIC_DRAW);
}

void TriangleMesh::render() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, this->vertices->size());
    glDisableVertexAttribArray(0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &buffer);
}

}  // namespace maguey
