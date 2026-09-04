#include "Game.hpp"
#include <raylib.h>
#include "AssetsPath.hpp"

void Game::LoadResources()
{
    //  Audio device must be initialized before loading any sound/music
    InitAudioDevice();
    // Load game resources here (e.g., textures, sounds, etc.)
    // TODO: Make this more generic, maybe with a ResourceManager class?
    // font = LoadFont(FONT);
    //music = LoadMusicStream(MUSIC);
    logo_music = LoadSound(LOGO_MUSIC);
    tittle_music = LoadMusicStream(TITTLE_MUSIC);
    gameplay_music = LoadMusicStream(GAMEPLAY_MUSIC);
}

void Game::UnLoadResources()
{
    UnloadSound(logo_music);
    UnloadMusicStream(tittle_music);
    UnloadMusicStream(gameplay_music);

    CloseAudioDevice(); // Close audio context
}

void Game::InitStarters()
{
    SetTargetFPS(FPs);
    //  Initialize game scenes and other necessary components here
    gameScenes[LOGO] = new Logo();
    gameScenes[TITTLE] = new Tittle(font, tittle_music, screenWidth, screenHeight);
    gameScenes[GAMEPLAY] = new Gameplay(gameplay_music);
    gameScenes[GAMEOVER] = new GameOver();

    currentScreen = LOGO;
}

//  Init Game
void Game::Init()
{
    // Initialize window and traces log.
    InitWindow(screenWidth, screenHeight, ApplicationName.c_str());
    SetTraceLogLevel(LOG_ALL);    
    // Initialize game resources here
    LoadResources();
    InitStarters();

    PlaySound(logo_music);
    gameScenes[currentScreen]->InitScene();
}
// Update logic (input, music, etc.)
void Game::Update(double deltaTime)
{
    //UpdateMusicStream(music); // Update music stream (always required for streaming music)

    if (!onTransition)
    {
        gameScenes[currentScreen]->UpdateScreen(deltaTime);
        GameScreen afterFinish = gameScenes[currentScreen]->FinishScreen();
        if (afterFinish != UNKNOWN)
        {
            TransitionToScreen(afterFinish);
        }
    }
    else
        UpdateTransition(); // Update transition (fade-in, fade-out)
}
// Draw game elements on the screen
void Game::Draw()
{
    // Draw game elements here
    BeginDrawing();

    ClearBackground(RAYWHITE);
    // Draw current screen
    gameScenes[currentScreen]->DrawScreen();

    // Draw full screen rectangle in front of everything
    if (onTransition)
        DrawTransition();

    // DrawFPS(10, 10);

    EndDrawing();
}
// Unload game resources and close the game
void Game::Unload()
{
    gameScenes[currentScreen]->UnloadScreen();
    UnLoadResources();
}

#pragma region Transition Methods

void Game::TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

void Game::UpdateTransition()
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            gameScenes[currentScreen]->UnloadScreen();
            currentScreen = transToScreen;
            // Load next screen
            gameScenes[currentScreen]->InitScene();

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = GameScreen(UNKNOWN);
        }
    }
}

void Game::DrawTransition()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

#pragma endregion