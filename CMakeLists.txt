cmake_minimum_required(VERSION 3.24)
project(RaylibPlayground)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_VERSION 4.2.0)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG ${RAYLIB_VERSION}
)
FetchContent_MakeAvailable(raylib)

function(enable_raylib TARGET)
    target_include_directories(${TARGET} PRIVATE ${raylib_BINARY_DIR}/raylib/include)
    target_link_libraries(${TARGET} raylib)
endfunction()

add_subdirectory(HelloWorld)
