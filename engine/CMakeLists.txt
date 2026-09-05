#----------------------------------------
# All source files for the engine
#----------------------------------------
add_library(engine STATIC
    src/EngineObjects/GameObject.cpp
    src/EngineObjects/UI.cpp
    src/EngineObjects/Renderer.cpp
    src/ProgramFlow/Scene.cpp
    src/ProgramFlow/Application.cpp
    src/ProgramFlow/clock.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC raylib)
