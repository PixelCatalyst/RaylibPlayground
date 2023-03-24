#pragma once

#include <raylib.h>
#include <rlgl.h>

struct GameState
{
    float angle{0.0f};
};

struct Triangle
{
    const Vector2 a;
    const Vector2 b;
    const Vector2 c;
    const Color color;

    Triangle(const Vector2& a, const Vector2& b, const Vector2& c, const Color& color) :
            a{a}, b{b}, c{c}, color{color}
    {
    }
};

class App
{
private:
    GameState gameState;
    Triangle triangle;
public:
    explicit App();

    void init();

    bool isRunning();

    void update();

    void draw();

    void close();
};
