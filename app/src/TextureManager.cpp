// =========================================================================
// TextureManager.cpp
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


#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance() {
    if (instance == nullptr) {
        instance = new TextureManager;
    }
    return instance;
}


void TextureManager::bindTexture(const GLenum& textureTarget, const GLuint& textureId) {
    // see if texture is a valid texture;
    if (!validTextureId(textureId)) {
        std::cout << "Failed to bind texture ;" << textureId << "'; texture does not exist." << std::endl;
        return;
    }
    bindTextureGL(textureTarget, textureId);
}

void TextureManager::bindTexture(const GLenum& textureTarget, const std::string& textureName) {
    if (!validTextureName(textureName)) {
        std::cout << "Failed to bind texture with name '" << textureName << "'; texture does not exist." << std::endl;
        return;
    }
    GLuint textureId = textureMap[textureName];
    bindTextureGL(textureTarget, textureId);
}


void TextureManager::bindTextureGL(const GLenum& textureTarget, const GLuint& textureId) {
    std::unordered_map<GLenum, GLuint>::iterator itt;
    // dont bind same texture if it is bound to the current target
    if ((itt=boundTextures.find(textureTarget)) != boundTextures.cend() && (itt->second == textureId)) {
        return;
    }
    boundTextures[textureTarget] = textureId;
    
    glActiveTexture(textureTarget);
    glBindTexture(GL_TEXTURE_2D, textureId);
}


// Code refrences LearnOpenGL https://github.com/JoeyDeVries/LearnOpenGL 
// by Joey De Vries for channel implementation and stbi usage
// TextureManager::loadTexture Licensed under CC BY-NC 4.0 
GLuint TextureManager::loadTexture(const std::string& texturePath, const std::string& textureName) {
    
    // if texture already present under a different name, add another name and return
    auto itt = pathMap.find(texturePath);
    if (itt!= pathMap.end()) {
        std::string otherName = itt->second;
        GLuint textureId = textureMap[otherName];
        textureMap[textureName] = textureId;
        return textureId;
    }

    int textureWidth = 0;
    int textureHeight = 0;
    int textureChannels = 0;

    std::uint8_t* textureData = stbi_load(texturePath.c_str(), &textureWidth, &textureHeight, &textureChannels, 0);

    if (textureData == nullptr) {
        std::cout << "Failed to create texture with name '" << textureName << "'; " << stbi_failure_reason() << std::endl;
        return 0;
    }

    if (!(textureChannels == 1 ||textureChannels == 3 || textureChannels == 4)) {
        std::cout << "Image has invalid number of channels. Needs 1, 3, or 4, got " << textureChannels << "." << std::endl;
        return 0;
    }
    // create texture
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    
    glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        GLenum textureFormatGL = GL_RED;
        switch (textureChannels) {
            case 1:
                textureFormatGL = GL_RED;
                break;
            case 3:
                textureFormatGL = GL_RGB;
                break;
            case 4:
                textureFormatGL = GL_RGBA;
                break;
            default:
                textureFormatGL = GL_RGB;
                break;
        }

        glTexImage2D(
            GL_TEXTURE_2D, 0, textureFormatGL, 
            textureWidth, textureHeight, 
            0, GL_RGB, GL_UNSIGNED_BYTE, textureData
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    // delete unneccessary texture data.
    stbi_image_free(textureData);

    pathMap[texturePath]=textureName;
    textureMap[textureName] = textureId;

    return textureId;
}
