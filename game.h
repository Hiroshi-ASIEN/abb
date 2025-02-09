#pragma once

#include "scene.h"

#define GAMESCENE_ENDTIME (120)	// ゲーム終了から遷移までの時間(秒)
// シーンにまとめていたゲーム画面特有の機能をこっちに移す
class Game :public Scene
{
	Player* player;
	Polygon2D* m_Fade;

	bool m_NextScene{};
	static bool m_LoadFinish;
public:
	static void Load();

	void Init() override;
	void Uninit()override;
	void Update() override;

	static bool GetFinish();

	static void GameEnd(bool _win);
};