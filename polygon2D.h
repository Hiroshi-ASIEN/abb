#pragma once

#include "gameObject.h"

enum FadeType
{
NonFade,
FadeIn,
FadeOut,
FadeTypeMax,
};

class Polygon2D:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;

	float m_fadeCount;
//	class Component*			m_BGM{};
//	class Audio*				m_BGM{};

	bool m_FadeFrag = false;
	FadeType m_FadeType = NonFade;
	XMFLOAT4 m_Color{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetTexture(ID3D11ShaderResourceView*);
	void InitSet(const wchar_t* texture, XMFLOAT4 size);
	void SetPos(XMFLOAT4 size);

	void SetColor(XMFLOAT4 color);
	void SetFade(FadeType type);
	bool Fade();

	bool GetFadeFrag();

};