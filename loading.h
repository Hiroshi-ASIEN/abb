#pragma once

#include "scene.h"

class Loading :public Scene
{
private:
	Polygon2D* m_Fade{};
	bool m_NextScene = false;
	class LoadLogo* m_Loading{};
	float x = 1.0f;
	float i = 0.01f;
	float z = 0.0f;

public:
	void Init()override;
	//	void Uninit()override;
	void Update()override;
	void Fade();
	//	void Draw()override;
};