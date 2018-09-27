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

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#define CHECK_SUCCESS(x)   \
  do {                     \
    if (!(x)) {            \
      glfwTerminate();     \
      exit(EXIT_FAILURE);  \
    }                      \
  } while (0)

#define CHECK_GL_SHADER_ERROR(id)                                           \
  do {                                                                      \
    GLint status = 0;                                                       \
    GLint length = 0;                                                       \
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);                          \
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);                         \
    if (status != GL_TRUE) {                                                \
      std::string log(length, 0);                                           \
      glGetShaderInfoLog(id, length, nullptr, &log[0]);                     \
      std::cerr << "Line " << __FILE__ << ":" << __LINE__                   \
                << " Status: " << status                                    \
                << " OpenGL Shader Error: Log = \n"                         \
                << &log[0];                                                 \
      std::cerr << length << " bytes\n";                                    \
      SDL_Quit();                                                           \
      exit(EXIT_FAILURE);                                                   \
    }                                                                       \
  } while (0)

#define CHECK_GL_PROGRAM_ERROR(id)                                           \
  do {                                                                       \
    GLint status = 0;                                                        \
    GLint length = 0;                                                        \
    glGetProgramiv(id, GL_LINK_STATUS, &status);                             \
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);                         \
    if (status != GL_TRUE) {                                                 \
      std::string log(length, 0);                                            \
      glGetProgramInfoLog(id, length, nullptr, &log[0]);                     \
      std::cerr << "Line " << __FILE__ << ":" << __LINE__                    \
                << " OpenGL Program Error: Log = \n"  << &log[0];            \
      SDL_Quit();                                                            \
      exit(EXIT_FAILURE);                                                    \
    }                                                                        \
  } while (0)

#define CHECK_GL_ERROR(statement)                                             \
  do {                                                                        \
    { statement; }                                                            \
    GLenum error = GL_NO_ERROR;                                               \
    if ((error = glGetError()) != GL_NO_ERROR) {                              \
      std::cerr << "Line " << __FILE__ << ":" << __LINE__                     \
                << " OpenGL Error: code  = " << error                         \
                << " description =  "                                         \
                << DebugGLErrorToString(static_cast<int>(error))              \
                << std::endl;                                                 \
      SDL_Quit();                                                             \
      exit(EXIT_FAILURE);                                                     \
    }                                                                         \
  } while (0)

const char* DebugGLErrorToString(int error);
