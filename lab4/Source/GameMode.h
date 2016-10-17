#pragma once
#include "Actor.h"

class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

private:
    
};

DECL_PTR(GameMode);
