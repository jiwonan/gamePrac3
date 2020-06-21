#include "player.h"
#include "global.h"

Player::Player()
{
	playerX = WINDOW_WIDTH / 2;
	playerY = WINDOW_HEIGHT * 0.7;
	speed = 300;
}

void Player::Update()
{
	if (inputManager.keyBuffer[VK_LEFT] == 1)
	{
		playerX -= speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_RIGHT] == 1)
	{
		playerX += speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_UP] == 1)
	{
		playerY -= speed * deltaTime;
	}
	if (inputManager.keyBuffer[VK_DOWN] == 1)
	{
		playerY += speed * deltaTime;
	}

	if (inputManager.prevKeyBuffer['Z'] == 0 &&
		inputManager.keyBuffer['Z'] == 1)
	{
		gameSystem.GeneratePlayerBulletSpread(playerX, playerY);
	}
}

void Player::Render()
{
	TextureElement* playerElement = textureManager.GetTexture(GAME_PLAYER_BODY);

	playerElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 31;
	srcRect.bottom = 46;

	D3DXVECTOR3 pos(playerX - 15, playerY - 23, 0);

	playerElement->sprite->Draw(playerElement->texture,&srcRect,nullptr,&pos,D3DCOLOR_XRGB(255,255,255));

	playerElement->sprite->End();
}