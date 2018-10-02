# Copyright 2018 Ricardo Delfin
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

project(src)

set(pwd ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB src ${pwd}/*.cpp)

add_library(maguey STATIC ${src})

message("LINKING")
message("SDL2: ${SDL2_LIBRARY}")
message("Glew LIBRARIES: ${GLEW_LIBRARIES}")
message("Glew LIBRARY: ${GLEW_LIBRARY}")
message("GLM library dir: ${glm_LIBRARY_DIRS}")
message("GLM libraries: ${glm_LIBRARIES}")
message("GLM library: ${glm_LIBRARY}")
message("OpenGL include: ${OPENGL_INCLUDE_DIRS}")
message("OpenGL library dirs: ${OPENGL_LIBRARY_DIRS}")
message("OpenGL Library: ${OPENGL_gl_LIBRARY}")

target_link_libraries(maguey ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${glm_LIBRARY_DIRS} ${OPENGL_gl_LIBRARY})

install(TARGETS maguey
        EXPORT magueyTargets
        DESTINATION lib)
install(DIRECTORY ${pwd}/../include/
        DESTINATION include)