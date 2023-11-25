#pragma once

class FadeAnimation
{
private:
    float durationSeconds{0.0f};
    float endValue{0.0f};
    float progress{0.0f};
public:
    FadeAnimation() = default;

    explicit FadeAnimation(float durationSeconds, float endValue);

    void update(float deltaSeconds);

    float getProgress() const;

    bool isFinished() const;
};
