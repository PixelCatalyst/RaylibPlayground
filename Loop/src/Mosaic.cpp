#include "Mosaic.h"

#include <raylib.h>
#include <rlgl.h>

Mosaic::Mosaic(const TileFactory& tileFactory, unsigned width, unsigned height) :
        width(width),
        height(height)
{
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            if (x == 2 && y == 2) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::down()}))
                ));
            } else if (x == 3 && y == 2) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right()}))
                ));
            } else if (x == 4 && y == 2) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right()}))
                ));
            } else if (x == 5 && y == 2) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::down()}))
                ));
            } else if (x == 5 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::down(), Port::up()}))
                ));
            } else if (x == 4 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right()}))
                ));
            } else if (x == 5 && y == 4) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::up(), Port::down()}))
                ));
            } else if (x == 5 && y == 5) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::up(), Port::left()}))
                ));
            } else if (x == 4 && y == 5) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::left()}))
                ));
            } else if (x == 3 && y == 5) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::left()}))
                ));
            } else if (x == 2 && y == 5) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::up()}))
                ));
            } else if (x == 2 && y == 4) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::up(), Port::down()}))
                ));
            } else if (x == 3 && y == 4) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right(), Port::left()}))
                ));
            } else if (x == 4 && y == 4) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left()}))
                ));
            } else if (x == 2 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left(), Port::right(), Port::up(), Port::down()}))
                ));
            } else if (x == 1 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::right()}))
                ));
            } else if (x == 3 && y == 3) {
                tiles.insert(std::make_pair(
                        Coord{x, y},
                        tileFactory.create(PortSet::of({Port::left()}))
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
        tilesToUpdate.insert(coord);
        tile.addRotation();
    }
}

void Mosaic::drawCentered(const Vector2& viewportSize) const
{
    rlPushMatrix();
    translateCentering(viewportSize);
    drawTiles([](const Tile& tile) { tile.draw(); });
    rlPopMatrix();
}

void Mosaic::drawCenteredAsOutline(const Vector2& viewportSize) const
{
    rlPushMatrix();
    translateCentering(viewportSize);
    drawTiles([](const Tile& tile) { tile.drawOutline(); });
    rlPopMatrix();
}

void Mosaic::drawCenteredAsAnimGradient(const Vector2& viewportSize) const
{
    rlPushMatrix();
    translateCentering(viewportSize);
    drawTiles([](const Tile& tile) { tile.drawAnimGradient(); });
    rlPopMatrix();
}

void Mosaic::translateCentering(const Vector2& viewportSize) const
{
    const Vector2 mosaicSize{
            static_cast<float>(width) * Tile::size(),
            static_cast<float>(height) * Tile::size()
    };
    rlTranslatef((viewportSize.x - mosaicSize.x) / 2.0f, (viewportSize.y - mosaicSize.y) / 2.0f, 0.0f);
}

void Mosaic::drawTiles(const std::function<void(const Tile&)>& drawFunction) const
{
    const float tileSize = Tile::size();
    for (auto& [coord, tile]: tiles) {
        rlPushMatrix();
        rlTranslatef(coord.first * tileSize, coord.second * tileSize, 0);
        drawFunction(tile);
        rlPopMatrix();
    }
}
