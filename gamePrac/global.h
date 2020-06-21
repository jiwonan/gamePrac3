#pragma once

#include <d3d9.h>

#include "texture_manager.h"
#include "input_manager.h"
#include "stage_manager.h"
#include "game_system.h"
#include "SDKsound.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define TITLE_SCREEN_IMAGE 1000

#define GAME_BACKGROUND_IMAGE 2000

#define GAME_PLAYER_BODY 3000
#define GAME_PLAYER_BULLET_1 3001

extern LPDIRECT3D9 g_pD3D;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern HWND gWindowHandle;

extern float deltaTime;

// all the managers
extern TextureManager textureManager;
extern InputManager inputManager;
extern StageManager stageManager;
extern GameSystem gameSystem;
extern CSoundManager soundManager;