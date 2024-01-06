#include <raylib.h>
#include <rlgl.h>

#include <cmath>

#include "Tile.h"

Tile::Tile(PortSet portSet, Sprite* sprite, Color color, int initialRotationPos) :
        portSet{portSet},
        sprite{sprite},
        color{color},
        baseRotationPos{initialRotationPos}
{
}

void Tile::addRotation()
{
    if (rotations.size() < 4) {
        rotations.emplace();
    }
}

bool Tile::update(float deltaSeconds)
{
    while (!rotations.empty() && (deltaSeconds > 0.0f)) {
        Rotation& rotation = rotations.front();
        deltaSeconds = rotation.update(deltaSeconds);
        if (rotation.isFinished()) {
            rotations.pop();
            applyRotation();
        }
    }
    return rotations.empty();
}

float Rotation::update(float deltaSeconds)
{
    totalSeconds += deltaSeconds;
    progress = std::clamp(calculateProgress(totalSeconds / durationSeconds), 0.0f, 1.0f);
    return std::max(0.0f, totalSeconds - durationSeconds);
}

float Rotation::calculateProgress(float time) const
{
    // Sigmoid function, result in [0.0, 1.0] for input in [0.0, 1.0]
    return (1.0f / (1.0f + expf(-((time * 10.0f) - 5.0f)))) * 1.01379f - 0.007f;
}

bool Rotation::isFinished() const
{
    return fabsf(progress - 1.0f) < std::numeric_limits<float>::epsilon();
}

void Tile::applyRotation()
{
    portSet.rotate();
    baseRotationPos = (baseRotationPos + 1) % 4;
}

void Tile::draw() const
{
    drawByVariant(SpriteVariant::PLAIN);
}

void Tile::drawOutline() const
{
    drawByVariant(SpriteVariant::OUTLINE);
}

void Tile::drawAnimGradient() const
{
    drawByVariant(SpriteVariant::ANIM_GRADIENT);
}

void Tile::drawByVariant(SpriteVariant variant) const
{
    float halfSize = Tile::size() / 2.0f;
    rlPushMatrix();
    rlTranslatef(halfSize, halfSize, 0.0f);
    float angle = 90.0f * static_cast<float>(baseRotationPos);
    if (!rotations.empty()) {
        angle += 90.0f * rotations.front().getProgress();
    }
    rlRotatef(angle, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-halfSize, -halfSize, 0.0f);
    sprite->draw(color, variant);
    rlPopMatrix();
}

float Tile::size()
{
    return 80.0f;
}

float Rotation::getProgress() const
{
    return progress;
}
