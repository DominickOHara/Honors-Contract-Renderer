// =========================================================================
// vertexShader.glsl
// -------------------------------------------------------------------------
// CC BY-NC 4.0
// Copyright (C) 2026 Dominick Ohara
//
// Code refrences LearnOpenGL https://github.com/JoeyDeVries/LearnOpenGL 
// by Joey De Vries (https://twitter.com/JoeyDeVriez).
// math implementation from https://dev.opencascade.org/doc/overview/html/specification__pbr_math.html
// =========================================================================
// NOTICE (For academic submission)
// --------------------------------------------------------------------------
// All code was hand produced, nor was anything copied or pasted.
// Any function or class explicitly mentioning Dominick Ohara as author did not reference
// any source material (except API documentnation or any links given as 
// attribution in function or class).
// ==========================================================================

#version 330 core
layout (location = 0) in vec3 lytVertexWorldPos;
layout (location = 1) in vec3 lytNormal;
layout (location = 2) in vec3 lytTangent;
layout (location = 3) in vec3 lytBitangent;
layout (location = 4) in vec2 lytTexCoords;



out VertexOut {
    vec3 normal;
    mat3 TBNTransform;
    vec3 worldPos;
    vec2 texCoords;
} vertexOut;


uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projTransform;


void main() {
    // transforming a column vector
    gl_Position = projTransform * viewTransform * modelTransform * vec4(lytVertexWorldPos, 1.0f);
    vertexOut.normal = lytNormal;
    vertexOut.TBNTransform = mat3(lytTangent, lytBitangent, lytNormal);
    vertexOut.texCoords = lytTexCoords; 
    vertexOut.worldPos = lytVertexWorldPos;
}