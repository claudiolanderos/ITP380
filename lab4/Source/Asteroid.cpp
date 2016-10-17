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
#include "MoveComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game)
    :Actor(game)
{
    auto sprite = MeshComponent::Create(*this);
    mesh = game.GetAssetCache().Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
    sprite->SetMesh(mesh);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    SetScale(0.1f);
    
    auto move = MoveComponent::Create(*this, Component::PreTick);
    move->SetLinearSpeed(150.0f);
    move->SetLinearAxis(1.0f);
}
