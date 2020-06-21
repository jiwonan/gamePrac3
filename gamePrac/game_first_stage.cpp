#include "game_first_stage.h"
#include "global.h"
#include "game_system.h"

GameFirstStage::GameFirstStage()
{
	gameSystem.player = &player;

	soundManager.sndStageOneBGM->Reset();
	soundManager.sndStageOneBGM->Play(0, DSBPLAY_LOOPING, 1);
}

void GameFirstStage::Update()
{

	background.Update();
	player.Update();
	gameSystem.Update();
}

void GameFirstStage::Render()
{
	background.Render();
	player.Render();
	gameSystem.Render();
}