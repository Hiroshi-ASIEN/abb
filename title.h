#pragma once

#include "scene.h"

class Title :public Scene
{
private:
	Polygon2D* m_Fade{};
	UI* m_Title{};
	UI* m_Push{};
	class Mosaic* m_TitleLoad{};
	class UI* m_LoadGage{};
	UI* m_GageFrame{};

	float x = 1.0f;
	float i{};

	bool m_NextScene = false;

	static bool m_LoadFinish;	
	static float m_LoadValue;
public:
	void Init()override;
	void SecondInit();
	void Uninit()override;
	void Update()override;
	void Fade();
//	void Draw()override;

	static void Load();
	static void Unload();
};