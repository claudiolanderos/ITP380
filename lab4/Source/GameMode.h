#pragma once
#include "Actor.h"
#include "Ship.h"
#include "AudioComponent.h"
#include "Arrow.h"

class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

    ~GameMode();
    
    void StartGame();
    
    void CollectCheckPoint();
private:
    void SpawnCheckpoint();
    
    ShipPtr mShip;
    AudioComponentPtr mAudioComponent;
    ArrowPtr    mArrow;
};

DECL_PTR(GameMode);
