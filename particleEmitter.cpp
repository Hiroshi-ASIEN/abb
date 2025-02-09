/**************************************************
* パーティクルエミッター
* [ParticleEmitter.cpp]
* Author    ：松本紘始
* Date      ：2024年05月15日
* 最終更新日 :2024年07月19日
***************************************************/

#include "main.h"
#include "renderer.h"
#include "particleEmitter.h"
#include "manager.h"
#include "camera.h"
#include "input.h"

ID3D11ShaderResourceView* ParticleEmitter::m_Texture{};

void ParticleEmitter::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
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

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}
void ParticleEmitter::Uninit()
{
//	m_Texture->Release();
	m_VertexBuffer->Release();
	if(m_PositionSRV) m_PositionSRV->Release();
	if(m_PositionBuffer) m_PositionBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ParticleEmitter::Update()
{
	// パーティクル発射
	int count = 10;

	if (m_Parent) UpdatePositionRotation();

	// パーティクルエミッターが起動されていたら発射
	if (this->isUse)
	{
		for (int i = 0; i < PARTICLE_MAX; i++)
		{
			if (this->m_Particle[i].Enable == false)
			{
				// タイプごとの発射処理
				switch (this->type)
				{
				case tNormal:	// ノーマル(授業のやつ)
					m_Particle[i].Life = 60;
					this->m_Particle[i].Position = this->m_Position;

					this->m_Particle[i].Velocity.x = (rand() % 100 - 50) / 500.0f;
					this->m_Particle[i].Velocity.y = (rand() % 100 + 50) / 500.0f;
					this->m_Particle[i].Velocity.z = (rand() % 100 - 50) / 500.0f;

					m_Particle[i].Acceleration.x = 0.0f;
					m_Particle[i].Acceleration.y = 0.0f;
					m_Particle[i].Acceleration.z = 0.0f;
					break;

				case tShower:	// シャワー（橋みたいなやつ）
					m_Particle[i].Life = 60;
					this->m_Particle[i].Position = this->m_Position;
					this->m_Particle[i].Velocity.x = (rand() % 100 - 50) / 50.0f;
					this->m_Particle[i].Velocity.y = 0.1f;
					this->m_Particle[i].Velocity.z = (rand() % 100 - 50) / 50.0f;
					m_Particle[i].Acceleration.x = 1.0f / 5;
					m_Particle[i].Acceleration.y = 1.0f / 5;
					m_Particle[i].Acceleration.z = 1.0f / 5;
					m_Particle[i].Alpha = 1.0f;
					rot++;
					break;
				case tJumpBooster:	// プレイヤージャンプ時のブースター
					m_Particle[i].Life = 20;
					this->m_Particle[i].Position = this->m_Position;
					this->m_Particle[i].Velocity.x = (rand() % 10 - 5) / 50.0f;
					this->m_Particle[i].Velocity.y = (rand() % 10 + 5) / 50.0f;
					this->m_Particle[i].Velocity.z = (rand() % 10 - 5) / 50.0f;
					m_Particle[i].Acceleration.x = sinf(rot) / 25;
					m_Particle[i].Acceleration.z = cosf(rot) / 25;
					m_Particle[i].Acceleration.y = -1.0f / 25;
					m_Particle[i].Alpha = 1.0f;
					rot++;
					break;
				case tBooster:	// 移動用ブースター
					m_Rotation = m_Parent->GetForward();

					m_Particle[i].Life = 10;
					this->m_Particle[i].Position.x = m_Position.x + ((rand() % 3 - 1) * 0.5f);
					this->m_Particle[i].Position.z = m_Position.z + ((rand() % 3 - 1) * 0.5f);
					this->m_Particle[i].Position.y = m_Position.y;// +((rand() % 2) * 0.5f);

					this->m_Particle[i].Velocity.x = -(m_Rotation.x * 0.8);
					this->m_Particle[i].Velocity.z = -(m_Rotation.z * 0.8);
					this->m_Particle[i].Velocity.y = 0.0f;

					m_Particle[i].Acceleration.x = ((sinf(rot) / 25) * (m_Particle[i].Velocity.x));
					m_Particle[i].Acceleration.z = ((sinf(rot) / 25) * (m_Particle[i].Velocity.z));
					m_Particle[i].Acceleration.y = 0.01f;//  cosf(rot) / 250;
					rot++;
					count -= 10;

					break;
				case tWind:	// 横移動する風にあおられてる感じのやつ
					m_Particle[i].Life = 60;
					this->m_Particle[i].Position.x = m_Position.x + (float)(rand() % 51 - 25);
					this->m_Particle[i].Position.y = m_Position.y + (float)(rand() % 21 - 10);
					this->m_Particle[i].Position.z = m_Position.z + (float)(rand() % 51 - 25);

					this->m_Particle[i].Velocity.x = 0.01f;
					this->m_Particle[i].Velocity.y = -0.1f;
					this->m_Particle[i].Velocity.z = 0.0f;
					m_Particle[i].Acceleration.y = (float)(rand() % 11 + 1) * 0.002;
					m_Particle[i].Acceleration.x = cosf(rot) / 100;
					m_Particle[i].Acceleration.z = -sinf(rot) / 100;
					rot++;
					count -= 1;
					break;

				case tRain:	// 上から降る雨みたいな感じのやつ
					m_Particle[i].Life = 40;
					this->m_Particle[i].Position.x = m_Position.x + (float)(rand() % 51 - 25);
					this->m_Particle[i].Position.y = m_Position.y + (float)(rand() % 21 - 10);
					this->m_Particle[i].Position.z = m_Position.z + (float)(rand() % 51 - 25);

					this->m_Particle[i].Velocity.x = 0.0f;
					this->m_Particle[i].Velocity.y = 0.001f;
					this->m_Particle[i].Velocity.z = 0.0f;
					m_Particle[i].Acceleration.x = (float)(rand() % 4 - 2) *0.002;
					m_Particle[i].Acceleration.y = -(float)(rand() % 11 + 1)*0.005;
					m_Particle[i].Acceleration.z = (float)(rand() % 4 - 2) *0.002;
					m_Particle[i].Alpha = 1.0f;
					break;

				case tFlare:	// 下から登る火の粉みたいな感じのやつ
					m_Particle[i].Life = 20;
					this->m_Particle[i].Position.x = m_Position.x + (float)(rand() % 51 - 25);
					this->m_Particle[i].Position.y = m_Position.y + (float)(rand() % 21 - 10);
					this->m_Particle[i].Position.z = m_Position.z + (float)(rand() % 51 - 25);

					this->m_Particle[i].Velocity.x =(rand() % 10 - 5) / 500.0f;
					this->m_Particle[i].Velocity.y =(rand() % 10 + 5) / 500.0f;
					this->m_Particle[i].Velocity.z =(rand() % 10 - 5) / 500.0f;
					m_Particle[i].Acceleration.x = (float)(rand() % 4 - 2) * 0.01;
					m_Particle[i].Acceleration.y = (float)(rand() % 8 + 2) * 0.01;
					m_Particle[i].Acceleration.z = (float)(rand() % 4 - 2) * 0.01;
					m_Particle[i].Alpha = 1.0f;
					count -= 2;
					break;

				case tFire:	// 焚火みたいな感じのやつ
					m_Particle[i].Life = 20;
					this->m_Particle[i].Position.x = m_Position.x;
					this->m_Particle[i].Position.y = m_Position.y;
					this->m_Particle[i].Position.z = m_Position.z;

					this->m_Particle[i].Velocity.x = 0.01f;
					this->m_Particle[i].Velocity.z = 0.01f;
					this->m_Particle[i].Velocity.y = -sinf((rand() % 11 - 5))/50 ;

					m_Particle[i].Acceleration.x = (rand() % 11 - 5)*0.001f;
					m_Particle[i].Acceleration.y = 0.02f;
					m_Particle[i].Acceleration.z = (rand() % 3- 1)*0.003f;
					rot++;
					count -= 5;
					break;

				case tBurst:	//P攻撃
					m_Rotation = m_Parent->GetForward();

					m_Particle[i].Life = 120;
					this->m_Particle[i].Position.x = m_Position.x + ((rand() % 3 - 1)*0.5f) ;
					this->m_Particle[i].Position.z = m_Position.z + ((rand() % 3 - 1) * 0.5f);
					this->m_Particle[i].Position.y = m_Position.y;// +((rand() % 2) * 0.5f);

					this->m_Particle[i].Velocity.x =-(m_Rotation.x *0.5f);
					this->m_Particle[i].Velocity.z =-(m_Rotation.z *0.5f);
					this->m_Particle[i].Velocity.y = 0.0f;

					m_Particle[i].Acceleration.x = 0.0f;
					m_Particle[i].Acceleration.z = -0.1f;
					m_Particle[i].Acceleration.y = 0.0f;

					m_Particle[i].Acceleration.x = -((sinf(rot) / 500) * (m_Particle[i].Velocity.z));
					m_Particle[i].Acceleration.z = -((sinf(rot) / 500) * (m_Particle[i].Velocity.x));
					m_Particle[i].Acceleration.y = (float)(cosf(rot)/1000 );
					rot++;

					break;

				case tShot:	// 射撃
					m_Particle[i].Life = 2;
					this->m_Particle[i].Position.x = m_Position.x + ((float)(rand() % 3 - 1) * 0.5f);
					this->m_Particle[i].Position.z = m_Position.z + ((float)(rand() % 3 - 1) * 0.5f);
					this->m_Particle[i].Position.y = m_Position.y;// +((rand() % 2) * 0.5f);

					this->m_Particle[i].Velocity.x = m_Rotation.x * 0.5f;
					this->m_Particle[i].Velocity.z = m_Rotation.z * 0.5f;
					this->m_Particle[i].Velocity.y = 0.0f;

					m_Particle[i].Acceleration.x = 0.0f;
					m_Particle[i].Acceleration.z = 0.1f;
					m_Particle[i].Acceleration.y = 0.0f;

					m_Particle[i].Acceleration.x = (sinf((float)rot) / 50) * (m_Particle[i].Velocity.z);
					m_Particle[i].Acceleration.z = (sinf((float)rot) / 50) * (m_Particle[i].Velocity.x);
					m_Particle[i].Acceleration.y = (float)(cosf(rot) / 100);
					rot++;
					count -= 50;
					break;

				case tBullet:
					m_Particle[i].Life = 10;
				this->m_Particle[i].Position = m_Position;

//					XMFLOAT3 pos = m_Parent->GetForward();
					count -= 10;
					break;
				default:
					break;
				}
				this->m_Particle[i].Enable = true;

				count--;
				if (count <= 0)	break;
			}
		}
	}
	// パーティクル移動
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (this->m_Particle[i].Enable == true)
		{
//			if (type == tBullet)
			{
//				this->m_Particle[i].Position = m_Position;
			}
//			else
			{
				if (type == tBurst)
				{
					if (m_Particle[i].Life > 115.0f)
					{
						// 移動処理
						m_Particle[i].Position.x -= m_Particle[i].Velocity.x;
						m_Particle[i].Position.y -= m_Particle[i].Velocity.y;
						m_Particle[i].Position.z -= m_Particle[i].Velocity.z;
					}
					else
					{
						// 移動処理
						m_Particle[i].Position.x += m_Particle[i].Velocity.x;
						m_Particle[i].Position.y += m_Particle[i].Velocity.y;
						m_Particle[i].Position.z += m_Particle[i].Velocity.z;
					}
				}
				else if (type == tShower)
				{
					m_Particle[i].Acceleration.y += -0.01f;
				}
				// 移動
				m_Particle[i].Velocity.x += m_Particle[i].Acceleration.x;
				m_Particle[i].Velocity.y += m_Particle[i].Acceleration.y;
				m_Particle[i].Velocity.z += m_Particle[i].Acceleration.z;

				// 重力
				this->m_Particle[i].Velocity.y += -0.01f;

				// 抵抗
				if (type != tNormal)
				{
					m_Particle[i].Velocity.x *= 0.8f;
					m_Particle[i].Velocity.y *= 0.8f;
					m_Particle[i].Velocity.z *= 0.8f;
				}

				// 移動
				m_Particle[i].Position.x += m_Particle[i].Velocity.x;
				m_Particle[i].Position.y += m_Particle[i].Velocity.y;
				m_Particle[i].Position.z += m_Particle[i].Velocity.z;
			}
			// ライフ
			m_Particle[i].Life--;
			if (m_Particle[i].Life <= 0)
			{
				if (this->type == tBurst)
				{
					this->SetIsUse(false);
				}
				m_Particle[i].Enable = false;
			}
		}
	}
}

