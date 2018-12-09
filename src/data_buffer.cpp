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

#include <GL/glew.h>
#include <GL/gl.h>

#include <maguey/data_buffer.hpp>
#include <maguey/internal/debuggl.hpp>

namespace maguey {

DataBuffer::DataBuffer() { }

DataBuffer::DataBuffer(GLuint vao) {
    CHECK_GL_ERROR(glGenBuffers(1, &this->buffer));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
    this->bindData();
}

void DataBuffer::bindAttrib(GLuint vao) {
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, this->buffer));
    CHECK_GL_ERROR(glVertexAttribPointer(vao, 3, GL_FLOAT, GL_FALSE, 0,
                                         nullptr));
}

}  // namespace maguey
