add_executable(
        Loop
        src/main.cpp
        src/App.cpp
        src/Mosaic.cpp
        src/Tile.cpp
        src/Sprite.cpp
        src/SpriteLoader.cpp
        src/TileFactory.cpp
        src/TileDefinition.cpp
        src/Port.cpp
        src/ColoringShader.cpp
        src/ColorPalette.cpp
        src/RadialFadeShader.cpp
        src/FadeAnimation.cpp
)

enable_raylib(Loop)
