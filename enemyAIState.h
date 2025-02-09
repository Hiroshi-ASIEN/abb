/**************************************************
* EnemyAIState
* [enemyAIState.h]
* Author    �F���{�h�n
* Date      �F2025�N01��15��
***************************************************/
#pragma once

#include <unordered_map>
#include "enemyMachine.h"

// �e��ԊJ�n����
#define ENEMYMOVE_LENGTH_IDLE (60.0f)	// �ҋ@�J�n����
#define ENEMYMOVE_LENGTH_STOKER (40.0f)	// �Ǐ]�J�n����
#define ENEMYMOVE_LENGTH_AWAY	(5.0f)	// ����J�n����
#define ENEMYMOVE_LENGTH_BATTLE (10.0f)	// �퓬�J�n����

// ��Ԉꗗ
enum ENEMYMACHINE_STATE
{
	// ��퓬���
	ENEMYMACHINE_STATE_IDLE=0,	// �ҋ@
	ENEMYMACHINE_STATE_SEARCH,	// ���G(��])
	ENEMYMACHINE_STATE_STOKER,	// �Ǐ]

	// �퓬���
	ENEMYMACHINE_STATE_BATTLE_STOKER,	// �Ǐ]
	ENEMYMACHINE_STATE_BATTLE_AWAY,		// ���(����ړ�)
	ENEMYMACHINE_STATE_BATTLE_MOVE_L,	// ���񍶈ړ�
	ENEMYMACHINE_STATE_BATTLE_MOVE_R,	// ����E�ړ�
	ENEMYMACHINE_STATE_BATTLE_MOVE,

	ENEMYMACHINE_STATE_MAX,
};

// �G�X�e�[�g��{�N���X
class EnemyAIState
{
protected:
	class	EnemyMachine* m_EM{};
	class EnemyStateManager* m_Manager{};

	class BehaviorNode* m_BN{};
public:
	float m_ChangeTime = 60.0f * 3.0f; // �؂�ւ��܂ł̍ŏ�����
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

// �G�ҋ@�X�e�[�g
class EnemyAIStateIdle :public EnemyAIState
{
public:
	using EnemyAIState::EnemyAIState;
	void Update()override;
};

// �G�T���i��]�j�X�e�[�g
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

// �G�퓬�X�e�[�g
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


// �X�e�[�g�Ǘ�
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

	EnemyAIState* m_NowChildState{};	// ��...m_State�ʃN���X�ɂ��ׂ�
	bool m_child{};
};

//////////////////// EOF ////////////////////