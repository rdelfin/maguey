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

#include <maguey/maguey.hpp>


const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;

const char VERT_SHADER[] = R"zzz(
#version 330 core
layout(location = 0) in vec3 pos_model;
layout(location = 1) in vec3 vert_color;
out vec3 frag_color;
void main(){
    gl_Position.xyz = pos_model;
    gl_Position.w = 1.0;
    frag_color = vert_color;
}
)zzz";

const char FRAG_SHADER[] = R"zzz(
#version 330 core
in vec3 frag_color;
out vec3 color;
void main(){
  color = frag_color;
}
)zzz";

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

static const GLfloat g_color_buffer_data[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};


class MainGame : public maguey::Game {
 public:
    MainGame() : maguey::Game("Display test", 1920, 1080),
        program(VERT_SHADER, FRAG_SHADER, {}, false) { }
    virtual ~MainGame() {}

 protected:
    void load() override {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);


        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                     g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
                     g_color_buffer_data, GL_STATIC_DRAW);

        this->program.load();
    }

    void update(maguey::Camera* camera) override { }

    void render(maguey::Camera* camera) override {
        this->program.enable();

       // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but
                                // must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            nullptr);           // array buffer offset

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but
                                // must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            nullptr);           // array buffer offset

        // Draw the triangle !
        // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

 private:
    maguey::Program program;
    GLuint vertexbuffer;
    GLuint colorbuffer;
};

int main() {
    MainGame game;
    game.run();
    return 0;
}
