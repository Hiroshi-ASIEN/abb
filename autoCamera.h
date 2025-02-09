#pragma once
#include "camera.h"

class AutoCamera :public Camera
{

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void AutoCameraMove();
	void AutoCameraFollow();

};