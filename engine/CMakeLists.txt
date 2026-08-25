#----------------------------------------
# All source files for the engine
#----------------------------------------
add_library(engine STATIC
    src/GameObject.cpp
    src/Scene.cpp
    src/UI.cpp
    src/Application.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC raylib)
