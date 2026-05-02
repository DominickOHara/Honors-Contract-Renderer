// =========================================================================
// Model.cpp
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
// Model manages a collection of meshes and draws them to the screen.
// ==========================================================================


#include "Model.hpp"

inline glm::vec3 assimpToGlm(const aiVector3D& vec) {
    return glm::vec3{vec.x, vec.y, vec.z};
}


Mesh meshFromAssimp(aiMesh* mesh, const aiScene* scene);

Model::Model(const std::string& modelPath) {
    textureAlbedoName = "";
    textureNormalName = "";
    textureRoughnessName = "";
    textureAOName = "";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "assimp error: " << importer.GetErrorString() << std::endl;
    }

    processNode(scene->mRootNode, scene);
}

void Model::draw(const ShaderProgram& shaderProgram){
    for (const auto& mesh : meshes) {
        mesh.draw(shaderProgram);
    }
    bindTextures(shaderProgram);
}


void Model::processNode(aiNode* node, const aiScene* scene) {
    for (std::size_t i = 0; i < node->mNumMeshes; i++) {
        this->meshes.emplace_back(
            meshFromAssimp(
                scene->mMeshes[node->mMeshes[i]], 
                scene
            )
        );
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }

}


void Model::bindTextures(const ShaderProgram& shader) {
    TextureManager* textureManager = TextureManager::getInstance();
    textureManager->bindTexture(GL_TEXTURE0, textureAlbedoName);
    textureManager->bindTexture(GL_TEXTURE1, textureNormalName);
    textureManager->bindTexture(GL_TEXTURE2, textureRoughnessName);
    textureManager->bindTexture(GL_TEXTURE3, textureAOName);
           
}


Mesh meshFromAssimp(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    for (std::size_t i = 0; i < mesh->mNumVertices; i++) {
        const aiVector3D vertexPos = mesh->mVertices[i]; 
        aiVector3D vertexTextureCoords = {0.0f, 0.0f, 0.0f};
        if (mesh->mTextureCoords[0]) {
            vertexTextureCoords = mesh->mTextureCoords[0][i];
        }
        Vertex newVertex;
        newVertex.position = assimpToGlm(mesh->mVertices[i]);
        newVertex.normal = assimpToGlm(mesh->mNormals[i]);
        newVertex.tangent = assimpToGlm(mesh->mTangents[i]);
        newVertex.bitangent = assimpToGlm(mesh->mBitangents[i]);
        newVertex.textureCoords = glm::vec2(vertexTextureCoords.x, vertexTextureCoords.y);
        vertices.push_back(newVertex);
    }

    for (std::size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (std::size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}