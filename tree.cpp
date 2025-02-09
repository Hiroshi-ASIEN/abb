/**************************************************
* フィールド処理
* [Tree.cpp]
* Author    ：松本紘始
* Date      ：2024年05月15日
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

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;		// GPU側の頂点バッファの内容を変えるための設定
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//

	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	/*
	// テクスチャ読込
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\Tree01.png", WIC_FLAGS_NONE, &metadata, image);
	//	LoadFromWICFile(L"asset\\texture\\dentou.png", WIC_FLAGS_NONE, &metadata, image);

	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
	*/

	// ストラクチャードバッファ
	{
		int pMax = 100;	// 定数
		// 一時データ　メモリリーク回避のため消すこと
		XMFLOAT3* pos = new XMFLOAT3[pMax];
		Scene* scene = Manager::GetScene();
		float groundHeight;	// 地面の高さ

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

		// ストラクチャードバッファ生成
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

		// 一時データ削除
		delete[] pos;

		// シェーダーリソースビュー生成
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

	// テクスチャ座標算出
//	float x = m_AnimeCount % 4 * (1.0f / 4);
//	float y = m_AnimeCount / 4 * (1.0f / 4);
	
	// 頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	// 書き換えていない部分もきちんと書く
	// unmapは前のデータを消してしまうから。
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


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// カメラのビューマトリクス取得
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();

	//ビューの逆行列
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);	// 逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;



	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//	world = scale * rot * trans;

	world = scale * invView * trans;

	Renderer::SetWorldMatrix(world);
	
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	// ストラクチャードバッファ設定
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Alpha To Coverage	(半透明には対応できないので、Effect等には使えない）
	// 透明な箇所が書き込まれなくなる設定	有効
	// ポリゴン描画
//	Renderer::SetATCEnable(true);
//	Renderer::GetDeviceContext()->Draw(4, 0);

// ジオメトリインスタンシング
	Renderer::GetDeviceContext()->DrawInstanced(4, 100, 0, 0);

	// 透明な箇所が書き込まれなくなる設定	無効
//	Renderer::SetATCEnable(false);

}

void Tree::SetXZPosition(XMFLOAT3 pos)
{
	Scene* scene = Manager::GetScene();
	float groundHeight;	// 地面の高さ
	groundHeight = scene->GetGameObject<MeshField>()->GetHeight(pos);
	groundHeight += 1.0f * (this->m_Scale.y / 2);
	this->SetPosition({ pos.x,groundHeight,pos.z });
}

void Tree::Load()
{
	// テクスチャ読込
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
