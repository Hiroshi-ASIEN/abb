/**************************************************
* フィールド処理
* [Field.cpp]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/

#include "main.h"
#include "renderer.h"
#include "meshField.h"

float g_FieldHeight[21][21] =
{
	/*
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	*/
/*
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,1.0,3.0,7.0,5.0,0.0,2.0,2.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,1.0,4.0,0.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,1.0,2.0,1.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,1.0,2.0,2.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,2.0,4.0,4.0,4.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,2.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,4.0,6.0,8.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0,2.0,3.0,2.0,1.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,4.0,6.0,7.0,10.0,2.0,1.0,0.0,0.0,0.0,0.0,0.0,1.0,2.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,2.0,4.0,6.0,4.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,2.0,2.0,1.0,0.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,4.0,2.0,3.0,2.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,4.0,3.0,5.0,3.0,0.0,0.0,2.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,5.0,3.0,4.0,1.0,0.1,0.0,2.0,0.0,0.0,1.0,2.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,},
	{0.0,0.0,0.0,5.0,3.0,4.0,2.0,0.1,0.0,0.0,0.0,1.0,2.0,3.0,2.0,1.0,0.0,3.0,2.0,0.0,0.0,},
	{0.0,0.0,0.0,4.0,5.0,5.0,2.0,0.2,0.0,0.0,0.0,0.0,1.0,2.0,1.0,0.0,0.0,4.0,0.0,3.0,0.0,},
	{0.0,0.0,0.0,0.0,2.0,2.0,0.0,0.1,0.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,5.0,5.0,4.0,0.0,},
	{0.0,0.0,0.0,0.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,4.0,5.0,8.0,8.0,0.0,},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,},
*/
	{5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,},
	{5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,-1.0,-1.0,-2.0,-4.0,-4.0,-4.0,-4.0,-4.0,-2.0,-1.0,-1.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,5.0,5.0,},
	{5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,},
	{5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,},

};


void MeshField::Init()
{
	// 頂点バッファ生成
	{
		float xp, zp;
		xp = 5.0f;	// １マスの面積
		zp = 5.0f;

		// 頂点設定
		for (int x = 0; x <= 20; x++)
		{
			for (int z = 0; z <= 20; z++)
			{
				m_Vertex[x][z].Position = XMFLOAT3((x - 10) * xp, g_FieldHeight[z][x], (z - 10) * -zp);

				m_Vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
				m_Vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

				m_Vertex[x][z].TexCoord = XMFLOAT2(x*0.5f, z*0.5f);
			}
		}
		// 法線ベクトル算出
		for (int x = 1; x < 20; x++)
		{
			for (int z = 1; z < 20; z++)

			{
				XMFLOAT3 vx, vz, vn;
				vx.x = m_Vertex[x + 1][z].Position.x - m_Vertex[x - 1][z].Position.x;
				vx.y = m_Vertex[x + 1][z].Position.y - m_Vertex[x - 1][z].Position.y;
				vx.z = m_Vertex[x + 1][z].Position.z - m_Vertex[x - 1][z].Position.z;

				vz.x = m_Vertex[x][z-1].Position.x - m_Vertex[x][z+1].Position.x;
				vz.y = m_Vertex[x][z-1].Position.y - m_Vertex[x][z+1].Position.y;
				vz.z = m_Vertex[x][z-1].Position.z - m_Vertex[x][z+1].Position.z;

				// 外積
				vn.x = vz.y * vx.z - vz.z * vx.y;
				vn.y = vz.z * vx.x - vz.x * vx.z;
				vn.z = vz.x * vx.y - vz.y * vx.x;

				// 正規化
				float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
				vn.x /= len;
				vn.y /= len;
				vn.z /= len;

				m_Vertex[x][z].Normal = vn;
			}
		}

		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;

		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));

		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}



	//	インデックスバッファ生成
	{
		// 今回は21頂点必要
	// １行作る為に、21頂点必要で、左右に並べるから*2
	// を20列作る為 * 20
	// 最後の縮退を引く-2

		unsigned int index[((21 + 1) * 2) * 20 - 2];

		int i = 0;
		for (int x = 0; x < 20; x++)	// x>列数
		{
			for (int z = 0; z < 21; z++)	// z>頂点数
			{
				// 左側の頂点	0,1,2
				index[i] = x * 21 + z;
				i++;
				// 右側の頂点	3,4,5
				index[i] = (x + 1) * 21 + z;
				i++;
			}
			if (x == 19)break;	// xが最後(19)だったら縮退は不要

			// 縮退ポリゴン用頂点 2つ
			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;

		}
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);

		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));

		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	// テクスチャ読込
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\asphalt02-pattern.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
 	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	m_InitFinish = true;
}
void MeshField::Uninit()
{
	m_IndexBuffer->Release();
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void MeshField::Update()
{
}

void MeshField::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
//	Renderer::GetDeviceContext()->Draw((21 * 21), 0);
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}

float MeshField::GetHeight(XMFLOAT3 Position)
{
	int x, z;
	// ブロック番号算出
	x = (int)(Position.x / 5.0f + 10.0f);
	z = (int)(Position.z / -5.0f + 10.0f);
	if (x < 0 || z < 0 || x >= STAGE_1_X || z >= STAGE_1_Y) return 0.0f;

	XMFLOAT3 pos0, pos1, pos2, pos3;
	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	XMFLOAT3 v12, v1p;
	v12.x = pos2.x - pos1.x;
	v12.y = pos2.y - pos1.y;
	v12.z = pos2.z - pos1.z;

	v1p.x = Position.x - pos1.x;
	v1p.y = Position.y - pos1.y;
	v1p.z = Position.z - pos1.z;

	// 外積
	float cy = v12.z * v1p.x - v12.x * v1p.z;

	float py;
	XMFLOAT3 n;
	if (cy > 0.0f)
	{
		// 左上ポリゴン
		XMFLOAT3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;

		// 外積
		n.x = v10.y * v12.z - v10.z * v12.y;
		n.y = v10.z * v12.x - v10.x * v12.z;
		n.z = v10.x * v12.y - v10.y * v12.x;
	}
	else
	{
		// 右下ポリゴン
		XMFLOAT3 v13;
		v13.x = pos3.x - pos1.x;
		v13.y = pos3.y - pos1.y;
		v13.z = pos3.z - pos1.z;

		// 外積
		n.x = v12.y * v13.z - v12.z * v13.y;
		n.y = v12.z * v13.x - v12.x * v13.z;
		n.z = v12.x * v13.y - v12.y * v13.x;
	}
	// 高さ取得
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;
	return py;
}

void MeshField::seta(float a[21][21])
{

}

bool MeshField::GetInitFinish()
{
	return m_InitFinish;
}
XMFLOAT3 MeshField::GetFieldScale()
{
	return m_FieldCollision;
}

