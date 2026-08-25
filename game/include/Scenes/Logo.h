#pragma once
#include "ProgramFlow/Scene.h"

class Logo : public Scene {
	int framesCounter;

	int logoPositionX;
	int logoPositionY;

	int lettersCount;

	int topSideRecWidth;
	int leftSideRecHeight;

	int bottomSideRecWidth;
	int rightSideRecHeight;

	int state;
	float alpha;
public:
	Logo();
	void InitScene() override;
	void UpdateScreen() override;
	void DrawScreen() override;
	void UnloadScreen() override {};
	void OnMouseDown() override {};
	void OnKeyPressed(KeyboardKey key) override {};
};