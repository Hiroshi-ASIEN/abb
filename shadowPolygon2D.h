#pragma once

#include "gameObject.h"

class ShadowPolygon2D:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;


	XMFLOAT4 m_Color{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetShadowColor(XMFLOAT4 color);
};