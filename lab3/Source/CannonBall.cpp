//
//  CannonBall.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "CannonBall.h"
#include "Game.h"

IMPL_ACTOR(CannonBall, Actor);

CannonBall::CannonBall(Game& game)
:Actor(game)
{
    auto meshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Cannonball.itpmesh2");
    meshComponent->SetMesh(mMesh);
    
    mMoveComponent = MoveComponent::Create(*this, Component::PreTick);
    mMoveComponent->SetLinearSpeed(300.0f);

    mSphereCollision = SphereCollision::Create(*this);
    mSphereCollision->RadiusFromMesh(mMesh);
}

void CannonBall::BeginPlay()
{
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &CannonBall::OnDieTimer, 3.0f);
}

void CannonBall::OnDieTimer()
{
    SetIsAlive(false);
}
