//
//  Tower.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Tower.h"
#include "Game.h"
#include "MeshComponent.h"

IMPL_ACTOR(Tower, Actor);

Tower::Tower(Game& game) :Actor(game)
{
    auto meshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/TowerBase.itpmesh2");
    meshComponent->SetMesh(mMesh);
}
