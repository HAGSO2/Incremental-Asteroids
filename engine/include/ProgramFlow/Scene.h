#pragma once
#include <raylib.h>
#include "EngineObjects/UI.h"

enum GameScreen {
	UNKNOWN = -1,
	LOGO = 0,
	TITTLE = 1,
	GAMEPLAY = 2,
	GAMEOVER = 3
};

#define GameplayButtonText "Play!"


class Scene {
protected:
	GameScreen finishScreen;
	Vector2 mousePosition;
	UI canvas;
	Color backgroundColor;
	Music music;
	bool hasMusic = false;
	
public:
	Scene();
	Scene(Music m);
	virtual void InitScene();
	virtual void UpdateScreen(double deltaTime);
	virtual void DrawScreen() = 0;
	virtual void UnloadScreen() = 0;
	GameScreen FinishScreen() { return finishScreen; };

	virtual void OnMouseDown() = 0;
	virtual void OnKeyPressed(KeyboardKey) = 0;

	void ChangeScene(GameScreen sc){finishScreen = sc;}
	Music GetMusic() { return music; };

private:
	void ManageInterruptions();
	
};