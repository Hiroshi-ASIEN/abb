#include "main.h"
#include "renderer.h"
#include "testObject.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"


void TestObject::Init()
{
	m_ModelComponent = new ModelRenderer(this);
	((ModelRenderer*)m_ModelComponent)->Load("asset\\model\\sphere_smooth.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\envMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\envMappingPS.cso");

	TexMetadata metadata1;
	ScratchImage image1;
	LoadFromWICFile(L"asset\\texture\\ster.png", WIC_FLAGS_NONE, &metadata1, image1);
	CreateShaderResourceView(Renderer::GetDevice(), image1.GetImages(), image1.GetImageCount(), metadata1, &m_Texture);
	assert(m_Texture);

	TexMetadata metadata;
	ScratchImage image;
	//	LoadFromWICFile(L"asset\\texture\\earthenvmap.png", WIC_FLAGS_NONE, &metadata, image);
	LoadFromWICFile(L"asset\\texture\\canary_wharf.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);

}

void TestObject::Uninit()
{
	delete m_ModelComponent;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Texture->Release();
	m_EnvTexture->Release();
}

void TestObject::Update()
{
//	m_Rotation.x += 0.01f;
	m_Rotation.z += 0.01f;
}

void TestObject::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);


	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	// テクスチャ設定(特殊なテクスチャを1に設定してみる
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_EnvTexture);



	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);

	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelComponent->Draw();

}