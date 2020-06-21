#include "title_stage.h"
#include "global.h"

void TitleStage::Update()
{

	if (inputManager.prevKeyBuffer[VK_LBUTTON] == 1 &&
		inputManager.keyBuffer[VK_LBUTTON] == 0)
	{
		stageManager.LoadGameFirstStage();
	}
}

void TitleStage::Render()
{
	TextureElement* titleElement = textureManager.GetTexture(TITLE_SCREEN_IMAGE);

	titleElement->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 640;
	srcRect.bottom = 480;

	titleElement->sprite->Draw(titleElement->texture, &srcRect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

	titleElement->sprite->End();
}