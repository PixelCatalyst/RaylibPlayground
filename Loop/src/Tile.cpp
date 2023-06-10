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

float Rotation::calculateProgress(float time) const
{
    // Sigmoid function, result in [0.0, 1.0] for input in [0.0, 1.0]
    return (1.0f / (1.0f + expf(-((time * 10.0f) - 5.0f)))) * 1.01379f - 0.007f;
}

float Rotation::update(float deltaSeconds)
{
    totalSeconds += deltaSeconds;
    progress = std::clamp(calculateProgress(totalSeconds / durationSeconds), 0.0f, 1.0f);
    return std::max(0.0f, totalSeconds - durationSeconds);
}

bool Rotation::isFinished() const
{
    return fabsf(progress - 1.0f) < std::numeric_limits<float>::epsilon();
}

float Rotation::getProgress() const
{
    return progress;
}
