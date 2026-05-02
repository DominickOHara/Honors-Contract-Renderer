// =========================================================================
// main.cpp
// -------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (C) 2026 Dominick Ohara
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the “Software”), 
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included 
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// =========================================================================
// NOTICE (For academic submission)
// --------------------------------------------------------------------------
// All code in 'main.cpp' was created by Dominick Ohara with no reference or 
// source material unless specified. (other than API documentation).
// =========================================================================
// Usage
// --------------------------------------------------------------------------
// The TextureManager loads, manages, and binds textures.
// ==========================================================================

#include <iostream>
#include <vector>
#include <cstdint>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "TextureManager.hpp"

Camera* appCamera;

void framebufferCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    appCamera->framebufferCallback(window, width, height);
}

void processInput(GLFWwindow* window, float dt) {
     appCamera->processInput(window, dt);

}

void processMouseInput(GLFWwindow* window, double mousePosX, double mousePosY) {
     appCamera->processMouseInput(window, mousePosX, mousePosY);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Render the cubes", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // load opengl
    // glad loading from implementation references https://github.com/Dav1dde/glad/blob/glad2/README.md 
    int glVersion = gladLoadGL(glfwGetProcAddress);
    if (glVersion == 0) {
        std::cout << "Glad failed to load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Glad loaded opengl: " << GLAD_VERSION_MAJOR(glVersion) << '.' << GLAD_VERSION_MINOR(glVersion) << std::endl;

    glEnable(GL_DEPTH_TEST);

    // load shaders
    ShaderProgram appShader(ShaderProgram::Builder()
        .addShader("./resources/shaders/vertexShader.glsl",  GL_VERTEX_SHADER)
        .addShader("./resources/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER)
        .linkShaders()
    );

    appShader.useProgram();
    appShader.setUniformInt("textureAlbedo", 0);
    appShader.setUniformInt("textureNormal", 1);
    appShader.setUniformInt("textureRoughness", 2);
    appShader.setUniformInt("textureAO", 3);

    // setup camera
    appCamera = new Camera({0.0f,2.0f,-6.0f}, 800, 600);
    
    //setup model pos
    glm::mat4 modelTransform(1.0f);
    appShader.setUniformMat4("modelTransform", modelTransform);

    // setup lights
    glm::vec3 lightPositions[] = {
        {-10.0f, 10.0f, -10.0f},
        {-10.0f, 10.0f,  10.0f},
        { 10.0f, 10.0f, -10.0f},
        { 5.0f, 5.0f,  5.0f}
    };
    glm::vec3 lightColors[] = {
        {1.00f, 0.00f, 0.00f},
        {0.00f, 1.00f, 0.00f},
        {0.00f, 0.00f, 1.00f},
        {10.00f, 10.00f, 10.00f}
    };
    appShader.setUniformVec3Array("lightPositions", 4, lightPositions);
    appShader.setUniformVec3Array("lightColors", 4, lightColors);

    // load textures and assets
    TextureManager* textureManager = TextureManager::getInstance();

    textureManager->loadTexture(
        "./resources/textures/LION_4K_Albedo.jpg", 
        "lion_albedo"
    );
    textureManager->loadTexture(
        "./resources/textures/LION_4K_Normal.jpg", 
        "lion_normal"
    );
    textureManager->loadTexture(
        "./resources/textures/LION_4K_Roughness.jpg", 
        "lion_roughness"
    );
    textureManager->loadTexture(
        "./resources/textures/LION_4K_AO.jpg", 
        "lion_ao"
    );

    Model statue("./resources/models/LION_STATUE_CGT.obj");
    statue.setAlbedoTexture("lion_albedo");
    statue.setNormalTexture("lion_normal");
    statue.setRoughnessTexture("lion_roughness");
    statue.setAOTexture("lion_ao");

    // set callbacks
    glfwSetFramebufferSizeCallback(window, framebufferCallback);
    glfwSetCursorPosCallback(window, processMouseInput);
    
    // loop
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();
        processInput(window, dt);
        glfwSwapBuffers(window);

        appCamera->update(dt);
        
        // lights
        // angle hard set to 0 due to saftey concerns
        // of flashing lights
        float theta = 0.0;
        glm::vec3 lightPositions[] = {
        { 10.0f*cos(theta), 5.0f,   10.0f*sin(theta)},
        { 10.0f*sin(theta), 5.0f,  -10.0f*cos(theta)},
        {-10.0f*cos(theta), 5.0f,  10.0f*sin(theta)},
        { 5*sin(theta), 9.0f, 5*cos(theta)}
        };
        glm::vec3 lightColors[] = {
            {30.00f, 0.00f, 0.00f},
            {0.00f, 30.00f, 0.00f},
            {0.00f, 0.00f, 30.00f},
            {30.00f, 30.00f, 30.00f}
        };
        appShader.setUniformVec3Array("lightPositions", 4, lightPositions);
        appShader.setUniformVec3Array("lightColors", 4, lightColors);

        // render
        glClearColor(0.05f, 0.025f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                                                                                                                                                
        appShader.useProgram();
        appCamera->apply(appShader);
        statue.draw(appShader);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}