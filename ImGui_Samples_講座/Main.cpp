#include "Main.h"

#include "DirectX.h"
#include "Geometory.h"
#include "Scene.h"
#include "SceneGame.h"

namespace
{
	Scene* g_pScene = nullptr;
}

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr))
	{
		return hr;
	}

	Geometory::Init();
	g_pScene = new SceneGame();
	return S_OK;
}

void Uninit()
{
	if (g_pScene)
	{
		delete g_pScene;
		g_pScene = nullptr;
	}

	Geometory::Uninit();
	UninitDirectX();
}

void Update()
{
	if (g_pScene)
	{
		g_pScene->RootUpdate();
	}
}

void Draw()
{
	BeginDrawDirectX();
	if (g_pScene)
	{
		g_pScene->RootDraw();
	}
	EndDrawDirectX();
}
