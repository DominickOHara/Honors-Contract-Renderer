// =========================================================================
// TextureManager.hpp
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
// All code in 'TextureManager.hpp' and 'TextureManager.cpp' was created 
// by Dominick Ohara with no reference or source material unless specified.
// (other than API documentation).
// =========================================================================
// Usage
// --------------------------------------------------------------------------
// The TextureManager loads, manages, and binds textures.
// ==========================================================================


#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include <string>
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>
#include <glad/gl.h>

// singleton class
// Singleton pattern developed referencing https://refactoring.guru/design-patterns/singleton/cpp/example
// for both definitions and implementation
class TextureManager {


public:


    inline bool validTextureId(const GLuint& textureId) const {
        for (const auto& pair : textureMap) {
            if (pair.second == textureId) { return true; }
        }
        return false;
    }

    inline bool validTextureName(const std::string textureName) const {
        return (textureMap.contains(textureName));
    }

    inline bool isTextureIdBound(const GLenum& textureTarget, const GLuint& textureId) const {
        auto itt=boundTextures.find(textureTarget);
        return (itt != boundTextures.end() && (itt->second == textureId));
    }

    inline GLuint getTextureId(const std::string textureName) {
        return (validTextureName(textureName))? textureMap[textureName] : 0;
    }

    void bindTexture(const GLenum& textureTarget, const GLuint& textureId);
    void bindTexture(const GLenum& textureTarget, const std::string& textureName);

    // Code refrences LearnOpenGL https://github.com/JoeyDeVries/LearnOpenGL 
    // by Joey De Vries (https://twitter.com/JoeyDeVriez) for channel implementation and stbi usage
    // TextureManager::loadTexture Licensed under CC BY-NC 4.0 
    GLuint loadTexture(const std::string& texturePath, const std::string& textureName);

    static TextureManager* getInstance();

private:
    std::unordered_map<GLenum, GLuint> boundTextures;
    std::unordered_map<std::string, GLuint> textureMap;
    std::unordered_map<std::string, std::string> pathMap;

    static TextureManager* instance;

    // disable copy and move constructors
    TextureManager(const TextureManager& other) = delete;

    // delete left and right assignment operators
    void operator=(const TextureManager& other) = delete;

    // make constructor private
    TextureManager() {}

    void bindTextureGL(const GLenum& textureTarget, const GLuint& textureId);

};

#endif