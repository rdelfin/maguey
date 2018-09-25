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

#include <vector>

#include <glm/glm.hpp>

#include <maguey/maguey.hpp>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const char VERT_SHADER[] = R"zzz(
#version 330 core
layout(location = 0) in vec3 pos_model;

void main() {
    gl_Position.xyz = pos_model;
    gl_Position.w = 1.0;
}
)zzz";

const char FRAG_SHADER[] = R"zzz(
#version 330 core
out vec3 color;
void main() {
    color = vec3(1.0, 1.0, 0.0);
}
)zzz";

static const std::vector<glm::vec3> points = {
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
};

class MainGame : public maguey::Game {
 public:
    MainGame() : maguey::Game("Mesh test", 1920, 1080),
        program(std::string(VERT_SHADER), std::string(FRAG_SHADER), false) { }

 protected:
    void load() override {
        this->program.load();
        this->mesh.load(points);
    }

    void update() override { }

    void render() override {
        this->program.enable();
        this->mesh.render();
    }

 private:
    maguey::Program program;
    maguey::TriangleMesh mesh;
};


int main() {
    MainGame game;
    game.run();
    return 0;
}
