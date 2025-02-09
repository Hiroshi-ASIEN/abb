//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �t�F�[�h�̏��
enum FADE_STATE
{
	FADE_NONE = 0,	// �t�F�[�h���������Ă��Ȃ�
	FADE_IN,			// �t�F�[�h�C��������
	FADE_OUT,			// �t�F�[�h�A�E�g������
	FADE_MAX
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class Fade
{
private:
//	int			m_TextureNo;				// �e�N�X�`���ԍ�

	FADE_STATE	m_FadeState = FADE_NONE;	// �t�F�[�h�̏��
	XMFLOAT4 m_Color;					// �t�F�[�h�̃J���[

public:
	HRESULT InitFade(void);
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);

//	void SceneFadeIn(SCENE nextScene);
//	void SceneTransition(SCENE nextScene);
	FADE_STATE GetFadeState(void);

	void SetFadeColor(float r, float g, float b);

	/*------------------------------------------------------------------------------
	   �t�F�[�h�A�E�g�E�t�F�[�h�C�����������Ȃ���V�[���J�ڂ���֐�
	------------------------------------------------------------------------------*/
	template<typename T>	// �e���v���[�g�֐�
	void SceneTransition()
	{
//		g_SceneNext = nextScene;
//		g_FadeState = FADE_OUT;

		Manager::SetScene<T>();
	}

	/*------------------------------------------------------------------------------
	   �t�F�[�h�C�����������Ȃ���V�[�����J�n����֐�
	------------------------------------------------------------------------------*/
	template<typename T>	// �e���v���[�g�֐�
	void SceneFadeIn()
	{
		g_Color.a = 1.0f;
		g_FadeState = FADE_IN;

		Manager::SetScene<T>();
//		SetScene(nextScene);
	}
}