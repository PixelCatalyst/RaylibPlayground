#pragma once

#include <raylib.h>

class ColorPalette
{
private:
    Color background;
    Color foreground;
    Color neonBackground;
    Color neonForeground;

    static float wrapHueValue(float hue);

public:
    ColorPalette();

    static ColorPalette createProcedurally();

    Color getBackground() const;

    Color getForeground() const;

    Color getNeonBackground() const;

    Color getNeonForeground() const;
};
