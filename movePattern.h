#pragma once

//#include "gameObject.h"
class Player;

class MovePattern
{

public:
	virtual ~MovePattern() = default;
	virtual void Update(Player* object) = 0;
};

class MovePatternNone :MovePattern
{
	virtual ~MovePatternNone() = default;
	virtual void Update(Player* object) override;
};