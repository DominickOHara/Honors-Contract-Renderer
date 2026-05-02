// =========================================================================
// ShaderProgram.cpp
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
// ShaderProgram abstracts away the shader implementation.
// ShaderBuilder is a helper class that fetches, compiles, and links 
// shaders into an OpenGL shader program (not a instance of class 
// 'ShaderProgram').
// ==========================================================================

#include "ShaderProgram.hpp"
#include <fstream>
#include <sstream>
#include <ostream>
#include <iostream>


ShaderProgram::Builder& ShaderProgram::Builder::addShader(const std::string& shaderPath, const GLenum& shaderType) {

    if (this->linked) {
        std::cout << "Cannot add shader; shader program already built." << std::endl;
    }

    GLuint shader;
    std::ifstream shaderFile;
    std::string shaderCodeString;
    const char* shaderCodeRaw;
    int shaderCompileSuccess;
    char shaderInfoLog[512] = {0};
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCodeString = shaderStream.str();
        shaderFile.close();
        //std::cout << "Shader code:\n" << shaderCodeString << std::endl;
    } catch (std::ifstream::failure err) {
        std::cout << "Failed to load file: " << err.what() << std::endl;
    }
    shaderCodeRaw = shaderCodeString.c_str();
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCodeRaw, nullptr);
    glCompileShader(shader);

    // display error messages
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (!shaderCompileSuccess) {
        glGetShaderInfoLog(shader, 512, nullptr, shaderInfoLog);\
        std::cout << "Failed to compile shader " << shaderPath << ": " << shaderInfoLog << std::endl;
    }
    
    shaderVector.emplace_back(shader);
    compileSuccess = compileSuccess && shaderCompileSuccess; // allows you to chain success flags (single 1 fails, all failed)

    return *this;
}


GLuint ShaderProgram::Builder::linkShaders() {
    if (this->linked) {
        std::cout << "Cannot link shaders; shader program already built." << std::endl;
    }
    GLint linkSuccess = true;
    char infoLog[512] = {0};
    shaderProgramId = glCreateProgram();
    for (const auto& shader : this->shaderVector) {
        glAttachShader(shaderProgramId, shader);
    }
    glLinkProgram(shaderProgramId);
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
        std::cout << "Failed to link shader program: " << infoLog << std::endl;
    }
    this->compileSuccess = this->compileSuccess && linkSuccess; // allows for success flag to be chained.
    
    // destroy uneeded shaders
    while (!shaderVector.empty()) {
        GLuint shader = shaderVector.back();
        shaderVector.pop_back();
        glDeleteShader(shader);
    }
            
    linked = true;
    return (this->compileSuccess) ? shaderProgramId : -1;
}