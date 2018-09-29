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

#include <glm/glm.hpp>

#include <maguey/uniform.hpp>

namespace maguey {

class Camera {
 public:
    Camera();
    Camera(const glm::vec3& up, const glm::vec3& center, const glm::vec3& pos,
           size_t screen_width, size_t screen_height);

    Camera(const Camera&) = delete;

    Camera& operator=(const Camera&) = delete;

    void* getPerspectiveMatrix();
    void* getViewMatrix();

    Uniform createPerspectiveMatrixUniform();
    Uniform createViewMatrixUniform();

    virtual ~Camera();

 private:
    void update_all();

    glm::vec3 up;
    glm::vec3 left;
    glm::vec3 forwards;
    glm::vec3 position;
    float swidth, sheight;

    glm::mat4 perspective_mat, view_mat;
};

}  // namespace maguey
