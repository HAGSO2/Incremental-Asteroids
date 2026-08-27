add_executable(game
    src/main.cpp
    src/Game.cpp
    src/Scenes/Logo.cpp
    src/Scenes/Tittle.cpp
    src/Scenes/TemplateScene.cpp
    src/Scenes/Gameplay.cpp
    src/Scenes/GameOver.cpp
    src/Player.cpp
)

# Copy assets to the output directory after building the game

add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/assets
  $<TARGET_FILE_DIR:game>/assets
)

target_include_directories(game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game PRIVATE engine)

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
