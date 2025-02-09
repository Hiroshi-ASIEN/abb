//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// フェードの状態
enum FADE_STATE
{
	FADE_NONE = 0,	// フェード処理をしていない
	FADE_IN,			// フェードイン処理中
	FADE_OUT,			// フェードアウト処理中
	FADE_MAX
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class Fade
{
private:
//	int			m_TextureNo;				// テクスチャ番号

	FADE_STATE	m_FadeState = FADE_NONE;	// フェードの状態
	XMFLOAT4 m_Color;					// フェードのカラー

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
	   フェードアウト・フェードイン処理をしながらシーン遷移する関数
	------------------------------------------------------------------------------*/
	template<typename T>	// テンプレート関数
	void SceneTransition()
	{
//		g_SceneNext = nextScene;
//		g_FadeState = FADE_OUT;

		Manager::SetScene<T>();
	}

	/*------------------------------------------------------------------------------
	   フェードイン処理をしながらシーンを開始する関数
	------------------------------------------------------------------------------*/
	template<typename T>	// テンプレート関数
	void SceneFadeIn()
	{
		g_Color.a = 1.0f;
		g_FadeState = FADE_IN;

		Manager::SetScene<T>();
//		SetScene(nextScene);
	}
}