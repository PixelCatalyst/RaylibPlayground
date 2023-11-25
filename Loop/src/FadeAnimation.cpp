#include "FadeAnimation.h"

#include <cmath>

FadeAnimation::FadeAnimation(float durationSeconds, float endValue) :
        durationSeconds{durationSeconds},
        endValue{endValue}
{
}

void FadeAnimation::update(float deltaSeconds)
{
    progress += (endValue / durationSeconds) * deltaSeconds;
}

float FadeAnimation::getProgress() const
{
    return std::fmin(progress, endValue);
}

bool FadeAnimation::isFinished() const
{
    return progress >= endValue;
}
