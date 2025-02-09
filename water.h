#pragma once

#include "gameObject.h"


class Water:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;

	float m_fadeCount;
//	class Component*			m_BGM{};
	class Audio*				m_BGM{};


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetTexture(ID3D11ShaderResourceView*);
	void InitSet(const wchar_t* texture, XMFLOAT4 size);
	void SetPos(XMFLOAT4 size);

};