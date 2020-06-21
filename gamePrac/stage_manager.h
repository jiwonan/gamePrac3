#pragma once

class Stage;

class StageManager
{
public:
	Stage* currentStage;

	void LoadTitleStage();
	void LoadGameFirstStage();

	void Update();
	void Render();
};