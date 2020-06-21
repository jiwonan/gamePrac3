#pragma once

#include "player.h"
#include <vector>

using namespace std;

class Bullet;

class GameSystem
{
public:
	Player* player;
	vector<Bullet*> playerBullets;

	void GenerateEnemyA();
	void GeneratePlayerBulletSpread(float x, float y);
	void Update();
	void Render();
};