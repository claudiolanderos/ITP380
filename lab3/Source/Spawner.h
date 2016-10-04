//
//  Spawner.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "GameTimers.h"

class Spawner : public Actor
{
    DECL_ACTOR(Spawner, Actor);
public:
    Spawner(Game& game);
    
    void BeginPlay() override;
    
    void SpawnEnemy();
    
    void SpawnWave();
    
private:
    std::atomic<int> currEnemies;
    std::atomic<int> waveEnemies;
    TimerHandle mSpawnWaveTimer;
    TimerHandle mSpawnEnemyTimer;
};
DECL_PTR(Spawner);
