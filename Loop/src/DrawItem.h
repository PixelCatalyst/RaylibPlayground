#pragma once

#include <raylib.h>

class DrawItem
{
public:
    virtual void draw() const = 0;

    virtual ~DrawItem()
    {
    };
};
