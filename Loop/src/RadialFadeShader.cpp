#include "RadialFadeShader.h"

void RadialFadeShader::init()
{
    shader = LoadShader(nullptr, "assets/shaders/radial_fade.frag");
    textureLoc = GetShaderLocation(shader, "texture1");
    originLoc = GetShaderLocation(shader, "origin");
    radiusLoc = GetShaderLocation(shader, "radius");
}

void RadialFadeShader::setOrigin(Vector2 origin)
{
    SetShaderValue(shader, originLoc, &origin, SHADER_UNIFORM_VEC2);
}

void RadialFadeShader::setRadius(float radius)
{
    SetShaderValue(shader, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
}

void RadialFadeShader::enable(Texture2D foregroundTexture)
{
    BeginShaderMode(shader);
    SetShaderValueTexture(shader, textureLoc, foregroundTexture);
}

void RadialFadeShader::disable()
{
    EndShaderMode();
}
