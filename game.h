#pragma once

#include "scene.h"

#define GAMESCENE_ENDTIME (120)	// �Q�[���I������J�ڂ܂ł̎���(�b)
// �V�[���ɂ܂Ƃ߂Ă����Q�[����ʓ��L�̋@�\���������Ɉڂ�
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