// =========================================================================
// Mesh.cpp
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

#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
    :vertices(vertices), indices(indices)
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            {
                // vertex position
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
                glEnableVertexAttribArray(0);
                // vertex normal
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
                glEnableVertexAttribArray(1);
                // vertex tangent
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
                glEnableVertexAttribArray(2);
                // vertex bitangent
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
                glEnableVertexAttribArray(3);
                // vertex texture coords
                glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
                glEnableVertexAttribArray(4);
            }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// void Mesh::draw() const {
//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
// }