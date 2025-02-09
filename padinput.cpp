#include <windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")//---���ǉ�---

#include "padinput.h"

void PadInput::UpdateControllerState()
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// �R���g���[���[�̏�Ԃ��擾
	DWORD result = XInputGetState(0, &state);

	if (result == ERROR_SUCCESS) {
		// �R���g���[���[���ڑ�����Ă���
		// �{�^���̏�Ԃ��`�F�b�N
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			// A�{�^���������ꂽ
		}
		// �A�i���O�X�e�B�b�N�̏�Ԃ��`�F�b�N
		SHORT lx = state.Gamepad.sThumbLX;
		SHORT ly = state.Gamepad.sThumbLY;
	}
	else {
		// �R���g���[���[���ڑ�����Ă��Ȃ�
	}
}