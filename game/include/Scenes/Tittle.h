#pragma once
#include "ProgramFlow/Scene.h"

class Tittle : public Scene {
	int framesCounter;
	Font font;
	int click;
	int screenWidth;
	int screenHeight;
	
public:
	Tittle(Font f, int w, int h);
	void InitScene() override {/*Scene::InitScene();*/ finishScreen = UNKNOWN;};
	void UpdateScreen(double deltaTime) override;
	void DrawScreen() override;
	void UnloadScreen() override {finishScreen = UNKNOWN;};
	void OnMouseDown() override;
	void OnKeyPressed(KeyboardKey) override {};
	private:
};