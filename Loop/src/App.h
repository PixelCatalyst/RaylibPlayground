#pragma once

#include <raylib.h>
#include <rlgl.h>

#include "Mosaic.h"

struct GameState
{
    float angle{0.0f};
};

class App
{
private:
    GameState gameState;
    Mosaic mosaic;
public:
    explicit App();

    void init();

    bool isRunning();

    void update();

    void draw();

    void close();
};
