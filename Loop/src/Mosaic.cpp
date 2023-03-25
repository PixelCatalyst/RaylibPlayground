#include "Mosaic.h"

#include <raylib.h>
#include <rlgl.h>

Mosaic::Mosaic(unsigned width, unsigned height) :
        width(width),
        height(height)
{
    Color colors[4]{
            SKYBLUE, LIME, PURPLE, RED
    };
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            fragments.insert(std::make_pair(Coord{x, y}, Fragment(colors[(y * width + x) % 3])));
        }
    }
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
    return Vector2{static_cast<float>(width) * 50.0f, static_cast<float>(height) * 50.0f};
}

void Fragment::draw() const
{
    DrawRectangle(0, 0, 50, 50, color);
    Color inverted{
            static_cast<unsigned char>(255 - color.r),
            static_cast<unsigned char>(255 - color.g),
            static_cast<unsigned char>(255 - color.b),
            color.a
    };
    if (availablePorts[static_cast<int>(PortIndex::UP)]) {
        DrawCircle(25, 3, 3, inverted);
    }
    if (availablePorts[static_cast<int>(PortIndex::RIGHT)]) {
        DrawCircle(47, 25, 3, inverted);
    }
    if (availablePorts[static_cast<int>(PortIndex::DOWN)]) {
        DrawCircle(25, 47, 3, inverted);
    }
    if (availablePorts[static_cast<int>(PortIndex::LEFT)]) {
        DrawCircle(3, 25, 3, inverted);
    }
}

Vector2 Fragment::size() const
{
    return Vector2{50.0f, 50.0f};
}

Fragment::Fragment(Color color) :
        color{color}
{
    availablePorts[0] = availablePorts[1] = availablePorts[2] = availablePorts[3] = true;
}
