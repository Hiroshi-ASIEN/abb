/**************************************************
* TeamAreaHead�N���X
* [player.h]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include "teamArea.h"

#define COMPONENT_INDEX (20)


//==================================================
// TeamAreaHead�N���X
//==================================================
class TeamAreaHead :public GameObject
{
private:
	Component* m_ModelComponent;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_dt = 1.0f / 60.0f;		// �o�ߎ���

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
