/**************************************************
* EnemyMachineクラス
* [EnemyMachine.h]
* Author    ：松本紘始
* Date      ：2024年05月15日
***************************************************/
#pragma once

#include "player.h"
//#include "enemy.h"
#include <unordered_map>
#define ACCEL_NORMAL (0.5f)
#define ACCEL_ATTACK (0.2f)

#define AISTATE_CHANGETIME_DEFAULT_MAX (60.0f*2.0f)

//==================================================
// EnemyMachineクラス
//==================================================
class EnemyMachine :public Player
{
private:
	class EnemyAIState* eAIS;

	class EnemyStateManager* m_StateManager;
//	BehaviorNode* m_BehaviorRoot_Battle;	// ビヘイビアツリーのルートノード

//	EnemyMovePattern* m_EnemyMovePattern;
//	EnemyMoveType m_Type = Search;
//	EnemyLRMove m_LR = L;
	XMFLOAT3 targetPos{};
	bool m_Move{};
	float m_AwayTimeCount{};
	int m_AwayTimeCountMax{};
	bool m_nextAwayDirection{};



public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void AddKillCount(int count);
	int GetKillCount();
	void EnemyTracking();
//	void ChangeMovePattern(EnemyMovePattern* _movepattern);

	bool DistanceRange(XMFLOAT3 _distance);


	void UpMove();
	void DownMove();
	void LeftMove();
	void RightMove();

	virtual bool Boost()override;
	virtual void Move()override;
	virtual bool Damage(int damage)override;
	virtual void Attack()override;
	virtual bool Defeated() override;	// 倒されたとき

	void SetAccel(XMFLOAT3 _accel);


	void EnemyAI();
	float EnemyAILength();
	XMFLOAT3 EnemyAIDistance();


	void LRAwayMove();
	void SetLRAwayCountMax(int _countMax);

	void SetState(EnemyAIState* _state);
};




//////////////////// EOF ////////////////////
/*
id/mv/at

at.mv-atSR

mv-SRat-id
mv.st/mv/aw
at.at/rl
*/