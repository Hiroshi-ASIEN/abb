#pragma once

#include "eMovePattern.h"

class EnemyMovePatternAreaTracking :public EnemyMovePattern
{
public:
	EnemyMovePatternAreaTracking();
	virtual ~EnemyMovePatternAreaTracking() = default;
	virtual void Update(Enemy* object)override;
};