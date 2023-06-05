#include <raylib.h>
#include <rlgl.h>

#include "Tile.h"

Tile::Tile(PortSet portSet, Sprite* sprite, Color color, int rotation) :
        portSet{portSet},
        sprite{sprite},
        color{color},
        rotation{rotation}
{
}

float Tile::size()
{
    return 80.0f;
}

bool Tile::update(float deltaSeconds)
{
    rot->update(deltaSeconds);
    if (rot->isFinished()) {
        Rotation* next = rot->getNext();
        delete rot;
        rot = next;
        applyRotation();
        return true;
    }
    return false;
}

void Tile::draw() const
{
    float halfSize = Tile::size() / 2.0f;
    rlPushMatrix();
    rlTranslatef(halfSize, halfSize, 0);
    float angle = 90.0f * rotation;
    if (rot != nullptr) {
        angle += 90.0f * rot->getProgress();
    }
    rlRotatef(angle, 0, 0, 1);
    rlTranslatef(-halfSize, -halfSize, 0);
    sprite->draw(color);
    rlPopMatrix();
}

void Tile::applyRotation()
{
    portSet.rotate();
    rotation = (rotation + 1) % 4;
}

void Tile::addRotation(Rotation* rot)
{
    if (this->rot == nullptr) {
        this->rot = rot;
    } else {
        rot->addNext(rot);
    }
}

void Rotation::update(float deltaSeconds)
{
    const float speed = 5.0f;
    const float increase = deltaSeconds * speed;
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
