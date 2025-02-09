/**************************************************
*	
*	main.cpp
***************************************************/

#include "main.h"
#include "manager.h"
#include <thread>

#include "padinput.h"

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ゲーム";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);


	Manager::Init();		// Manager初期化



	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	int frameCount = 0;

	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				frameCount++;
				if (frameCount > 60)
				{
					frameCount = 0;

					// フレームレート計測
					float fps = 1000.0f / (dwCurrentTime - dwExecLastTime);
					std::string title;
					title = std::string(WINDOW_NAME) + " " + std::to_string(fps) + "fps";
					SetWindowText(g_Window, title.c_str());
				}

				dwExecLastTime = dwCurrentTime;

//				UpdateControllerState();

				Manager::Update();
				Manager::Draw();
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	CoUninitialize();


	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

 	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void ClipMouseCursorToWindow()
{
	HWND hWnd = GetWindow();
	// ウィンドウのクライアント領域を取得
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	// ウィンドウのスクリーン座標を取得
	POINT topLeft = { clientRect.left, clientRect.top };
	POINT bottomRight = { clientRect.right, clientRect.bottom };

	ClientToScreen(hWnd, &topLeft);
	ClientToScreen(hWnd, &bottomRight);

	RECT clipRect = { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };

	// カーソルをウィンドウ内に制限
	ClipCursor(&clipRect);
}
void ClipMouseCursorToSmallerArea()
{
	HWND hWnd = GetWindow();

	// ウィンドウのクライアント領域を取得
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	// ウィンドウのスクリーン座標を取得
	POINT topLeft = { clientRect.left, clientRect.top };
	POINT bottomRight = { clientRect.right, clientRect.bottom };

	ClientToScreen(hWnd, &topLeft);
	ClientToScreen(hWnd, &bottomRight);

	// 制限する領域をウィンドウサイズよりも少し小さくする
	int margin = 10; // ウィンドウの内側に10ピクセルの余白をつける
	RECT clipRect = { topLeft.x + margin, topLeft.y + margin, bottomRight.x - margin, bottomRight.y - margin };

	// カーソルを制限する
	ClipCursor(&clipRect);
}

// カーソルの制限を解除するには、ClipCursorにNULLを渡す
void UnclipMouseCursor()
{
	ClipCursor(NULL);
}
