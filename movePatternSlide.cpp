#include "movePatternSlide.h"
#include "movePatternWalk.h"
#include "player.h"

MovePatternSlide::MovePatternSlide()
{
}

void MovePatternSlide::Update(Player* object)
{
	// �����^�C�v�ֈڍs
	object->ChangeMovePattern(new MovePatternWalk);


}
