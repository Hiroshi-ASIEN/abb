/**************************************************
* Weapon ベースクラス
* [WeaponBase.h]
* Author    ：松本紘始
* Date      ：2024年11月07日
***************************************************/
#pragma once

#include "gameObject.h"
#include "bullet.h"
#include "bulletMissile.h"
#include "component.h"
#include <string>
//#include "player.h"

#define TRIGGER_TIME_MAX (60.0f*1.0f)

enum WeaponPosition;

enum WEAPON_TYPE
{
	CANON = 0,
	RIFLE,
	MISSILE,
	Sword,
	WT_MAX,
};

class WeaponBase :public GameObject
{
protected:
	// 使用系
	bool m_AutoTarget{};	// ターゲットのほうを自動で向くか 初期 true
	bool m_AttackUse = false;	// 撃ったか
	float m_TriggerTimeMax = TRIGGER_TIME_MAX;
	float m_TriggerTime = TRIGGER_TIME_MAX;	// 発射間隔
	int m_MagazineCapacityMax = 500;	// 1マガジン装填可能数
	int m_MagazineCapacity = 500;		// 現在のマガジン装填数
	int m_BulletAllCapacityMax = 100;		// 所持弾数上限
	int m_BulletAllCapacity = 100;			// 所持弾数

	// モデル系
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	XMFLOAT4 m_Material{};
	
	XMFLOAT3 m_OffSet{};	// 親からの座標のずれ位置
	GameObject* m_Target{};
	// パーティクルエミッター
	class ParticleEmitter* m_Particle;

	//
	class Audio* m_SE;

public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void ActiveMove();			// 作動中の動き
	virtual void Shot() = 0;			// 発射関連
	virtual void ReSetTriggerTime();	// 発射できるまでのtimer管理

	virtual void CreateParticle();		// パーティクル生成
	virtual Bullet* CreateBullet(BulletType _bullet);		// 弾生成

	virtual WeaponBase* GetWeapon();	// 武器情報取得用
public:
	virtual void Attack();				// 攻撃
	virtual void MagazineReload();		// リロード
	XMFLOAT3 GetOffSet();
	virtual void SetOffSet(XMFLOAT3 _sizeoff);	// ずれ座標設定
	virtual void SetParent(GameObject* _parent);

	void AutoTarget(bool _frag);

	void SetDirection(XMFLOAT3 _rot);
protected:
	void SetWeaponConfig(float _triggerTime, int _magazineCapacity, int _allCapacity);
};

