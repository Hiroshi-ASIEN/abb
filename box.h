/**************************************************
* Boxクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"

#define COMPONENT_INDEX (20)

//==================================================
// Boxクラス
//==================================================
class Box :public GameObject
{
private:
	class BoxSpowner* spowner;

	Component* m_ModelComponent;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT3 m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Accel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float m_dt = 1.0f / 60.0f;		// 経過時間

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Move();
	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();

	void Accept(Component* component);
	void TrackingBox();
};




//////////////////// EOF ////////////////////
