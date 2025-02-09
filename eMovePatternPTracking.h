#pragma once
#include "eMovePattern.h"

class EnemyMovePatternPTracking :public EnemyMovePattern
{
public:
	EnemyMovePatternPTracking();
	virtual ~EnemyMovePatternPTracking() = default;
	virtual void Update(Enemy* object,XMFLOAT3 targetPos) override;
};