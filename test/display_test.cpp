#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <SDL2/SDL.h>

#include <maguey/cleanup.h>

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

const int TILE_SIZE = 40;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main(int, char**){
    bool quit = false;
    SDL_Event e;
    SDL_GLContext glContext;

    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Maguey test", 100, 100, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }

    glContext = SDL_GL_CreateContext(window);
    if(glContext == nullptr) {
        logSDLError(std::cout, "createGLContext");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    glewInit();

    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
    //     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == nullptr){
    //     logSDLError(std::cout, "CreateRenderer");
    //     cleanup(window);
    //     SDL_Quit();
    //     return 1;
    // }

    while(!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        glClearColor(0.390625f, 0.58203125f, 0.92578125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window);

        //Render the scene
        //Note: This is within the program's main loop
        // SDL_RenderClear(renderer);
        // SDL_RenderPresent(renderer);
        // SDL_Delay(16);
    }

    cleanup(window);
    SDL_Quit();
    return 0;
}
