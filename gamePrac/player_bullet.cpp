#include "player_bullet.h"
#include "global.h"

PlayerBullet::PlayerBullet(float x, float y, float vx, float vy)
{
	posX = x;
	posY = y;

	velX = vx;
	velY = vy;

	isDead = false;
}

void PlayerBullet::Update()
{
	posX += velX;
	posY += velY;

	if (posX<0 || posX>WINDOW_WIDTH ||
		posY<0 || posX>WINDOW_HEIGHT)
	{
		isDead = true;
	}
}

void PlayerBullet::Render()
{
	TextureElement* bulletElement = textureManager.GetTexture(GAME_PLAYER_BULLET_1);

	bulletElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 11;
	srcRect.bottom = 11;

	D3DXVECTOR3 pos(posX - 5, posY - 5, 0);

	bulletElement->sprite->Draw(bulletElement->texture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	bulletElement->sprite->End();
}

D3DXVECTOR2 PlayerBullet::GetPosition()
{
	return D3DXVECTOR2(posX, posY);
}

float PlayerBullet::GetRadius()
{
	return 5.0f;
}

bool PlayerBullet::IsDead()
{
	return isDead;
}