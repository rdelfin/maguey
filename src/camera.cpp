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

#include <iostream>

#include <maguey/camera.hpp>
#include <maguey/internal/debug_util.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace maguey {


Camera::Camera() {
}

Camera::Camera(const glm::vec3& up, const glm::vec3& center,
               const glm::vec3& pos, size_t swidth, size_t sheight)
               : swidth(swidth), sheight(sheight), position(pos) {
    this->forwards = glm::normalize(center - pos);
    this->left = glm::normalize(glm::cross(up, this->forwards));
    this->up = glm::normalize(glm::cross(this->forwards, left));
    this->update_all();
}

void* Camera::getProjectionMatrix() {
    return glm::value_ptr(this->projection_mat);
}

void* Camera::getViewMatrix() {
    return glm::value_ptr(this->view_mat);
}

Uniform Camera::createProjectionMatrixUniform() {
    return Uniform(this->getProjectionMatrix(), UNIFORM_FMAT_4, "projection");
}

Uniform Camera::createViewMatrixUniform() {
    return Uniform(this->getViewMatrix(), UNIFORM_FMAT_4, "view");
}

void Camera::setCamera(const glm::vec3& up, const glm::vec3& center,
                       const glm::vec3& pos) {
    this->forwards = glm::normalize(center - pos);
    this->left = glm::normalize(glm::cross(up, this->forwards));
    this->up = glm::normalize(glm::cross(this->forwards, this->left));
    this->update_all();
}

void Camera::update_all() {
    this->projection_mat = glm::perspectiveFov(2.0f, this->swidth,
                                               this->sheight, 0.5f, 1000.0f);
    this->view_mat = glm::lookAt(this->position,
                                 this->position + this->forwards, this->up);
}

Camera::~Camera() { }


}  // namespace maguey
