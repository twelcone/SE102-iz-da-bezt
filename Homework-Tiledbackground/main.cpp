/* =============================================================
	Homework 02: Adding Tiled Background of world 1-1 Mario
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"
//#include "Cloud.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAPBRICK_WIDTH 16

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_MAP 30
#define ID_TEX_CLOUD 40

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"
#define TEXTURE_PATH_MAP TEXTURES_DIR "\\map.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 160.0f
#define MARIO_START_VX 0.1f
#define GRASS_X 200.0f
#define GRASS_Y 164.0f
#define COIN_X 150.0f
#define COIN_Y 100.0f

CBrick *brick;

CGoomba *goomba;

int numMapBrick = 1 + SCREEN_WIDTH / MAPBRICK_WIDTH;
CMap** arrMapBrick = new CMap * [numMapBrick];
CMap2** arrMapBrick2 = new CMap2 * [numMapBrick];

CCloud** arrCloud = new CCloud * [12];

CGrass** arrGrass = new CGrass * [11];

CCoin** arrCoin = new CCoin * [3];

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMIES);
	//, D3DCOLOR_XRGB(156, 219, 239)
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_MAP, TEXTURE_PATH_MAP);


	CSprites * sprites = CSprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right 

	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 300, 117, 316, 133, texMisc);
	sprites->Add(20002, 318, 117, 334, 133, texMisc);
	sprites->Add(20003, 336, 117, 352, 133, texMisc);
	sprites->Add(20004, 354, 117, 370, 133, texMisc);

	LPTEXTURE texGoomba = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 59, 11, 78, 37, texGoomba);
	sprites->Add(30002, 81, 16, 102, 36, texGoomba);
	sprites->Add(30003, 81, 16, 102, 36, texGoomba);
	sprites->Add(30004, 59, 11, 78, 37, texGoomba);

	LPTEXTURE texMap = textures->Get(ID_TEX_MAP);
	sprites->Add(40001, 308, 128, 323, 143, texMap);
	sprites->Add(40002, 308, 110, 323, 125, texMap);

	LPTEXTURE texCloud = textures->Get(ID_TEX_MAP);
	sprites->Add(50000, 668, 255, 683, 270, texCloud);
	sprites->Add(50001, 686, 255, 701, 270, texCloud);
	sprites->Add(50002, 704, 255, 719, 270, texCloud);
	sprites->Add(50003, 668, 272, 683, 287, texCloud);
	sprites->Add(50004, 686, 272, 701, 287, texCloud);
	sprites->Add(50005, 704, 272, 719, 287, texCloud);

	LPTEXTURE texGrass = textures->Get(ID_TEX_MAP);
	sprites->Add(60000, 146, 20, 161, 35, texGrass);
	sprites->Add(60001, 164, 20, 179, 35, texGrass);
	sprites->Add(60002, 146, 38, 161, 53, texGrass);
	sprites->Add(60003, 164, 38, 179, 53, texGrass);
	sprites->Add(60004, 146, 38, 161, 53, texGrass);
	sprites->Add(60005, 164, 56, 179, 71, texGrass);
	sprites->Add(60006, 146, 38, 161, 53, texGrass);
	sprites->Add(60007, 164, 74, 179, 89, texGrass);
	sprites->Add(60008, 200, 56, 215, 71, texGrass);
	sprites->Add(60009, 200, 74, 215, 89, texGrass);
	sprites->Add(60010, 164, 20, 179, 35, texGrass);

	LPTEXTURE texCoin = textures->Get(ID_TEX_MAP);
	sprites->Add(70000, 182, 110, 197, 125, texCoin);
	sprites->Add(70001, 200, 110, 215, 125, texCoin);
	sprites->Add(70002, 218, 110, 233, 125, texCoin);
	sprites->Add(70003, 236, 110, 251, 125, texCoin);

	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(70000);
	ani->Add(70001);
	ani->Add(70002);
	ani->Add(70003);
	animations->Add(700, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	
	ani = new CAnimation(100);
	ani->Add(20001,1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);


	ani = new CAnimation(100);
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(520, ani);

	ani = new CAnimation(100);
	ani->Add(30003);
	ani->Add(30004);
	animations->Add(521, ani);

	ani = new CAnimation(100);
	ani->Add(40001);
	animations->Add(530, ani);

	ani = new CAnimation(100);
	ani->Add(40002);
	animations->Add(531, ani);

	ani = new CAnimation(100);
	ani->Add(60000);
	animations->Add(560, ani);

	for (int i = 0; i < 11; i++)
	{
		ani = new CAnimation(100);
		ani->Add(60000 + i);
		animations->Add(560 + i, ani);
	}

	
	for (int i = 0; i < 6; i++) {
		ani = new CAnimation(100);
		ani->Add(50000 + i);
		animations->Add(550 + i, ani);
	}
	
	
	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX);

	goomba = new CGoomba(MARIO_START_X + 20, MARIO_START_Y - 90, MARIO_START_VX * 0.8);

	brick = new CBrick(100.0f, 100.0f);

	for (int i = 0; i < 3; i++)
	{
		arrCoin[i] = new CCoin(COIN_X + 20*i, COIN_Y);
	}

	for (int i = 0; i < numMapBrick; i++)
	{
		arrMapBrick[i] = new CMap(MAPBRICK_WIDTH * i , MARIO_START_Y + 36);
		arrMapBrick2[i] = new CMap2(MAPBRICK_WIDTH * i , MARIO_START_Y + 20);
	}
	
	int arrX[12] = { 20, 36, 52, 20, 36, 52, 200, 216, 232, 200, 216, 232 };
	int arrY[12] = { 120, 120, 120, 105, 105, 105, 140, 140, 140, 125, 125, 125 };
	for (int i = 0; i < 12; i++)
	{
		arrCloud[i] = new CCloud(MARIO_START_X + arrX[i], MARIO_START_Y - arrY[i]);
	}

	int arrX_2[11] = { 0, 16, 0, 16, 0, 16, 0, 16, 32, 32, 32 };
	int arrY_2[11] = { 48, 48, 32, 32, 16, 16, 0, 0, 16, 0, 32 };

	for (int i = 0; i < 11; i++)
	{
		arrGrass[i] = new CGrass(GRASS_X + arrX_2[i], GRASS_Y - arrY_2[i]);
	}
	/*
	arrGrass[0] = new CGrass(GRASS_X, GRASS_Y - 48);
	arrGrass[1] = new CGrass(GRASS_X + 16, GRASS_Y - 48);
	arrGrass[2] = new CGrass(GRASS_X, GRASS_Y - 32);
	arrGrass[3] = new CGrass(GRASS_X + 16, GRASS_Y - 32);
	arrGrass[4] = new CGrass(GRASS_X, GRASS_Y - 16);
	arrGrass[5] = new CGrass(GRASS_X + 16, GRASS_Y - 16);
	arrGrass[6] = new CGrass(GRASS_X, GRASS_Y);
	arrGrass[7] = new CGrass(GRASS_X + 16, GRASS_Y);
	arrGrass[8] = new CGrass(GRASS_X + 32, GRASS_Y - 16);
	arrGrass[9] = new CGrass(GRASS_X + 32, GRASS_Y);
	arrGrass[10] = new CGrass(GRASS_X + 32, GRASS_Y - 32);
	*/
	/*
	arrCloud[0] = new CCloud(MARIO_START_X + 20, MARIO_START_Y - 130);
	arrCloud[1] = new CCloud(MARIO_START_X + 36, MARIO_START_Y - 130);
	arrCloud[2] = new CCloud(MARIO_START_X + 52, MARIO_START_Y - 130);
	arrCloud[3] = new CCloud(MARIO_START_X + 20, MARIO_START_Y - 115);
	arrCloud[4] = new CCloud(MARIO_START_X + 36, MARIO_START_Y - 115);
	arrCloud[5] = new CCloud(MARIO_START_X + 52, MARIO_START_Y - 115);
	arrCloud[6] = new CCloud(MARIO_START_X + 200, MARIO_START_Y - 140);
	arrCloud[7] = new CCloud(MARIO_START_X + 216, MARIO_START_Y - 140);
	arrCloud[8] = new CCloud(MARIO_START_X + 232, MARIO_START_Y - 140);
	arrCloud[9] = new CCloud(MARIO_START_X + 200, MARIO_START_Y - 125);
	arrCloud[10] = new CCloud(MARIO_START_X + 216, MARIO_START_Y - 125);
	arrCloud[11] = new CCloud(MARIO_START_X + 232, MARIO_START_Y - 125);
	*/
}
	
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	goomba->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();

		for (int i = 0; i < 11; i++)
		{
			arrGrass[i]->Render(i);
		}

		for (int i = 0; i < 3; i++)
		{
			arrCoin[i]->Render();
		}
		

		mario->Render();
		goomba->Render();
		for (int i = 0; i < numMapBrick; i++)
		{
			arrMapBrick[i]->Render();
			arrMapBrick2[i]->Render();
		}

		for (int i = 0; i < 6; i++)
		{
			arrCloud[i]->Render(i);
			arrCloud[i + 6]->Render(i);
		}

		

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}