/**************************************************
* EnemyAIState
* [enemyAIState.h]
* Author    ：松本紘始
* Date      ：2025年01月15日
***************************************************/
#pragma once

#include <unordered_map>
#include "enemyMachine.h"

// 各状態開始距離
#define ENEMYMOVE_LENGTH_IDLE (60.0f)	// 待機開始距離
#define ENEMYMOVE_LENGTH_STOKER (40.0f)	// 追従開始距離
#define ENEMYMOVE_LENGTH_AWAY	(5.0f)	// 回避開始距離
#define ENEMYMOVE_LENGTH_BATTLE (10.0f)	// 戦闘開始距離

// 状態一覧
enum ENEMYMACHINE_STATE
{
	// 非戦闘状態
	ENEMYMACHINE_STATE_IDLE=0,	// 待機
	ENEMYMACHINE_STATE_SEARCH,	// 索敵(回転)
	ENEMYMACHINE_STATE_STOKER,	// 追従

	// 戦闘状態
	ENEMYMACHINE_STATE_BATTLE_STOKER,	// 追従
	ENEMYMACHINE_STATE_BATTLE_AWAY,		// 回避(後方移動)
	ENEMYMACHINE_STATE_BATTLE_MOVE_L,	// 旋回左移動
	ENEMYMACHINE_STATE_BATTLE_MOVE_R,	// 旋回右移動
	ENEMYMACHINE_STATE_BATTLE_MOVE,

	ENEMYMACHINE_STATE_MAX,
};

// 敵ステート基本クラス
class EnemyAIState
{
protected:
	class	EnemyMachine* m_EM{};
	class EnemyStateManager* m_Manager{};

	class BehaviorNode* m_BN{};
public:
	float m_ChangeTime = 60.0f * 3.0f; // 切り替わるまでの最小時間
	EnemyAIState() {}; // = delete;
	EnemyAIState(float changeTime) { m_ChangeTime = changeTime; }
	EnemyAIState(BehaviorNode* bn) { m_BN = bn; }
	EnemyAIState(BehaviorNode* bn, float changeTime) { m_BN = bn; m_ChangeTime = changeTime; }
	virtual ~EnemyAIState();

	virtual void Update() = 0;	
	virtual void Init(EnemyMachine* _enemy, EnemyStateManager* _manager);
	virtual void Init(EnemyMachine* _enemy);
	virtual void Uninit();
};

// 敵待機ステート
class EnemyAIStateIdle :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

// 敵探索（回転）ステート
class EnemyAIStateSearch :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

class EnemyAIStateStoker :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

// 敵戦闘ステート
class EnemyAIStateBattle :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

class EnemyAIState_BattleMove_LR :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

class EnemyAIState_BattleMove_Away :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

class EnemyAIState_BattleMove_Stoker :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};


// ステート管理
class EnemyStateManager
{
private:
	EnemyAIState* m_NowState{};
	EnemyMachine* m_Enemy{};


public:
	static std::unordered_map<ENEMYMACHINE_STATE, EnemyAIState*> m_State;
	EnemyStateManager(EnemyMachine* _enemy);
	~EnemyStateManager();

	void Init(EnemyMachine* _enemy);

	void ChangeState(ENEMYMACHINE_STATE newState);
	void ChangeChildState(ENEMYMACHINE_STATE newState);
	void Update();

	static bool Load();
	static bool Unload();

	EnemyAIState* m_NowChildState{};	// 仮...m_State別クラスにすべき
	bool m_child{};
};

//////////////////// EOF ////////////////////