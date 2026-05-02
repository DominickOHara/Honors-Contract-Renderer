// =========================================================================
// ShaderProgram.hpp
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


#ifndef SHADER
#define SHADER

#include <string>
#include <vector>
#include<iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {

public:

    /*
        Builder class is used as after the shader compilation, various fields
        such as 'compileSuccess' or 'linked' or the 'shaderVector' are no longer
        used and take up space
    */
    class Builder {
    public:
        Builder& addShader(const std::string& shaderPath, const GLenum& shaderType);
        GLuint linkShaders();
    private:
        bool compileSuccess = true;
        bool linked = false;
        GLuint shaderProgramId = 0;
        std::vector<GLuint> shaderVector;
    };

    const GLuint shaderProgramId;


    ShaderProgram(const GLuint& shaderProgramId): shaderProgramId(shaderProgramId) {};

    ShaderProgram& addShader(const std::string& shaderPath, const GLenum& shaderType);
    bool linkShaders();

    inline void useProgram() const { glUseProgram(shaderProgramId); }

    // uniform manipulation for shaders
    inline void setUniformInt(const std::string& uniformName, const GLint& data) const {
        glUniform1i(glGetUniformLocation(shaderProgramId, uniformName.c_str()), data);
    }

    inline void setUniformUInt(const std::string& uniformName, const GLuint& data) const {
        glUniform1i(glGetUniformLocation(shaderProgramId, uniformName.c_str()), data);
    }

    inline void setUniformFloat(const std::string& uniformName, const GLfloat& data) const {
        glUniform1f(glGetUniformLocation(shaderProgramId, uniformName.c_str()), data);
    }

    inline void setUniformBool(const std::string& uniformName, const GLboolean& data) const {
        glUniform1i(glGetUniformLocation(shaderProgramId, uniformName.c_str()), (GLint)data);
    }

    inline void setUniformMat4(const std::string& uniformName, const glm::mat4& data) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(data));
    }

    inline void setUniformVec3(const std::string& uniformName, const glm::vec3& data) const {
        glUniform3f(glGetUniformLocation(shaderProgramId, uniformName.c_str()), data.x, data.y, data.z);
    }

    inline void setUniformVec3Array(const std::string& uniformName, const GLsizei arraySize, const glm::vec3* data) const {
        glUniform3fv(glGetUniformLocation(shaderProgramId, uniformName.c_str()), arraySize * 3, (const GLfloat*)data);
    }
    
private:

};


#endif