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

#include <SDL2/SDL.h>

#include <iostream>

#include <maguey/game.hpp>
#include <maguey/internal/cleanup.hpp>


namespace maguey {

Game::Game() { }

Game::Game(const std::string& window_name, size_t width, size_t height)
    : window_name(window_name), window_width(width), window_height(height),
      camera(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, -1)) { }

void Game::run() {
    bool quit = false;
    SDL_Event e;
    SDL_GLContext glContext;

    // Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "There was an error running SDL_Init" << std::endl;
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Maguey test", 100, 100,
                                          this->window_width,
                                          this->window_height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "There was an error running SDL_CreateWindow" << std::endl;
        SDL_Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cerr << "There was an error running SDL_GL_CreateContext"
                  << std::endl;
        cleanup(window);
        SDL_Quit();
        return;
    }

    glewInit();

    this->load(&this->camera);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        this->update(&this->camera);

        glClearColor(0.390625f, 0.58203125f, 0.92578125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->render(&this->camera);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    cleanup(window);
    SDL_Quit();
}

Game::~Game() { }

}  // namespace maguey
