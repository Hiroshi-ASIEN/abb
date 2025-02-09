#pragma once

// meshFieldBattle	 �ʏ�̖��O�Ƃ͈قȂ�\�������邽�ߒ���

#include "gameObject.h"
#include "meshField.h"

#define VERTEX_DATA_FIELD_1 (21)
#define VERTEX_DATA_FIELD_2 (42)

enum FieldType
{
	Field1 = 0,
	FieldMax,
};

class MeshField_Battle :public MeshField
{
private:
	ID3D11Buffer* m_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	// �c��20�����������̂ŁA20+1 (2�ɂ��������2+1)
	VERTEX_3D m_VertexB[VERTEX_DATA_FIELD_2][VERTEX_DATA_FIELD_2]{};	// ���_�f�[�^

	int m_VertexData{};


	bool m_InitFinish{};


public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	float GetHeight(XMFLOAT3 Position)override;

	void seta(float a[VERTEX_DATA_FIELD_2][VERTEX_DATA_FIELD_2]);

	bool GetInitFinish()override;

	void SetField(FieldType _fieldType);


};