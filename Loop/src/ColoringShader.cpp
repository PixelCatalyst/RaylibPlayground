#include "ColoringShader.h"

void ColoringShader::init()
{
    shader = LoadShader(nullptr, "assets/shaders/coloring.frag");
    backgroundColorLoc = GetShaderLocation(shader, "backgroundColor");
    foregroundColorLoc = GetShaderLocation(shader, "foregroundColor");
}

void ColoringShader::setColors(Color background, Color foreground)
{
    fillColorVector(backgroundColorVector, background);
    fillColorVector(foregroundColorVector, foreground);
    SetShaderValue(shader, backgroundColorLoc, backgroundColorVector, SHADER_UNIFORM_IVEC3);
    SetShaderValue(shader, foregroundColorLoc, foregroundColorVector, SHADER_UNIFORM_IVEC3);
}

void ColoringShader::fillColorVector(int vector[3], Color fill)
{
    vector[0] = fill.r;
    vector[1] = fill.g;
    vector[2] = fill.b;
}

void ColoringShader::enable()
{
    BeginShaderMode(shader);
}

void ColoringShader::disable()
{
    EndShaderMode();
}
