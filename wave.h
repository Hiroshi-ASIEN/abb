#pragma once

// meshField	 通常の名前とは異なる可能性があるため注意

#include "gameObject.h"
#include <list>

#define WAVE_AMPLITUDE (20.0f)	// 振幅(波高)
#define WAVE_LENGTH (40.0f)		// 波長
#define WAVE_CYCLE (10.0f)		// 周期

class Wave :public GameObject
{
private:
	ID3D11Buffer* m_IndexBuffer = NULL;	// インデックスバッファ

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_envTexture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	// 縦横20分割したいので、20+1 (2にしたければ2+1)
	VERTEX_3D m_Vertex[21][21]{};	// 頂点データ
	std::list<VERTEX_3D> x{};
	std::list<VERTEX_3D> z{};

	float m_Time{};
	float dx{};
	float dz{};
	float length{};
	XMFLOAT4 m_Material{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(XMFLOAT3 Position);

	void seta(float a[21][21]);
};