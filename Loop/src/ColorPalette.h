#pragma once

#include <raylib.h>

class ColorPalette
{
private:
    Color background;
    Color foreground;

    static float wrapHueValue(float hue);

public:
    ColorPalette();

    static ColorPalette createProcedurally();

    Color getBackground() const;

    Color getForeground() const;
};
