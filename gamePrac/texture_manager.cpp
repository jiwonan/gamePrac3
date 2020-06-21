#include "texture_manager.h"
#include "global.h"

void TextureManager::LoadTexture(const TCHAR* name, int id)
{
	TextureElement* newTexture = new TextureElement();

	newTexture->id = id;
	D3DXCreateSprite(g_pd3dDevice, &newTexture->sprite);
	D3DXCreateTextureFromFile(g_pd3dDevice, name, &newTexture->texture);

	elements.push_back(newTexture);
}

TextureElement* TextureManager::GetTexture(const int id)
{
	for (int i; i < elements.size(); ++i)
	{
		if (elements[i]->id == id)
		{
			return elements[i];
		}
	}
	return nullptr;
}
