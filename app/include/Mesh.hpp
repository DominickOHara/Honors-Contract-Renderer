// =========================================================================
// Mesh.hpp
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
// The Mesh handles a OpenGL VAO and associated vertex data.
// The Vertex struct is the data required for a single vertex.
// ==========================================================================

#ifndef MESH
#define MESH

#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <iostream>

#include "ShaderProgram.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 textureCoords;
};


class Mesh {

public:

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

    inline void draw(const ShaderProgram& shaderProgram) const {
        glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    };

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint VAO;
    GLuint VBO; 
    GLuint EBO;
};







#endif 