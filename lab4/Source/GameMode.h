#pragma once
#include "Actor.h"
#include "Ship.h"
#include "AudioComponent.h"
#include "Arrow.h"
#include "GameTimers.h"
#include "HUD.h"

class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

    ~GameMode();
    
    void StartGame();
    
    void EndGame();
    
    void CollectCheckPoint();
private:
    void SpawnCheckpoint();
    
    ShipPtr mShip;
    AudioComponentPtr mAudioComponent;
    ArrowPtr mArrow;
    TimerHandle timeHandle;
    HUDPtr mHUD;
    int range = 0;
};

DECL_PTR(GameMode);
