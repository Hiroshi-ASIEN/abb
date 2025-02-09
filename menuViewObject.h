/**************************************************
* Menu�\���p�I�u�W�F�N�g
* [menuVireObject.h]
* Author    �F���{�h�n
* Date      �F2024�N11��07��
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <string>

class MenuVireObject :public GameObject
{
private:
	// ���f���n
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT4 m_Material{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetModel(const char* FileName);
};

