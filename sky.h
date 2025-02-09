/**************************************************
* Skyクラス
* [sky.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <list>

#define COMPONENT_INDEX (20)

//==================================================
// Skyクラス
//==================================================
class Sky :public GameObject
{
private:
	Component* m_ModelComponent;
	std::list<Component*> m_component;	// コンポーネント

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Move();
};




//////////////////// EOF ////////////////////
