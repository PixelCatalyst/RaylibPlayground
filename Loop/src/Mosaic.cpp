#include "Mosaic.h"

#include <raylib.h>
#include <rlgl.h>

Mosaic::Mosaic(const TileFactory& tileFactory, unsigned width, unsigned height) :
        width(width),
        height(height)
{
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            tiles.insert(std::make_pair(
                    Coord{x, y},
                    tileFactory.create(PortSet::of({Port::up(), Port::right(), Port::down()}))
            ));
        }
    }
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
