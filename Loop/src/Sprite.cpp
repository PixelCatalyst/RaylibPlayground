#include <raylib.h>
#include <rlgl.h>

#include "Sprite.h"

Sprite::Sprite(const std::string& fileName)
{
    texture = LoadTexture(fileName.c_str());
}

void Sprite::draw(Color color) const
{
    rlPushMatrix();
    DrawTexture(texture, 0, 0, color);
    rlPopMatrix();
}
