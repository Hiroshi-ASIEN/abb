#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "disneyPBR.h"
#include "input.h"

void DisneyPBR::Init()
{
	m_Model = new CModel();
	m_Model->Load( "asset\\model\\torus.obj" );

	m_Position = D3DXVECTOR3( 6.0f, 1.0f, 0.0f );//<========�\�����W
	m_Rotation = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Scale = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	//�ǂݍ��ރV�F�[�_�[��cso�t�@�C���ł��邱�Ƃɒ��Ӂ@���ƃt�@�C���p�X�����ӁI
	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "disneyPBRVS.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "disneyPBRPS.cso");


}

void DisneyPBR::Uninit()
{
	m_Model->Unload();
	delete m_Model;


	//�����ɃV�F�[�_�[�I�u�W�F�N�g�̉����ǉ�
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void DisneyPBR::Update()
{
	if (CInput::GetKeyPress('A'))
		m_Position.x -= 0.1f;

	if (CInput::GetKeyPress('D'))
		m_Position.x += 0.1f;

	if (CInput::GetKeyPress('W'))
		m_Position.z += 0.1f;

	if (CInput::GetKeyPress('S'))
		m_Position.z -= 0.1f;


	if (CInput::GetKeyPress('R'))
		m_Rotation.x -= 0.1f;
	if (CInput::GetKeyPress('F'))
		m_Rotation.x += 0.1f;

	if (CInput::GetKeyPress('Q'))
		m_Rotation.y -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_Rotation.y += 0.1f;

}

void DisneyPBR::Draw()
{
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);

	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);		// ����
	light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);		// ���C�g�F
	light.Position = D3DXVECTOR4(0.0f, 2.0f, -5.0f, 0.0f);	// ���C�g���W
	light.PointLightParam = D3DXVECTOR4(100.0f, 5.0f, 0.5f, 0.5f);

	CRenderer::SetLight(light);

	//return;
	//�C���v�b�g���C�A�E�g�̃Z�b�g�iDirectX�֒��_�̍\����������j
	CRenderer::GetDeviceContext()->
		IASetInputLayout(m_VertexLayout);

	//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->
		VSSetShader(m_VertexShader, NULL, 0);

	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	CRenderer::GetDeviceContext()->
		PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}


