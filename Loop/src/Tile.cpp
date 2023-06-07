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
    if (rotation != nullptr) {
        rotation->update(deltaSeconds);
        if (rotation->isFinished()) {
            Rotation* next = rotation->getNext();
            delete rotation;
            rotation = next;
            applyRotation();
        }
    }
    return (rotation == nullptr);
}

void Tile::draw() const
{
    float halfSize = Tile::size() / 2.0f;
    rlPushMatrix();
    rlTranslatef(halfSize, halfSize, 0);
    float angle = 90.0f * static_cast<float>(baseRotationPos);
    if (rotation != nullptr) {
        angle += 90.0f * rotation->getProgress();
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
    auto* nextRotation = new Rotation;
    if (rotation == nullptr) {
        rotation = nextRotation;
    } else {
        rotation->addNext(nextRotation);
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

void Rotation::addNext(Rotation* rot)
{
    if (next == nullptr) {
        next = rot;
    } else {
        next->addNext(rot);
    }
}

Rotation* Rotation::getNext()
{
    return next;
}

float Rotation::getProgress() const
{
    return std::min(1.0f, progress);
}
