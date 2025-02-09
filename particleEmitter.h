#pragma once

#include "gameObject.h"

enum ParticleType
{
	tNormal = 0,
	tShower,
	tJumpBooster,
	tBooster,
	tWind,
	tRain,
	tFlare,
	tFire,
	tBurst,
	tShot,
	tBullet,
	TypeMax,
};
// エフェクトは3dで座標指定するので3dオブジェクト
class ParticleEmitter :public GameObject
{
private:

	XMFLOAT3 m_OffSet{};

	ID3D11Buffer* m_VertexBuffer = NULL;
	static ID3D11ShaderResourceView* m_Texture;

	ID3D11Buffer* m_PositionBuffer{};
	ID3D11ShaderResourceView* m_PositionSRV{};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	XMFLOAT4 m_Material = XMFLOAT4(0.5f, 0.1f, 0.1f, 1.0f);
		//XMFLOAT4(1.0, 1.0, 1.0, 1.0);
	bool isUse = true;
	int m_AnimeCount{};	// 初期化
	int type = tNormal;

	int rot = 0;
	// パーティクル一粒を表す構造体
	struct PARTICLE
	{
		bool	 Enable;
		int		 Life;
		float Alpha;
		XMFLOAT3 Position;
		XMFLOAT3 Velocity;
		XMFLOAT3 Acceleration;


	};

	static const int PARTICLE_MAX = 1000;
	PARTICLE m_Particle[PARTICLE_MAX]{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetIsUse(bool use);
	void SetParticleDestroy();

	void SetType(ParticleType type);
	void SetMaterialColor(XMFLOAT4 color);

	void SetOffSet(XMFLOAT3 offset);
	void SetParent(GameObject* parent);

	void UpdatePositionRotation();

	void ParticleMove();
	void SetRandomRange(int _xRange, int _xOffSet, int _zRange, int _zOffSet);

	static void Load();
	static void Unload();
};