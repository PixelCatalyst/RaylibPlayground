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
)

enable_raylib(Loop)
