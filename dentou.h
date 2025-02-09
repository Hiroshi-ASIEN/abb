#pragma once

#include "gameObject.h"

// エフェクトは3dで座標指定するので3dオブジェクト
class Dentou :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11Buffer* m_PositionBuffer{};
	ID3D11ShaderResourceView* m_PositionSRV{};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_AnimeCount{};	// 初期化

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetXZPosition(XMFLOAT3 pos);


};