// =========================================================================
// Model.hpp
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

#ifndef MODEL
#define MODEL

#include <iostream>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "TextureManager.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"



class Model {

public:

    Model(const std::string& modelPath);

    void draw(const ShaderProgram& shaderProgram);
    inline void setAlbedoTexture(const std::string textureName) { textureAlbedoName =  textureName; }
    inline void setNormalTexture(const std::string textureName) { textureNormalName =  textureName; }
    inline void setRoughnessTexture(const std::string textureName) { textureRoughnessName =  textureName; }
    inline void setAOTexture(const std::string textureName) { textureAOName = textureName; }

private:
    std::vector<Mesh> meshes;
    std::string textureAlbedoName;
    std::string textureNormalName;
    std::string textureRoughnessName;
    std::string textureAOName;

    void processNode(aiNode* node, const aiScene* scene);
    void bindTextures(const ShaderProgram& shader);
};






#endif