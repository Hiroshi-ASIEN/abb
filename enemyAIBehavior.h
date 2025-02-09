/**************************************************
* EnemyAIBehavior
* [enemyAIBehavior.h]
* Author    ：松本紘始
* Date      ：2025年01月25日
***************************************************/
#pragma once

#include <unordered_map>
#include "enemyMachine.h"

// ビヘイビアツリーノードの戻り値
enum BEHAVIOR_RESULT
{
	BEHAVIOR_RESULT_CONTINUE,
	BEHAVIOR_RESULT_SUCCESS,
	BEHAVIOR_RESULT_FAULURE,
};

// ビヘイビアツリーノードの基本クラス
class BehaviorNode
{
protected:
	std::vector<BehaviorNode*> m_Child;	// 子ノード
	class EnemyMachine* m_EM{};
	EnemyAIState* m_EAIS{};	// ステートマシン

public:
	BehaviorNode() {};
	BehaviorNode(EnemyAIState* enemyAIState);
	~BehaviorNode();

	void Init(EnemyMachine* _enemy);
	void AddChild(BehaviorNode* _child);

	virtual BEHAVIOR_RESULT Update() = 0;
	void Uninit();
};

// ビヘイビアツリーのシーケンス
class BehaviorSequence :public BehaviorNode
{
private:
	int m_Index = 0;

public:
	using BehaviorNode::BehaviorNode;	// 基本クラスのコンストラクタを利用
	BEHAVIOR_RESULT Update()override;
};

// ビヘイビアツリーのセレクタ
class BehaviorSelector :public BehaviorNode
{
private:
	int m_Index = 0;
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;

};

// ビヘイビアツリーのタスク(戦闘)

class BehaviorTask_Battle_Idle :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Move:public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Attack_Gun :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Tracking :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_HealthCheck :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_RangeCheck :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_DownMove :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};
class BehaviorTask_Battle_Away :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};

class BehaviorTask_Battle_Boost :public BehaviorNode
{
public:
	using BehaviorNode::BehaviorNode;
	BEHAVIOR_RESULT Update()override;
};


//////////////////// EOF ////////////////////