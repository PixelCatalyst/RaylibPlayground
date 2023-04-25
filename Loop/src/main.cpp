#include "App.h"

int main()
{
    App app;
    app.init();

    while (app.isRunning()) {
        app.update();
        app.draw();
    }

    app.shutdown();
    return 0;
}
