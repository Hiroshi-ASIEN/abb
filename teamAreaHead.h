/**************************************************
* TeamAreaHeadクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include "teamArea.h"

#define COMPONENT_INDEX (20)


//==================================================
// TeamAreaHeadクラス
//==================================================
class TeamAreaHead :public GameObject
{
private:
	Component* m_ModelComponent;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_dt = 1.0f / 60.0f;		// 経過時間

	AreaState m_AreaState{};

	XMFLOAT4 m_Color{};
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void RotationLoop();
	void ChangeType(AreaState type);

	void ColorChange(XMFLOAT4 color);
};




//////////////////// EOF ////////////////////
