/**************************************************
* Playerクラス
* [player.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "movePattern.h"
#include <string>
#include "weaponBase.h"

#define PLAYER_HP_MAX (100)
#define PLAYER_INVINSIBLE_TIME_MAX (60*0.2)
#define DESTROY_COUNT (60 * 2)	// 破壊されるまでの時間(秒)


// 武器場所
enum WeaponPosition
{
	WP_Center = 0,
	WP_L_ARM,
	WP_R_ARM,
	WP_L_SHOULDER,
	WP_R_SHOULDER,

	WP_MAX,
};

// 移動タイプ
enum MoveType
{
	Idle=0,
	Walk,
	Slide,

	MoveTypeMax,
};

//==================================================
// Playerクラス
//==================================================
class Player :public GameObject
{
protected:

	bool m_PCRotate = true;	// カメラの向きを向き続けるか（仮

	// モデル系
	static Component* m_ModelComponent;
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT4 m_Material{};

	//	const char* m_MovePaternAnimation =( "Idle");

	// アニメーション
	std::string m_AnimationMovePatern = "Idle";
	std::string m_NextAnimationMovePatern = "Idle";

	bool m_MoveTriger = false;
	int m_AnimationFrame;

	float m_AnimeTime;	// 簡易Animation風用変数
	float m_Blend = 0.0f;


	// 移動系
	MoveType m_MoveType = Slide;
	MovePattern* m_MovePattern;
	XMFLOAT3 oldPosition{};

	// ジャンプ系
	bool m_JumpUse = false;

	float m_BoostEnergy{};
	float m_BEmax{};
	float m_BoostPower{};

	XMFLOAT3 m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Accel = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float m_dt = 1.0f / 60.0f;		// 経過時間

	XMFLOAT4 m_Quatarnion{};
	XMFLOAT3 m_CameraRotation{};

	// 戦闘系
	int m_KillCount = 0;	// 撃破数
	float m_Hp = PLAYER_HP_MAX;	// 体力
	float m_InvisibleTime = PLAYER_INVINSIBLE_TIME_MAX;	// 無敵時間


	class Camera* camera;
	class Audio* m_SE{};	// SE
	class ParticleEmitter* m_Particle;
	class ParticleEmitter* m_MParticle;
	class ParticleEmitter* m_LRParticle;
	class ParticleEmitter* m_BParticle;
	class UI* m_UI{};
	UI* m_GageFrame{};
	UI* m_HpBar{};
	UI* m_HpFrame{};

	// 武器
	WeaponBase* m_LArmWepon;
	WeaponBase* m_RArmWepon;
	WeaponBase* m_LShoulderWepon;
	WeaponBase* m_RShoulderWepon;
	WeaponBase* m_CenterWepon;

//	Component* m_ChildModel{};

	WeaponBase* m_ChildModel{};

	class ShadowVolume* m_ShadowVolume {};
	class ShadowPolygon2D* m_ShadowPolygon2D{};

	int m_DestroyCount{};
private:
	void UpMove(XMFLOAT3 cForward);
	void DownMove(XMFLOAT3 cForward);
	void LeftMove(XMFLOAT3 cRight);
	void RightMove(XMFLOAT3 cRight);

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void Load();
	static void Unload();

	void AddKillCount(int count);
	int GetKillCount();

	int GetHp();
	void ChangeMovePattern(MovePattern* movepattern);

	virtual bool Damage(int damage);

	virtual float CheckPosition();
	void WeaponMove();

protected:

	virtual bool Defeated();	// 倒されたとき

	void PJump();


	virtual void Move();
	virtual void Attack();
	virtual bool Boost();


	
	void LArmAttack();
	void RArmAttack();
	void LShoulderAttack();
	void RShoulderAttack();
	void PAttack();

//	void Accept(Component* component);

//	XMFLOAT3 ForwardQuaternion(XMFLOAT4 quaternion);

	void ChangeAnimation(std::string nextAnimation);
	void ModelCreate();


public:
	void WeaponAccept(WEAPON_TYPE _weapon, WeaponPosition _position);
	virtual bool Away();
};




//////////////////// EOF ////////////////////
