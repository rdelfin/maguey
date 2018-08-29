#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>

#include <maguey/cleanup.h>

#include <iostream>
#include <vector>


const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;

const std::string VERT_SHADER = R"zzz(
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

const std::string FRAG_SHADER = R"zzz(
#version 330 core
in vec3 frag_color;
out vec3 color;
void main(){
  color = frag_color;
}
)zzz";

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

GLuint load_shaders(const std::string& vertex_shader, const std::string& fragment_shader){

    // Create the shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int log_len;

    // Compile Vertex Shader
    const char* vshader_ptr = vertex_shader.c_str();
    glShaderSource(vertex_shader_id, 1, &vshader_ptr, NULL);
    glCompileShader(vertex_shader_id);

    // Check Vertex Shader
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> error_msg(log_len + 1);
        glGetShaderInfoLog(vertex_shader_id, log_len, NULL, &error_msg[0]);
        printf("%s\n", &error_msg[0]);
    }

    // Compile Fragment Shader
    const char* fshader_ptr = fragment_shader.c_str();
    glShaderSource(fragment_shader_id, 1, &fshader_ptr, NULL);
    glCompileShader(fragment_shader_id);

    // Check Fragment Shader
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> error_msg(log_len + 1);
        glGetShaderInfoLog(fragment_shader_id, log_len, NULL, &error_msg[0]);
        printf("%s\n", &error_msg[0]);
    }

    // Link the program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> error_msg(log_len + 1);
        glGetProgramInfoLog(program_id, log_len, NULL, &error_msg[0]);
        printf("%s\n", &error_msg[0]);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

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

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint programID = load_shaders(VERT_SHADER, FRAG_SHADER);

    while(!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        glClearColor(0.390625f, 0.58203125f, 0.92578125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

       // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    cleanup(window);
    SDL_Quit();
    return 0;
}
