//
//  Ship.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "MoveComponent.h"
#include "Sound.h"
#include "SphereCollision.h"
#include "Asteroid.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include "Checkpoint.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
    :Actor(game)
{
    mMeshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    mMeshComponent->SetMesh(mMesh);

    //Load sound
    mSoundCue = mAudioComponent->PlaySound(game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav"), true);
    
    mInputComponent = InputComponent::Create(*this, Component::PreTick);
    mInputComponent->SetAngularSpeed(Math::Pi);
    mInputComponent->SetLinearSpeed(400.0f);
    mInputComponent->SetPitchSpeed(Math::Pi);
    mCameraComponent = CameraComponent::Create(*this);
    mCameraComponent->SetMoveComponent(mInputComponent);
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mMesh);
    coll->SetScale(1.0f);
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    if(Math::IsZero(mInputComponent->GetLinearAxis()))
    {
        mSoundCue.Pause();
    }
    else
    {
        mSoundCue.Resume();
    }
}

void Ship::FireMissile()
{
}

void Ship::BeginPlay()
{
    mInputComponent->BindLinearAxis("Move");
    mInputComponent->BindYawAxis("Yaw");
    mInputComponent->BindPitchAxis("Pitch");
    mCameraComponent->SnapToIdealPosition();
}

void Ship::BeginTouch(Actor& other)
{
    Super::BeginTouch(other);
    if(this->IsPaused() == false && IsA<Checkpoint>(other))
    {
        other.SetIsAlive(false);
        mGame.GetGameMode()->CollectCheckPoint();
    }
}

void Ship::OnRespawnShip()
{
    SetIsPaused(false);
    mMeshComponent->SetIsVisible(true);
    SetPosition(Vector3::Zero);
}

void Ship::Recenter()
{
    SetRotation(Quaternion::Identity);
    mCameraComponent->SnapToIdealPosition();
}
