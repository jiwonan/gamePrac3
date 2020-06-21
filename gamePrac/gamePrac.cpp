#include <Windows.h>
#include "framework.h"
#include "gamePrac.h"

#include "global.h"
#include "game_background.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 g_pd3dDevice;
HWND gWindowHandle;

bool GameRunning = true;

TextureManager textureManager;
InputManager inputManager;
StageManager stageManager;
GameSystem gameSystem;
CSoundManager soundManager;

CSound* pSound;

float deltaTime = 0.3f;
DWORD prevTime;
    
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void InitMySound(HWND hWnd)
{
    soundManager.Initialize(hWnd, DSSCL_NORMAL);
    {
        WCHAR filename[MAX_PATH];
        swprintf_s<MAX_PATH>(filename, L"sfx/lazer1.wav");
        soundManager.Create(&soundManager.sndPlayerBullet, filename, DSBCAPS_CTRLVOLUME);
    }

    {
        WCHAR filename[MAX_PATH];
        swprintf_s<MAX_PATH>(filename, L"sfx/epic_end.wav");
        soundManager.Create(&soundManager.sndStageOneBGM, filename, DSBCAPS_CTRLVOLUME);
    }

}

void InitMyStuff()
{
    textureManager.LoadTexture(L"backgrounds/title.png", TITLE_SCREEN_IMAGE);
    textureManager.LoadTexture(L"backgrounds/background.png", GAME_BACKGROUND_IMAGE);
    textureManager.LoadTexture(L"player/player1.png", GAME_PLAYER_BODY);
    textureManager.LoadTexture(L"player/player_bullet_1.png", GAME_PLAYER_BULLET_1);
    
    stageManager.LoadTitleStage();

    prevTime = GetTickCount();
}

void EngineUpdate()
{
    DWORD cur = GetTickCount();
    DWORD diff = cur - prevTime;
    deltaTime = diff / 1000.0f;

    if (deltaTime > 0.016)
    {
        deltaTime = 0.016;
    }

    prevTime = cur;

    if (inputManager.keyBuffer[VK_ESCAPE] == 1)
    {
        GameRunning = false;
    }

    stageManager.Update();
    inputManager.Update();
}

VOID EngineRender()
{
    if (NULL == g_pd3dDevice)
        return;

    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        stageManager.Render();

        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT InitD3D(HWND hWnd)
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    // d3dpp.Windowed = false;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    
    /*d3dpp.BackBufferWidth = WINDOW_WIDTH;
    d3dpp.BackBufferHeight = WINDOW_HEIGHT;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;*/

    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    return S_OK;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEPRAC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEPRAC));

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT && GameRunning == true)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            EngineUpdate();
            EngineRender();
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEPRAC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   gWindowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!gWindowHandle)
   {
      return FALSE;
   }

   InitD3D(gWindowHandle);
   InitMyStuff();
   InitMySound(gWindowHandle);

   ShowWindow(gWindowHandle, nCmdShow);
   UpdateWindow(gWindowHandle);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
       {
            inputManager.keyBuffer[wParam] = 1;
            break;
       }
    case WM_KEYUP:
    { 
        inputManager.keyBuffer[wParam] = 0;
        break;
    }

    case WM_LBUTTONDOWN:
    {
        inputManager.keyBuffer[VK_LBUTTON] = 1;
        break;
    }

    case WM_LBUTTONUP:
    {
        inputManager.keyBuffer[VK_LBUTTON] = 0;
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}