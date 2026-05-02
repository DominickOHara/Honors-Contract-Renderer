// =========================================================================
// Camera.cpp
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

#include "Camera.hpp"

#include <cmath>

void Camera::update(float dt) {
    cameraTransform = glm::lookAt(position, position + cameraFrontVector, cameraUpVector);
}

void Camera::apply(const ShaderProgram& shaderProgram) const {
    shaderProgram.setUniformMat4("viewTransform", cameraTransform);
    shaderProgram.setUniformMat4("projTransform", projectionTransform);
    shaderProgram.setUniformVec3("cameraPosition", position);
}

void Camera::processInput(GLFWwindow* window, const float& dt) {
    const float CAMERA_SPEED = 2.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += CAMERA_SPEED * dt * cameraFrontVector;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= CAMERA_SPEED * dt * cameraFrontVector;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += CAMERA_SPEED * dt * glm::normalize(glm::cross(cameraFrontVector, cameraUpVector));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= CAMERA_SPEED * dt * glm::normalize(glm::cross(cameraFrontVector, cameraUpVector));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        position += CAMERA_SPEED * dt * cameraUpVector;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        position -= CAMERA_SPEED * dt * cameraUpVector;
    }
}


void Camera::processMouseInput(GLFWwindow* window, double mousePosX, double mousePosY) {
    yaw = 3.14159265358f*(-1.0 + 2.0 * (mousePosX/viewportWidth));
    pitch = 3.14159265358f/2.0f*(1.0 -2.0 * (mousePosY/viewportHeight));
    cameraFrontVector = glm::normalize(glm::vec3(
        std::cosf(yaw) * std::cosf(pitch),
        std::sinf(pitch),
        std::sinf(yaw) * std::cosf(pitch)
    ));
}

void Camera::framebufferCallback(GLFWwindow* window, int viewportWidth, int viewportHeight) {
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
    updatePerspectiveTransform();
}