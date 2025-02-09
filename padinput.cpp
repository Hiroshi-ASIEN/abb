#include <windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")//---★追加---

#include "padinput.h"

void PadInput::UpdateControllerState()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// コントローラーの状態を取得
	DWORD result = XInputGetState(0, &state);

	if (result == ERROR_SUCCESS) {
		// コントローラーが接続されている
		// ボタンの状態をチェック
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			// Aボタンが押された
		}
		// アナログスティックの状態をチェック
		SHORT lx = state.Gamepad.sThumbLX;
		SHORT ly = state.Gamepad.sThumbLY;
	}
	else {
		// コントローラーが接続されていない
	}
}