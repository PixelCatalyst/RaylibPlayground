#pragma once

#include <raylib.h>

#include "DrawItem.h"
#include "Port.h"
#include "Sprite.h"

class Rotation
{
private:
    float progress{0.0f};
    Rotation* next{nullptr};
public:
    void update(float deltaSeconds);

    bool isFinished() const;

    void addNext(Rotation* next);

    Rotation* getNext();

    float getProgress() const;
};

class Tile : public DrawItem
{
private:
    PortSet portSet;
    Sprite* sprite;
    Color color;
    int baseRotationPos;

    Rotation* rotation{nullptr};

    void applyRotation();

public:
    explicit Tile(PortSet portSet, Sprite* sprite, Color color, int initialRotationPos);

    static float size();

    bool update(float deltaSeconds);

    void draw() const override;

    void addRotation();
};
