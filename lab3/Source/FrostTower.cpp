//
//  FrostTower.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "FrostTower.h"
#include "Game.h"

IMPL_ACTOR(FrostTower, Tower);

FrostTower::FrostTower(Game& game)
:Tower(game)
{
    mChild = Actor::SpawnAttached(*this);
    auto meshComponent = MeshComponent::Create(*mChild);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Frost.itpmesh2");
    meshComponent->SetMesh(mMesh);
    
    TimerHandle handle;
    game.GetGameTimers().SetTimer(handle, this, &FrostTower::FreezeEnemies, 2.0f, true);
}

void FrostTower::FreezeEnemies()
{
    std::vector<Enemy*> inRange;
    inRange = mGame.GetWorld().GetEnemiesInRange(this->GetPosition(), 150.0f);
    
    for(auto iter : inRange)
    {
        iter->Slow();
    }
}
