#pragma once

// meshField	 �ʏ�̖��O�Ƃ͈قȂ�\�������邽�ߒ���

#include "gameObject.h"
#include <list>

#define STAGE_1_X (21)
#define STAGE_1_Y (21)


class MeshField :public GameObject
{
protected:
	ID3D11Buffer* m_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	// �c��20�����������̂ŁA20+1 (2�ɂ��������2+1)
	VERTEX_3D m_Vertex[21][21]{};	// ���_�f�[�^
	std::list<VERTEX_3D> x;
	std::list<VERTEX_3D> z;


	bool m_InitFinish{};

	XMFLOAT3 m_FieldCollision{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	virtual float GetHeight(XMFLOAT3 Position);

	void seta(float a[21][21]);

	virtual bool GetInitFinish();
	XMFLOAT3 GetFieldScale();
};