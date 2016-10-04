//
//  Spawner.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Spawner.h"
#include "Enemy.h"
#include "Game.h"

IMPL_ACTOR(Spawner, Actor);

Spawner::Spawner(Game& game)
:Actor(game)
{
    currEnemies = 0;
    waveEnemies = 5;
}

void Spawner::BeginPlay()
{
    mGame.GetGameTimers().SetTimer(mSpawnEnemyTimer, this, &Spawner::SpawnEnemy, 1.0f, true);
    mGame.GetGameTimers().PauseTimer(mSpawnEnemyTimer);
        mGame.GetGameTimers().SetTimer(mSpawnWaveTimer, this, &Spawner::SpawnWave, 10.0f, true);
}

void Spawner::SpawnEnemy()
{
    currEnemies += 1;
    Enemy::Spawn(mGame);
    if(currEnemies >= waveEnemies)
    {
        currEnemies = 0;
        waveEnemies += 5;
        mGame.GetGameTimers().PauseTimer(mSpawnEnemyTimer);
        mGame.GetGameTimers().UnpauseTimer(mSpawnWaveTimer);
    }
}

void Spawner::SpawnWave()
{
    mGame.GetGameTimers().PauseTimer(mSpawnWaveTimer);
    mGame.GetGameTimers().UnpauseTimer(mSpawnEnemyTimer);
}
