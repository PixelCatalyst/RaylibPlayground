#pragma once

#include <raylib.h>

class DrawItem
{
public:
    virtual void draw() const = 0;

    virtual Vector2 size() const;

    virtual ~DrawItem()
    {
    };
};

class DrawUtils
{
public:
    static void drawCentered(const DrawItem& drawItem);
};
