#pragma once

#include "gameObject.h"

// �G�t�F�N�g��3d�ō��W�w�肷��̂�3d�I�u�W�F�N�g
class Tree :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	static ID3D11ShaderResourceView* m_Texture;

	ID3D11Buffer* m_PositionBuffer{};
	ID3D11ShaderResourceView* m_PositionSRV{};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_AnimeCount{};	// ������

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetXZPosition(XMFLOAT3 pos);

	static void Load();
	static void Unload();
};