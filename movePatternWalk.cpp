#include "movePatternWalk.h"
#include "movePatternSlide.h"
#include "player.h"

MovePatternWalk::MovePatternWalk()
{
}

void MovePatternWalk::Update(Player* object)
{
	// �X���C�h�^�C�v�ֈڍs
	object->ChangeMovePattern(new MovePatternSlide);
}
