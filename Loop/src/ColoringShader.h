#pragma once

#include <raylib.h>

class ColoringShader
{
private:
    Shader shader{};
    int backgroundColorLoc = -1;
    int foregroundColorLoc = -1;

    int backgroundColorVector[3] = {0};
    int foregroundColorVector[3] = {0};

    void fillColorVector(int vector[3], Color fill);

public:
    void init();

    void setColors(Color background, Color foreground);

    void enable();

    void disable();
};
