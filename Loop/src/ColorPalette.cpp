#include "ColorPalette.h"

ColorPalette::ColorPalette() :
        background{BLACK},
        foreground{WHITE},
        neonBackground{WHITE},
        neonForeground{BLACK}
{
}

ColorPalette ColorPalette::createProcedurally()
{
    ColorPalette palette{};

    float hue = static_cast<float>(GetRandomValue(0, 3600)) / 10.0f;
    float saturation = static_cast<float>(GetRandomValue(660, 920)) / 1000.0f;
    float brightness = static_cast<float>(GetRandomValue(520, 610)) / 1000.0f;
    palette.foreground = ColorFromHSV(hue, saturation, brightness);
    palette.neonBackground = ColorFromHSV(hue, saturation, 0.14f + brightness * 0.05f);

    const float hueJerk = 24.0f;
    hue = static_cast<float>(GetRandomValue(int(hue - hueJerk), int(hue + hueJerk)));
    hue = wrapHueValue(hue);
    saturation = static_cast<float>(GetRandomValue(170, 220)) / 1000.0f;
    brightness = static_cast<float>(GetRandomValue(870, 980)) / 1000.0f;
    palette.background = ColorFromHSV(hue, saturation, brightness);
    palette.neonForeground = ColorFromHSV(hue, saturation * 4.2f * (1.0f - saturation * 0.33f), brightness);

    return palette;
}

float ColorPalette::wrapHueValue(float hue)
{
    if (hue < 0.0f) {
        hue += 360.0f;
    } else if (hue > 360.0f) {
        hue -= 360.0f;
    }
    return hue;
}

Color ColorPalette::getBackground() const
{
    return background;
}

Color ColorPalette::getForeground() const
{
    return foreground;
}

Color ColorPalette::getNeonBackground() const
{
    return neonBackground;
}

Color ColorPalette::getNeonForeground() const
{
    return neonForeground;
}
