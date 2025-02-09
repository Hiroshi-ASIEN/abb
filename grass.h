#pragma once

#include "gameObject.h"

// �G�t�F�N�g��3d�ō��W�w�肷��̂�3d�I�u�W�F�N�g
class Grass :public GameObject
{
private:
	ID3D11ShaderResourceView* m_Texture;	// �e�N�X�`���g�p�p
	static ID3D11ShaderResourceView* m_GrassTexture0;
	static ID3D11ShaderResourceView* m_GrassTexture1;
	static ID3D11ShaderResourceView* m_GrassTexture2;
	static ID3D11ShaderResourceView* m_GrassTexture3;

	ID3D11Buffer* m_VertexBuffer = NULL;

	// ID3D11Buffer�͔ėp�����������ł�������
	ID3D11Buffer* m_PositionBuffer{};			// GPU�֍��W��񑗐M�p...���ۂɒl�������Ă���
	ID3D11ShaderResourceView* m_PositionSRV{};	// PositionBuffer�փA�N�Z�X���邽�߂̑����p

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetXZPosition(XMFLOAT3 pos);

	void SetType(int i);

	void SetRandomRange(int _xRange, int _xOffSet, int _zRange, int _zOffSet);


	static void Load();
	static void Unload();
};