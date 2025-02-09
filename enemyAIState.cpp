#include "main.h"
#include "renderer.h"
#include "enemyMachine.h"
#include <list>
#include "game.h"
#include "enemyAIState.h"
#include "enemyAIBehavior.h"

std::unordered_map<ENEMYMACHINE_STATE, EnemyAIState*> EnemyStateManager::m_State{};

void EnemyAIStateIdle::Update()
{
	m_ChangeTime--;
	if (m_ChangeTime > 0.0f)return;

	m_Manager->ChangeState(ENEMYMACHINE_STATE_SEARCH);
}

void EnemyAIStateSearch::Update()
{
	XMFLOAT3 rot = m_EM->GetRotation();
	rot.y += 0.02f;

	m_EM->SetRotation(rot);

	m_ChangeTime--;
	if (m_ChangeTime > 0.0f)return;

	//if (m_EM->EnemyAILength() < 5.0f)
	{
		m_Manager->ChangeState(ENEMYMACHINE_STATE_BATTLE_MOVE);
		m_Manager->m_child = true;
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_MOVE_L);
	}
}

void EnemyAIStateStoker::Update()
{
	m_EM->EnemyTracking();
	m_EM->UpMove();
	m_ChangeTime--;

	if (m_ChangeTime > 0.0f)return;

	m_Manager->ChangeState(ENEMYMACHINE_STATE_SEARCH);
}

void EnemyAIStateBattle::Update()
{
	m_BN->Update();
	
	if (m_EM->EnemyAILength() > ENEMYMOVE_LENGTH_STOKER)
	{
		m_Manager->ChangeState(ENEMYMACHINE_STATE_STOKER);
		m_Manager->m_child = false;
	}
}

void EnemyAIState_BattleMove_LR::Update()
{
	m_EM->LeftMove();
	m_ChangeTime--;

	if (m_ChangeTime > 0.0f)return;

	float length = m_EM->EnemyAILength();
	if (length > ENEMYMOVE_LENGTH_STOKER)
	{
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_STOKER);
	}
	else if (length < ENEMYMOVE_LENGTH_AWAY)
	{
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_AWAY);
	}
}

void EnemyAIState_BattleMove_Away::Update()
{

	m_EM->DownMove();
	m_ChangeTime--;

	if (m_ChangeTime > 0.0f)return;

	if (m_EM->EnemyAILength() > ENEMYMOVE_LENGTH_STOKER)
	{
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_STOKER);
	}
	else if (m_EM->EnemyAILength() > ENEMYMOVE_LENGTH_AWAY)
	{
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_MOVE_L);
	}
}

void EnemyAIState_BattleMove_Stoker::Update()
{
	m_EM->UpMove();
	m_ChangeTime--;

	if (m_ChangeTime > 0.0f)return;
	if (m_EM->EnemyAILength() < ENEMYMOVE_LENGTH_STOKER)
	{
		m_Manager->ChangeChildState(ENEMYMACHINE_STATE_BATTLE_MOVE_L);
	}
}

EnemyStateManager::EnemyStateManager(EnemyMachine* _enemy):m_Enemy(_enemy)
{

}

EnemyStateManager::~EnemyStateManager()
{
	Unload();
}

void EnemyStateManager::Init(EnemyMachine* _enemy)
{
	for (auto state : m_State)
	{
		state.second->Init(_enemy, this);
	}

	m_NowState = m_State[ENEMYMACHINE_STATE_IDLE];
}

void EnemyStateManager::ChangeState(ENEMYMACHINE_STATE _nextState)
{
	if (m_State.find(_nextState) == m_State.end()) return;

	m_NowState = m_State[_nextState];
	m_NowState->m_ChangeTime = 60.0f * 3.0f;
}

void EnemyStateManager::ChangeChildState(ENEMYMACHINE_STATE newState)
{
	if (m_State.find(newState) == m_State.end()) return;

	m_NowChildState = m_State[newState];
	m_NowChildState->m_ChangeTime = 60.0f * 3.0f;
}

void EnemyStateManager::Update()
{
	if (!m_NowState) return;

		m_NowState->Update();

		if (m_child) m_NowChildState->Update();

}

bool EnemyStateManager::Load()
{
	// 基本系ステート
	m_State[ENEMYMACHINE_STATE_IDLE] = new EnemyAIStateIdle();
	m_State[ENEMYMACHINE_STATE_SEARCH] = new EnemyAIStateSearch();
	m_State[ENEMYMACHINE_STATE_STOKER] = new EnemyAIStateStoker();

	// 戦闘系ステート
	m_State[ENEMYMACHINE_STATE_BATTLE_STOKER] = new EnemyAIState_BattleMove_Stoker();
	m_State[ENEMYMACHINE_STATE_BATTLE_AWAY] = new EnemyAIState_BattleMove_Away();
	m_State[ENEMYMACHINE_STATE_BATTLE_MOVE_L] = new EnemyAIState_BattleMove_LR();

	// 戦闘基本ステートビヘイビアツリー
	{
		BehaviorNode* BehaviorNode_Move = new BehaviorTask_Battle_Move(m_State[ENEMYMACHINE_STATE_BATTLE_MOVE_L]);	// 戦闘時移動

		BehaviorNode* BehaviorRoot_Away = new BehaviorSelector();	// 回避セレクター
//		BehaviorRoot_Away->AddChild(BehaviorNode_Move);				// 戦闘時移動
		BehaviorRoot_Away->AddChild(new BehaviorTask_RangeCheck());		//距離確認
		BehaviorRoot_Away->AddChild(new BehaviorTask_Battle_Away());	// 回避行動

		BehaviorNode* BehaviorRoot_Battle = new BehaviorSequence();	// シーケンス
		BehaviorRoot_Battle->AddChild(new BehaviorTask_Battle_Tracking());	// 視線追従
		BehaviorRoot_Battle->AddChild(BehaviorNode_Move);				// 戦闘時移動
		BehaviorRoot_Battle->AddChild(BehaviorRoot_Away);					// 回避セレクター
		BehaviorRoot_Battle->AddChild(new BehaviorTask_Battle_Attack_Gun());	// 攻撃

		m_State[ENEMYMACHINE_STATE_BATTLE_MOVE] = new EnemyAIStateBattle(BehaviorRoot_Battle);
	}



	return true;
}

bool EnemyStateManager::Unload()
{
	for (auto state : m_State)
	{
		state.second->Uninit();
		state.second = nullptr;
		delete state.second;
	}
	m_State.clear();
	return true;
}

EnemyAIState::~EnemyAIState()
{
}

void EnemyAIState::Init(EnemyMachine* _enemy, EnemyStateManager* _manager)
{
	this->Init(_enemy);
	m_Manager = _manager;
}

void EnemyAIState::Init(EnemyMachine* _enemy)
{
	m_EM = _enemy;

	if (!m_BN) return;

	m_BN->Init(_enemy);
}

void EnemyAIState::Uninit()
{
	if (!m_BN) return;

	m_BN->Uninit();
	m_BN = nullptr;
	delete m_BN;
}
