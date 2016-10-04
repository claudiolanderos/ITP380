//
//  Enemy.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/28/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Enemy.h"
#include "Game.h"

IMPL_ACTOR(Enemy, Actor);

Enemy::Enemy(Game& game) :Actor(game)
{
    mMeshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Peasant.itpmesh2");
    mMeshComponent->SetMesh(mMesh);
    
    SetPosition(GetGame().GetGameMode()->GetSpawnPos());
    SetRotation(0.0f);
    mMoveComponent = MoveComponent::Create(*this, Component::PreTick);
    mMoveComponent->SetLinearSpeed(60.0f);
    mMoveComponent->SetLinearAxis(1.0f);
    
    mSphereCollision = SphereCollision::Create(*this);
    mSphereCollision->RadiusFromMesh(mMesh);
}

void Enemy::BeginTouch(Actor &other)
{
    Super::BeginTouch(other);
    
    if(this->IsAlive() && IsA<Tile>(other))
    {
        this->SetIsAlive(false);
    }
}

void Enemy::BeginPlay()
{
    mGame.GetWorld().AddEnemy(*this);
}

void Enemy::EndPlay()
{
    mGame.GetWorld().RemoveEnemy(*this);
}

void Enemy::Slow()
{
    mMeshComponent->SetTextureIndex(1);
    mMoveComponent->SetLinearSpeed(30.0f);
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &Enemy::UnSlow, 1.0f);
}

void Enemy::UnSlow()
{
    mMeshComponent->SetTextureIndex(0);
    mMoveComponent->SetLinearSpeed(60.0f);
}
