#include <windows.h>
#include <mmsystem.h>

#include "Defines.h"
#include "DirectX.h"
#include "Main.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "winmm.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wcex.lpszClassName = L"ImGuiSceneGameSample";

	if (!RegisterClassExW(&wcex))
	{
		MessageBoxW(nullptr, L"Failed to RegisterClassExW.", L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	AdjustWindowRect(&rect, style, FALSE);

	HWND hWnd = CreateWindowW(
		wcex.lpszClassName,
		APP_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!hWnd)
	{
		UnregisterClassW(wcex.lpszClassName, hInstance);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	RECT clientRect = {};
	GetClientRect(hWnd, &clientRect);
	UINT clientWidth = static_cast<UINT>(clientRect.right - clientRect.left);
	UINT clientHeight = static_cast<UINT>(clientRect.bottom - clientRect.top);
	if (clientWidth == 0) clientWidth = SCREEN_WIDTH;
	if (clientHeight == 0) clientHeight = SCREEN_HEIGHT;

	if (FAILED(Init(hWnd, clientWidth, clientHeight)))
	{
		Uninit();
		DestroyWindow(hWnd);
		UnregisterClassW(wcex.lpszClassName, hInstance);
		return 0;
	}

	timeBeginPeriod(1);
	DWORD previousTick = timeGetTime();
	MSG message = {};

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
			continue;
		}

		const DWORD currentTick = timeGetTime();
		const float elapsedMs = static_cast<float>(currentTick - previousTick);
		if (elapsedMs < (1000.0f / fFPS))
		{
			Sleep(1);
			continue;
		}

		Update();
		Draw();
		previousTick = currentTick;
	}

	timeEndPeriod(1);
	Uninit();
	UnregisterClassW(wcex.lpszClassName, hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return TRUE;
	}

	switch (message)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			OnResizeDirectX(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
