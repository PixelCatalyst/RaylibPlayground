#include "App.h"

int main()
{
    App app;
    app.init();

    while (app.isRunning()) {
        app.update();
        app.draw();
    }

    app.close();
    return 0;
}
