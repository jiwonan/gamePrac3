#pragma once

#include <d3d9.h>

#include "texture_manager.h"
#include "input_manager.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

extern LPDIRECT3D9 g_pD3D;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern HWND gWindowHandle;

// all the managers
extern TextureElement textureManager;
extern InputManager inputManager;