#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <maguey/game.hpp>
#include <maguey/internal/cleanup.h>

#include <iostream>


namespace maguey {

Game::Game() {

}

Game::Game(const std::string& window_name, size_t width, size_t height)
    : window_name(window_name), window_width(width), window_height(height) {

}

void Game::run() {
    bool quit = false;
    SDL_Event e;
    SDL_GLContext glContext;

    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "There was an error running SDL_Init" << std::endl;
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Maguey test", 100, 100, this->window_width,
        this->window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cerr << "There was an error running SDL_CreateWindow" << std::endl;
        SDL_Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if(glContext == nullptr) {
        std::cerr << "There was an error running SDL_GL_CreateContext" << std::endl;
        cleanup(window);
        SDL_Quit();
        return;
    }

    glewInit();

    this->load();

    while(!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        this->update();

        glClearColor(0.390625f, 0.58203125f, 0.92578125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->render();

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    cleanup(window);
    SDL_Quit();
}

Game::~Game() {

}

}  // namespace maguey