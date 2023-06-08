#include <raylib.h>
#include <rlgl.h>

#include "Tile.h"

Tile::Tile(PortSet portSet, Sprite* sprite, Color color, int initialRotationPos) :
        portSet{portSet},
        sprite{sprite},
        color{color},
        baseRotationPos{initialRotationPos}
{
}

float Tile::size()
{
    return 80.0f;
}

bool Tile::update(float deltaSeconds)
{
    if (!rotations.empty()) {
        Rotation& rotation = rotations.front();
        rotation.update(deltaSeconds);
        if (rotation.isFinished()) {
            rotations.pop();
            applyRotation();
        }
    }
    return rotations.empty();
}

void Tile::draw() const
{
    float halfSize = Tile::size() / 2.0f;
    rlPushMatrix();
    rlTranslatef(halfSize, halfSize, 0);
    float angle = 90.0f * static_cast<float>(baseRotationPos);
    if (!rotations.empty()) {
        angle += 90.0f * rotations.front().getProgress();
    }
    rlRotatef(angle, 0, 0, 1);
    rlTranslatef(-halfSize, -halfSize, 0);
    sprite->draw(color);
    rlPopMatrix();
}

void Tile::applyRotation()
{
    portSet.rotate();
    baseRotationPos = (baseRotationPos + 1) % 4;
}

void Tile::addRotation()
{
    if (rotations.size() < 5) {
        rotations.emplace();
    }
}

float Rotation::calculateVelocity() const
{
    return (-20.0f * ((progress * progress) - progress) + 5.0f);
}

void Rotation::update(float deltaSeconds)
{
    const float increase = deltaSeconds * calculateVelocity();
    progress = std::min(1.0f, progress + increase);
}

bool Rotation::isFinished() const
{
    return progress >= 1.0f;
}

float Rotation::getProgress() const
{
    return std::min(1.0f, progress);
}
