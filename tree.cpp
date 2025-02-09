/**************************************************
* �t�B�[���h����
* [Tree.cpp]
* Author    �F���{�h�n
* Date      �F2024�N05��15��
***************************************************/

#include "main.h"
#include "renderer.h"
#include "tree.h"
#include "manager.h"
#include "camera.h"
#include "meshField.h"

ID3D11ShaderResourceView* Tree::m_Texture{};

void Tree::Init()
{

	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f,-1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;		// GPU���̒��_�o�b�t�@�̓��e��ς��邽�߂̐ݒ�
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	/*
	// �e�N�X�`���Ǎ�
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\Tree01.png", WIC_FLAGS_NONE, &metadata, image);
	//	LoadFromWICFile(L"asset\\texture\\dentou.png", WIC_FLAGS_NONE, &metadata, image);

	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
	*/

	// �X�g���N�`���[�h�o�b�t�@
	{
		int pMax = 100;	// �萔
		// �ꎞ�f�[�^�@���������[�N����̂��ߏ�������
		XMFLOAT3* pos = new XMFLOAT3[pMax];
		Scene* scene = Manager::GetScene();
		float groundHeight;	// �n�ʂ̍���

		{
			float x, z;
			for (int j = 0; j < pMax; j++)
			{
				x = 1.0f * (rand() % 40 - 0);
				z = 1.0f * (rand() % 40 - 0);
				groundHeight = scene->GetGameObject<MeshField>()->GetHeight(XMFLOAT3{ x,1.0f,z });
				pos[j] = XMFLOAT3(x, groundHeight + m_Scale.y, z);
			}
		}

		// �X�g���N�`���[�h�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(XMFLOAT3) * pMax;
		bd.StructureByteStride = sizeof(XMFLOAT3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pos;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_PositionBuffer);

		// �ꎞ�f�[�^�폜
		delete[] pos;

		// �V�F�[�_�[���\�[�X�r���[����
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = pMax;
		Renderer::GetDevice()->CreateShaderResourceView(m_PositionBuffer, &srvd, &m_PositionSRV);
	}
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS2.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexture2DPS.cso");

	SetScale(XMFLOAT3(2.0f, 2.0f, 2.0f));
}
void Tree::Uninit()
{
	m_VertexBuffer->Release();
	if (m_PositionSRV) m_PositionSRV->Release();
	if (m_PositionBuffer) m_PositionBuffer->Release();


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Tree::Update()
{

}

void Tree::Draw()
{

	// �e�N�X�`�����W�Z�o
//	float x = m_AnimeCount % 4 * (1.0f / 4);
//	float y = m_AnimeCount / 4 * (1.0f / 4);
	
	// ���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	// ���������Ă��Ȃ�������������Ə���
	// unmap�͑O�̃f�[�^�������Ă��܂�����B
	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f,0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f,1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f,1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// �J�����̃r���[�}�g���N�X�擾
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();

	//�r���[�̋t�s��
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);	// �t�s��
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;



	// ���[���h�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//	world = scale * rot * trans;

	world = scale * invView * trans;

	Renderer::SetWorldMatrix(world);
	
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	// �X�g���N�`���[�h�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Alpha To Coverage	(�������ɂ͑Ή��ł��Ȃ��̂ŁAEffect���ɂ͎g���Ȃ��j
	// �����ȉӏ����������܂�Ȃ��Ȃ�ݒ�	�L��
	// �|���S���`��
//	Renderer::SetATCEnable(true);
//	Renderer::GetDeviceContext()->Draw(4, 0);

// �W�I���g���C���X�^���V���O
	Renderer::GetDeviceContext()->DrawInstanced(4, 100, 0, 0);

	// �����ȉӏ����������܂�Ȃ��Ȃ�ݒ�	����
//	Renderer::SetATCEnable(false);

}

void Tree::SetXZPosition(XMFLOAT3 pos)
{
	Scene* scene = Manager::GetScene();
	float groundHeight;	// �n�ʂ̍���
	groundHeight = scene->GetGameObject<MeshField>()->GetHeight(pos);
	groundHeight += 1.0f * (this->m_Scale.y / 2);
	this->SetPosition({ pos.x,groundHeight,pos.z });
}

void Tree::Load()
{
	// �e�N�X�`���Ǎ�
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\Tree01.png", WIC_FLAGS_NONE, &metadata, image);
	//	LoadFromWICFile(L"asset\\texture\\dentou.png", WIC_FLAGS_NONE, &metadata, image);

	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
}

void Tree::Unload()
{
	m_Texture->Release();
}
