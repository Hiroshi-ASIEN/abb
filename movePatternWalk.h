#pragma once

#include "movePattern.h"

class MovePatternWalk :public MovePattern
{
public:
	MovePatternWalk();
	virtual ~MovePatternWalk() = default;
	virtual void Update(Player* object)override;
};