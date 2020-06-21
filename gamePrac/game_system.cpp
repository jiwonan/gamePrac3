#include "game_system.h"
#include "player_bullet.h"
#include "global.h"

void GameSystem::GenerateEnemyA()
{

}

void GameSystem::GeneratePlayerBulletSpread(float x, float y)
{
	soundManager.sndPlayerBullet->Reset();
	soundManager.sndPlayerBullet->Play(0, 0, 1);
	float speed = 8;

	for (int i = 0; i < 5; ++i)
	{
		float deltaAngle = (i * 8 + 70) * 3.141592f / 180.0f;
		float velX = cos(deltaAngle) * speed;
		float velY = -sin(deltaAngle) * speed;
		PlayerBullet* newBullet = new PlayerBullet(x, y, velX, velY);
		playerBullets.push_back(newBullet);
	}
}

void GameSystem::Update()
{
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();)
	{
		(*iter)->Update();
		if ((*iter)->IsDead())
		{
			iter = playerBullets.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameSystem::Render()
{
	for (int i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i]->Render();
	}
}