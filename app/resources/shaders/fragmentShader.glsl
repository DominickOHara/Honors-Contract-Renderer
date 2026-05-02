// =========================================================================
// fragmentShader.glsl
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

out vec4 FragColor;

in VertexOut {
    vec3 normal;
    mat3 TBNTransform;
    vec3 worldPos;
    vec2 texCoords;
} fragIn;

uniform sampler2D textureAlbedo;
uniform sampler2D textureNormal;
uniform sampler2D textureRoughness;
uniform sampler2D textureAO;

uniform vec3 cameraPosition;

uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];


float NDFTrowbridgeReitzGGX(float cosThetaH, float a) {
    return (a * a) / 
    (pow(3.1415 * cosThetaH*cosThetaH*(a*a-1.0)+1.0, 2.0)+0.001);
}

float GeomShadSmithSchlick(float cosThetaL, float cosThetaV, float k) {
    return (cosThetaL * cosThetaV) /
    (
        (cosThetaL*(1.0-k) + k) *
        (cosThetaV*(1.0-k) + k)
    );
}

vec3 FresnelFactorSchlick(vec3 f0, float cosThetaVH) {
    return f0 + (1.0 - f0) * pow((1.0 - cosThetaVH), 5.0);
}



void main() {
    vec4 albedoSample = texture(textureAlbedo, fragIn.texCoords);
    vec4 normalSample = texture(textureNormal, fragIn.texCoords);
    vec4 roughnessSample = texture(textureRoughness, fragIn.texCoords);
    vec4 aoSample = texture(textureAO, fragIn.texCoords);

    vec3 ao = aoSample.rgb;
    vec3 normal = normalize(fragIn.TBNTransform * (normalSample.rgb * 2.0 - 1.0));
    float roughness = length(roughnessSample);
    vec3 albedo = albedoSample.rgb;

    vec3 irradience = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 4; i++) {
        vec3 lightPos = lightPositions[i];
        vec3 lightColor = lightColors[i]*10;
        vec3 lightDir = normalize(lightPos - fragIn.worldPos);
        vec3 viewDir = normalize(cameraPosition - fragIn.worldPos);
        vec3 halfVec = normalize(lightDir + viewDir);
        vec3 radiance = lightColor / pow(length(lightPos - fragIn.worldPos), 2);
        
        float cosThetaL = max(dot(normal, lightDir), 0);
        float cosThetaV = max(dot(normal, viewDir), 0);
        float cosThetaH = max(dot(normal, halfVec), 0);
        float cosThetaVH = max(dot(halfVec, viewDir), 0);
        float a = roughness;
        float k = a/2.0;

        float ior = 1.5;
        vec3 f0 = vec3(pow((1-ior)/(1+ior),2.0));
        vec3 F = FresnelFactorSchlick(f0, cosThetaVH);

        float G = GeomShadSmithSchlick(cosThetaL, cosThetaV, k);
        float D = NDFTrowbridgeReitzGGX(cosThetaH, a);

        vec3 fs = D*G*F / (4.0*cosThetaL*cosThetaV + 0.001);
        vec3 fd = (1.0-F)*0.5*albedo/3.1415;

        irradience += (fs + fd)* radiance * cosThetaL;
    }

    FragColor = vec4(irradience * ao + vec3(0.05), 1.0);
}