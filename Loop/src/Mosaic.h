#pragma once

#include "DrawUtils.h"

#include <map>

class Sprite
{
private:
    Texture2D texture;
public:
    explicit Sprite();

    void draw(Color color) const;
};

class Fragment : public DrawItem
{
private:
    Sprite* sprite;
    Color color;

    enum class PortIndex
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    };
    bool availablePorts[4];

public:
    explicit Fragment(Sprite* sprite, Color color);

    Vector2 size() const override;

    void draw() const override;
};

using Coord = std::pair<unsigned, unsigned>;

class Mosaic : public DrawItem
{
private:
    std::map<Coord, Fragment> fragments;
    unsigned width;
    unsigned height;

    Sprite* tile4Sprite;
public:
    Mosaic(unsigned width, unsigned height);

    ~Mosaic() override;

    Vector2 size() const override;

    void draw() const override;
};
