#pragma once

#include "DrawUtils.h"

#include <map>

class Fragment : public DrawItem
{
private:
    //TODO Fragment appearance
    enum class PortIndex
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    };
    bool availablePorts[4];

    Color color;
public:
    explicit Fragment(Color color);

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
public:
    Mosaic(unsigned width, unsigned height);

    Vector2 size() const override;

    void draw() const override;
};
