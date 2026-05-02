# The MIT License (MIT)
# 
# Copyright (C) 2026 Dominick Ohara
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the “Software”), 
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, 
# and/or sell copies of the Software, and to permit persons to whom the 
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included 
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 4.00)

#if this is on, assimp will not compile. (option from assimp CMakeLists.txt)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)

project(cube_renderer)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

FetchContent_Declare(
    glfw_external
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
    FIND_PACKAGE_ARGS NAMES glfw
)

FetchContent_Declare(
    glad_external
    GIT_REPOSITORY https://github.com/Dav1dde/glad
    GIT_TAG v2.0.8
    FIND_PACKAGE_ARGS NAMES glad
)

FetchContent_Declare(
    glm_external
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 1.0.3
    FIND_PACKAGE_ARGS NAMES glm
)

FetchContent_Declare(
    assimp_external
    GIT_REPOSITORY https://github.com/assimp/assimp
    GIT_TAG v6.0.4
    FIND_PACKAGE_ARGS NAMES assimp
)

FetchContent_Declare(
    stb_external
    GIT_REPOSITORY https://github.com/nothings/stb
)

FetchContent_MakeAvailable(
    glfw_external
    glad_external
    glm_external
    stb_external
    assimp_external
)

# since stb is not a CMake project, need to set it up manually
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_external_SOURCE_DIR})
target_compile_features(stb INTERFACE c_std_99)

# initalize glad
#https://deepwiki.com/Dav1dde/glad/5.1-cmake-integration
set(GLAD_CMAKE_PATH ${glad_external_SOURCE_DIR}/cmake)
add_subdirectory("${GLAD_CMAKE_PATH}" "glad_cmake")
glad_add_library(glad API gl:core=4.6)

add_subdirectory(app)