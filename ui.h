#pragma once

#include "gameObject.h"

// 練習用クラス
class UI:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;

	class Audio*				m_BGM{};
	XMFLOAT4 m_Color{};
//	class Player* player;
	XMFLOAT4 m_Size{};
public:
//	using Component::Component;

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetTexture(ID3D11ShaderResourceView*);
	void InitSet(const wchar_t* texture, XMFLOAT4 size,int type);

	void SetColor(XMFLOAT4 color);
	// size = x:横0地点、y:縦0地点、z:横max地点、w縦max地点
	void SetPos(XMFLOAT4 size);
	void SetSize(XMFLOAT4 size);

};