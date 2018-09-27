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

#include <maguey/camera.hpp>

namespace maguey {

class Game {
 public:
    Game();
    Game(const std::string& window_name, size_t width, size_t height);

    void run();

    virtual ~Game();

 protected:
    virtual void load(Camera* camera) = 0;
    virtual void update(Camera* camera) = 0;
    virtual void render(Camera* camera) = 0;

 private:
    std::string window_name;
    size_t window_width, window_height;
    Camera camera;
};

}  // namespace maguey
