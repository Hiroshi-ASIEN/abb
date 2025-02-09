#pragma once

#include "scene.h"

class Result :public Scene
{
	bool m_NextScene = false;
	Polygon2D* m_Fade{};
public:
	void Init()override;
//	void Uninit();
	void Update()override;
//	void Draw();

	void GameOver();
	void GameClear();
};

class GameClear :public Scene
{
	bool m_NextScene = false;
	Polygon2D* m_Fade{};
	Polygon2D* m_Clear{};
	float x = 1.0f;
	float i = 0.01f;
public:
	void Init()override;
//	void Uninit();
	void Update()override;
	//	void Draw();
};

class GameOver :public Scene
{
	bool m_NextScene = false;
	Polygon2D* m_Fade{};
	Polygon2D* m_Over{};
	float x = 1.0f;
	float i = 0.01f;
public:
	void Init()override;
	//	void Uninit();
	void Update()override;
	//	void Draw();
};
