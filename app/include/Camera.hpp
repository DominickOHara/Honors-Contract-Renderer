// =========================================================================
// Camera.hpp
// -------------------------------------------------------------------------
// CC BY-NC 4.0
// Copyright (C) 2026 Dominick Ohara
//
// Code refrences LearnOpenGL https://github.com/JoeyDeVries/LearnOpenGL 
// by Joey De Vries (https://twitter.com/JoeyDeVriez).
// =========================================================================
// NOTICE (For academic submission)
// --------------------------------------------------------------------------
// All code was hand produced, nor was anything copied or pasted.
// Any function or class explicitly mentioning Dominick Ohara as author did not reference
// any source material (except API documentnation or any links given as 
// attribution in function or class).
// =========================================================================
// Usage
// --------------------------------------------------------------------------
// Camera handles the view and projection transform logic.
// It also supports updating the view based on user inputs.
// ==========================================================================


#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.hpp"


class Camera {

public:


    Camera(glm::vec3 position, int viewportWidth, int viewportHeight) 
    : position(position), viewportHeight(viewportHeight), viewportWidth(viewportWidth) 
    {
        lastMousePosX = viewportWidth / 2.0f;
        lastMousePosY = viewportHeight / 2.0f;
        updatePerspectiveTransform();
    }

    void update(float dt);
    void processInput(GLFWwindow* window, const float& dt);
    void processMouseInput(GLFWwindow* window, double mousePosX, double mousePosY);
    void framebufferCallback(GLFWwindow* window, int viewportWidth, int viewportHeight);
    
    inline void updateViewport(const int& width, const int& height) {
        viewportWidth = width;
        viewportHeight = height;
    }

    void apply(const ShaderProgram& shader) const;

private:


    float lastMousePosX;
    float lastMousePosY;
    bool firstMouseUpdate = true;

    float yaw = 0.0f;
    float pitch = 0.0f;

    int viewportWidth;
    int viewportHeight;

    glm::vec3 cameraUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraFrontVector = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    glm::mat4 cameraTransform = glm::mat4(1.0f);
    glm::mat4 projectionTransform = glm::mat4(1.0f);

    inline void updatePerspectiveTransform() {
        projectionTransform = glm::perspective(glm::radians(110.0f), (float)viewportWidth / (float)viewportHeight, 0.1f, 1000.0f);
    }

};







#endif