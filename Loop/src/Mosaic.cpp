#include "Mosaic.h"

#include <raylib.h>
#include <rlgl.h>

Mosaic::Mosaic(const TileFactory& tileFactory, unsigned width, unsigned height) :
        width(width),
        height(height)
{
    const unsigned rightEnd = width - 1;
    const unsigned downEnd = height - 1;
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            if (x == 0 && y == 0) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::down()}))
                ));
            } else if (x == rightEnd && y == 0) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::down()}))
                ));
            } else if (x == 0 && y == downEnd) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::up()}))
                ));
            } else if (x == rightEnd && y == downEnd) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::up()}))
                ));
            } else if (x == 3 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::up()}))
                ));
            } else if (x == 0) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::up(), Port::down()}))
                ));
            } else if (x == rightEnd) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::up(), Port::down()}))
                ));
            } else if (y == 0) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right(), Port::down()}))
                ));
            } else if (y == downEnd) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right(), Port::up()}))
                ));
            } else {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right(), Port::down(), Port::up()}))
                ));
            }
        }
    }
}

void Mosaic::update(float deltaSeconds)
{
    for (auto it = tilesToUpdate.begin(); it != tilesToUpdate.end();) {
        auto tile = tiles.find(*it);
        if (tile->second.update(deltaSeconds)) {
            it = tilesToUpdate.erase(it);
        } else {
            ++it;
        }
    }
}

void Mosaic::onLeftClick(const Vector2& mousePos, const Vector2& viewportSize)
{
    const Vector2 mosaicSize{
            static_cast<float>(width) * Tile::size(),
            static_cast<float>(height) * Tile::size()
    };
    const Vector2 alignedMousePos{
            mousePos.x - ((viewportSize.x - mosaicSize.x) / 2.0f),
            mousePos.y - ((viewportSize.y - mosaicSize.y) / 2.0f)
    };
    rotateTile(alignedMousePos.x / Tile::size(), alignedMousePos.y / Tile::size());
}

void Mosaic::rotateTile(unsigned x, unsigned y)
{
    auto it = tiles.find({x, y});
    if (it != tiles.end()) {
        auto& [coord, tile] = *it;
        auto* rot = new Rotation;
        tilesToUpdate.insert(coord);
        tile.addRotation(rot);
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
