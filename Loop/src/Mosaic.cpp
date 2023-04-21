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
            tiles.insert(std::make_pair(
                    Coord{x, y},
                    Tile(sprites[(y * width + x) % 5], color)
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

void Mosaic::drawCentered(const Vector2& viewportSize) const
{
    const Vector2 mosaicSize{
            static_cast<float>(width) * Tile::size(),
            static_cast<float>(height) * Tile::size()
    };
    rlPushMatrix();
    rlTranslatef((viewportSize.x - mosaicSize.x) / 2.0f, (viewportSize.y - mosaicSize.y) / 2.0f, 0);
    drawTiles();
    rlPopMatrix();
}

void Mosaic::drawTiles() const
{
    const float tileSize = Tile::size();
    for (auto& [coord, tile]: tiles) {
        rlPushMatrix();
        rlTranslatef(coord.first * tileSize, coord.second * tileSize, 0);
        tile.draw();
        rlPopMatrix();
    }
}
