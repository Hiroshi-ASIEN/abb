/**************************************************
* Menu表示用オブジェクト
* [menuVireObject.h]
* Author    ：松本紘始
* Date      ：2024年11月07日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <string>

class MenuVireObject :public GameObject
{
private:
	// モデル系
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

