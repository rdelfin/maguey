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

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include <maguey/maguey.hpp>
#include <maguey/internal/debug_util.hpp>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const char VERT_SHADER[] = R"zzz(
#version 330 core
layout(location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = vec4(pos, pos.z * -1.0f);
}
)zzz";

const char FRAG_SHADER[] = R"zzz(
#version 330 core
out vec3 color;
void main() {
    color = vec3(1.0, 1.0, 0.0);
}
)zzz";

static std::vector<glm::vec3> points = {
    glm::vec3(1.0f,  -1.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f,   1.0f, 0.0f),
};

class MainGame : public maguey::Game {
 public:
    MainGame() : maguey::Game("Mesh test", 800, 600) { }

    virtual ~MainGame() { }

 protected:
    void load(maguey::Camera* camera) override {
        glm::mat4 view = *reinterpret_cast<glm::mat4*>(camera->getViewMatrix());
        glm::mat4 proj = *reinterpret_cast<glm::mat4*>(
            camera->getProjectionMatrix());
        std::cout << "New points: " << std::endl;
        for (glm::vec3& point : points) {
            point = glm::vec3(proj * view * glm::vec4(point, 1.0f));
            std::cout << vec_str(point) << std::endl;
        }

        this->mesh.load(points, maguey::Program(
            std::string(VERT_SHADER), std::string(FRAG_SHADER),
            {
                camera->createProjectionMatrixUniform(),
                camera->createViewMatrixUniform(),
            }, false));
    }

    void update(maguey::Camera* camera) override { }

    void render(maguey::Camera* camera) override {
        this->mesh.render();
    }

 private:
    maguey::TriangleMesh mesh;
};


int main() {
    MainGame game;
    game.run();
    return 0;
}
