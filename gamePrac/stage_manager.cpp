#include "stage_manager.h"
#include "title_stage.h"
#include "game_first_stage.h"

void StageManager::LoadTitleStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}

	TitleStage* stage = new TitleStage();
	currentStage = stage;
}

void StageManager::LoadGameFirstStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	GameFirstStage* stage = new GameFirstStage();
	currentStage = stage;
}


void StageManager::Update()
{
	currentStage->Update();
}

void StageManager::Render()
{
	currentStage->Render();
}