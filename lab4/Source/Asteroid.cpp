//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Asteroid.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Random.h"
#include "SphereCollision.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game)
    :Actor(game)
{
    auto sprite = MeshComponent::Create(*this);
    mesh = game.GetAssetCache().Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
    sprite->SetMesh(mesh);
    SetScale(0.1f);
}
