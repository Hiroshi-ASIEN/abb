#pragma once

// meshField	 �ʏ�̖��O�Ƃ͈قȂ�\�������邽�ߒ���

#include "gameObject.h"
#include <list>

#define WAVE_AMPLITUDE (20.0f)	// �U��(�g��)
#define WAVE_LENGTH (40.0f)		// �g��
#define WAVE_CYCLE (10.0f)		// ����

class Wave :public GameObject
{
private:
	ID3D11Buffer* m_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;
	ID3D11ShaderResourceView* m_envTexture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	// �c��20�����������̂ŁA20+1 (2�ɂ��������2+1)
	VERTEX_3D m_Vertex[21][21]{};	// ���_�f�[�^
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