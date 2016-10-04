//
//  CannonTower.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "CannonTower.h"
#include "Game.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& game)
    :Tower(game)
{
    mChild = Actor::SpawnAttached(*this);
    auto meshComponent = MeshComponent::Create(*mChild);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Cannon.itpmesh2");
    meshComponent->SetMesh(mMesh);
}
