#pragma once

#include <raylib.h>

class RadialFadeShader
{
private:
    Shader shader{};
    int textureLoc{-1};
    int originLoc{-1};
    int radiusLoc{-1};
public:
    void init();

    void setOrigin(Vector2 origin);

    void setRadius(float radius);

    void enable(Texture2D foregroundTexture);

    void disable();
};
