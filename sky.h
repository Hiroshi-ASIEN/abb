/**************************************************
* Sky�N���X
* [sky.h]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <list>

#define COMPONENT_INDEX (20)

//==================================================
// Sky�N���X
//==================================================
class Sky :public GameObject
{
private:
	Component* m_ModelComponent;
	std::list<Component*> m_component;	// �R���|�[�l���g

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
