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

#include <sstream>
#include <string>

#include <glm/glm.hpp>

template<class T>
std::string vec_str(const glm::tvec1<T>& v) {
    std::stringstream ss;
    ss << "(" << v[0] << ")";
    return ss.str();
}

template<class T>
std::string vec_str(const glm::tvec2<T>& v) {
    std::stringstream ss;
    ss << "(" << v[0] << ", " << v[1] << ")";
    return ss.str();
}

template<class T>
std::string vec_str(const glm::tvec3<T>& v) {
    std::stringstream ss;
    ss << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    return ss.str();
}

template<class T>
std::string vec_str(const glm::tvec4<T>& v) {
    std::stringstream ss;
    ss << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
    return ss.str();
}

template<class T>
std::string mat_str(const glm::tmat2x2<T>& m) {
    std::stringstream ss;
    ss << "(" << m[0][0] << ", " << m[1][0] << std::endl
       << " " << m[0][1] << ", " << m[1][1] << ")" << std::endl;
    return ss.str();
}

template<class T>
std::string mat_str(const glm::tmat3x3<T>& m) {
    std::stringstream ss;
    ss << "(" << m[0][0] << ", " << m[1][0] << ", " << m[2][0] << std::endl
       << " " << m[0][1] << ", " << m[1][1] << ", " << m[2][1] << std::endl
       << " " << m[0][2] << ", " << m[1][2] << ", " << m[2][2]
       << ")" << std::endl;
    return ss.str();
}

template<class T>
std::string mat_str(const glm::tmat4x4<T>& m) {
    std::stringstream ss;
    ss << "(" << m[0][0] << ", " << m[1][0]
       << ", " << m[2][0] << ", " << m[3][0] << std::endl

       << " "  << m[0][1] << ", " << m[1][1]
       << ", " << m[2][1] << ", " << m[3][1] << std::endl

       << " "  << m[0][2] << ", " << m[1][2]
       << ", " << m[2][2] << ", " << m[3][2] << std::endl
       << " "  << m[0][3] << ", " << m[1][3]
       << ", " << m[2][3] << ", " << m[3][3] << ")" << std::endl;
    return ss.str();
}