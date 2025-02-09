/**************************************************
* ロード用ロゴ表示
* [loadLogo.cpp]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"

class LoadLogo :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	XMFLOAT4 m_Color{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetColor(XMFLOAT4 color);
};