void ParticleEmitter::Draw()
{
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
//	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.Diffuse = m_Material;		// マテリアルは外部から設定可能
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Zバッファ無効
	Renderer::SetDepthEnable(false);

	// 加算合成有効
	Renderer::SetBlendAddEnable(true);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (this->m_Particle[i].Enable == true)
		{
			// ワールドマトリクス設定
			XMMATRIX world, scale, trans;
			scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
			trans = XMMatrixTranslation(m_Particle[i].Position.x, m_Particle[i].Position.y, m_Particle[i].Position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			// ポリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}

	// Zバッファ有効
	Renderer::SetDepthEnable(true);

	// 加算合成無効
	Renderer::SetBlendAddEnable(false);
}

// パーティクルエミッター起動設定
void ParticleEmitter::SetIsUse(bool use)
{
	this->isUse = use;
}

void ParticleEmitter::SetParticleDestroy()
{
}

// タイプ設定
void ParticleEmitter::SetType(ParticleType type)
{
	this->type = type;
}

// カラー設定
void ParticleEmitter::SetMaterialColor(XMFLOAT4 color)
{
	m_Material = color;
}

void ParticleEmitter::SetOffSet(XMFLOAT3 offset)
{
	m_OffSet = offset;
}

void ParticleEmitter::SetParent(GameObject* parent)
{
	m_Parent = parent;

}

void ParticleEmitter::UpdatePositionRotation()
{
	{
		if (!m_Parent) return;  // 親オブジェクトが設定されていない場合は何もしない

		XMFLOAT3 forward = m_Parent->GetForward();
		XMFLOAT3 parentPosition = m_Parent->GetPosition();

		// オフセットの距離を前方ベクトルに基づいて計算
	//	float distance = 15.0f;  // 前方の中心位置
	//	offset.x = forward.x * distance;
	//	offset.y = forward.y * distance;
	//	offset.z = forward.z * distance;

		// 新しい位置を計算
		XMFLOAT3 newPosition;
		newPosition.x = (parentPosition.x + forward.x)+ m_OffSet.x;
		newPosition.y = (parentPosition.y + forward.y)+ m_OffSet.y;
		newPosition.z = (parentPosition.z + forward.z)+ m_OffSet.z;

		// SearchCollisionの位置を更新
		m_Position = newPosition;
	}

}
void ParticleEmitter::ParticleMove()
{
	m_Particle->Acceleration.z = 10.0f;

	m_Particle->Velocity.x += m_Rotation.x * m_Particle->Acceleration.z;
	m_Particle->Velocity.z += m_Rotation.z * m_Particle->Acceleration.z;

	// 摩擦処理
	m_Particle->Velocity.x -= m_Particle->Velocity.x * 0.1f;
	m_Particle->Velocity.z -= m_Particle->Velocity.z * 0.1f;

	// 移動処理
	m_Particle->Position.x += m_Particle->Velocity.x * 1.0f;
	m_Particle->Position.y += m_Particle->Velocity.y * 1.0f;
	m_Particle->Position.z += m_Particle->Velocity.z * 1.0f;

}


void ParticleEmitter::Load()
{
	// テクスチャ読込
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\particle.png", WIC_FLAGS_NONE, &metadata, image);

	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
}

void ParticleEmitter::Unload()
{
	m_Texture->Release();

}
