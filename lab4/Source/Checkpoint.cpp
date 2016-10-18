//
//  Checkpoint.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/17/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "Game.h"
#include "MeshComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Checkpoint, Actor);

Checkpoint::Checkpoint(Game& game)
:Actor(game)
{
    auto sprite = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Checkpoint.itpmesh2");
    sprite->SetMesh(mMesh);

    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mMesh);
    coll->SetScale(0.75f);
}
