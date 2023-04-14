#pragma once

#include <raylib.h>

class DrawItem
{
public:
    virtual Vector2 size() const;

    virtual void draw() const = 0;

    virtual ~DrawItem()
    {
    };
};

class DrawUtils
{
public:
    static void drawCentered(const DrawItem& drawItem);
};
