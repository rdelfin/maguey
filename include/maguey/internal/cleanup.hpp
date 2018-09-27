
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

#include <SDL2/SDL.h>

#include <utility>

/*
 * Recurse through the list of arguments to clean up, cleaning up
 * the first one in the list each iteration.
 */
template<typename T, typename... Args>
void cleanup(T *t, Args&&... args) {
    // Cleanup the first item in the list
    cleanup(t);
    // Clean up the remaining arguments
    cleanup(std::forward<Args>(args)...);
}

/*
 * These specializations serve to free the passed argument and also provide the
 * base cases for the recursive call above, eg. when args is only a single
 * item one of the specializations below will be called by
 * cleanup(std::forward<Args>(args)...), ending the recursion
 */
template<>
inline void cleanup<SDL_Window>(SDL_Window *win) {
    if (!win) {
        return;
    }
    SDL_DestroyWindow(win);
}
template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren) {
    if (!ren) {
        return;
    }
    SDL_DestroyRenderer(ren);
}
template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex) {
    if (!tex) {
        return;
    }
    SDL_DestroyTexture(tex);
}
template<>
inline void cleanup<SDL_Surface>(SDL_Surface *surf) {
    if (!surf) {
        return;
    }
    SDL_FreeSurface(surf);
}
