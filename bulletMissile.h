/**************************************************
* BulletMissileクラス
* [bullet.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "gameObject.h"
#include "component.h"
#include <list>
#include "bullet.h"

#include "Collision.h"
#define COMPONENT_INDEX (20)
#define M_DESTROY_COUNT_MAX (60*2)

//==================================================
// BulletMissileクラス
//==================================================
class BulletMissile :public Bullet
{
private:
	float m_RotationSpeed = 1.0f;	// 回転速度

	XMFLOAT4 m_Quaternion{};

	float m_MissileSpeed = 1.0f;

	XMFLOAT3 m_Direction{0.0f,0.0f,0.0f};

	int i = 0;
	float m_Count = 20.0f;
	float m_DestroyCount = M_DESTROY_COUNT_MAX;

public:
	void Init()override;	// 初期化処理
	void Uninit()override;	// 終了処理
	void Update()override;	// 更新処理
	void Draw()override;	// 描画処理

	void Move();			// 移動処理
	void TrackingMove();
	void SetParent(GameObject* parent);

//	void SetTargetObject(GameObject* object);	// 追従ターゲット設定
//	void SetTargetPosition(XMFLOAT3 position);	// 着弾ポジション設定（こっちを定期更新する？）

};




//////////////////// EOF ////////////////////