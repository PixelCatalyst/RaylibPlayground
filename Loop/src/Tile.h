#pragma once

#include <raylib.h>

#include <queue>

#include "DrawItem.h"
#include "Port.h"
#include "Sprite.h"

class Rotation
{
private:
    const float durationSeconds{0.15f};

    float progress{0.0f};
    float totalSeconds{0.0f};

    float calculateProgress(float time) const;

public:
    float update(float deltaSeconds);

    bool isFinished() const;

    float getProgress() const;
};

class Tile : public DrawItem
{
private:
    PortSet portSet;
    Sprite* sprite;
    Color color;
    int baseRotationPos;

    std::queue<Rotation> rotations;

    void applyRotation();

    void drawByVariant(SpriteVariant variant) const;

public:
    explicit Tile(PortSet portSet, Sprite* sprite, Color color, int initialRotationPos);

    void addRotation();

    bool update(float deltaSeconds);

    void draw() const override;

    void drawOutline() const;

    static float size();
};
