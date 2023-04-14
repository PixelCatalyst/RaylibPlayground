#include "Mosaic.h"

#include <raylib.h>
#include <rlgl.h>

Mosaic::Mosaic(unsigned width, unsigned height) :
        width(width),
        height(height)
{
    tile1Sprite = new Sprite("assets/tiles/tile1.png");
    tile2aSprite = new Sprite("assets/tiles/tile2a.png");
    tile2bSprite = new Sprite("assets/tiles/tile2b.png");
    tile3Sprite = new Sprite("assets/tiles/tile3.png");
    tile4Sprite = new Sprite("assets/tiles/tile4.png");

    Sprite* sprites[5] = {
            tile1Sprite,
            tile3Sprite,
            tile2aSprite,
            tile4Sprite,
            tile2bSprite
    };

    const Color color = BEIGE;
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            fragments.insert(std::make_pair(
                    Coord{x, y},
                    Fragment(sprites[(y * width + x) % 5], color)
            ));
        }
    }
}

Mosaic::~Mosaic()
{
    delete tile1Sprite;
    delete tile2aSprite;
    delete tile2bSprite;
    delete tile3Sprite;
    delete tile4Sprite;
}

void Mosaic::draw() const
{
    for (auto& [coord, frag]: fragments) {
        const Vector2 fragSize = frag.size();
        rlPushMatrix();
        rlTranslatef(coord.first * fragSize.x, coord.second * fragSize.y, 0);
        frag.draw();
        rlPopMatrix();
    }
}

Vector2 Mosaic::size() const
{
    return Vector2{static_cast<float>(width) * 80.0f, static_cast<float>(height) * 80.0f};
}

Fragment::Fragment(Sprite* sprite, Color color) :
        sprite{sprite},
        color{color}
{
    availablePorts[0] = availablePorts[1] = availablePorts[2] = availablePorts[3] = true;
}

Vector2 Fragment::size() const
{
    return Vector2{80.0f, 80.0f};
}

void Fragment::draw() const
{
    sprite->draw(color);
}

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
